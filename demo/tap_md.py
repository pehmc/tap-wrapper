"""
Copyright (c) 2026 pehmc. Apache 2.0 License.
See LICENSE file in the project root for full license information.
"""

import os
import time
from pathlib import Path

from tap.api import MdApi


class TapQuoteApi(MdApi):
    """TAP 行情 API 封装（含合约查询）"""

    def __init__(self):
        super().__init__()
        self.connect_status = False
        self.login_status = False
        self.subscribed_symbols = set()
        self.commodities = []          # 缓存商品列表
        self.contracts = []            # 缓存合约列表

    def onRspLogin(self, error: int, data: dict) -> None:
        """登录响应"""
        if error != 0:
            print(f"行情服务器登录失败，错误码：{error}")
            self.login_status = False
        else:
            print("行情服务器登录成功")
            self.login_status = True
            self.connect_status = True

    def onAPIReady(self) -> None:
        """API 就绪后，先查商品，再查合约"""
        print("行情 API 已就绪，开始查询商品信息...")
        self.qryCommodity()

    def onDisconnect(self, reason: int) -> None:
        self.connect_status = False
        self.login_status = False
        print(f"行情服务器连接断开，原因码：{reason}")

    def onRspQryCommodity(self, session: int, error: int, last: str, data: dict) -> None:
        """商品查询回报"""
        if error != 0:
            print(f"查询商品失败，错误码：{error}")
            return

        if data:
            self.commodities.append(data)
            commodity = data.get("Commodity", {})
            print(f"  商品: {commodity.get('CommodityNo')} | "
                  f"交易所: {commodity.get('ExchangeNo')} | "
                  f"类型: {commodity.get('CommodityType')} | "
                  f"名称: {data.get('CommodityEngName', '')}")

        if last == "Y":
            print(f"商品查询完成，共 {len(self.commodities)} 条")
            # 以 COMEX 黄金为例，查询其下的合约
            target = next((
                c for c in self.commodities
                if c.get("Commodity", {}).get("ExchangeNo") == "COMEX"
                and c.get("Commodity", {}).get("CommodityNo") == "GC"
            ), None)
            if target:
                comm = target.get("Commodity", {})
                print(f"开始查询合约: {comm.get('CommodityNo')}")
                req = {
                    "ExchangeNo": comm.get("ExchangeNo"),
                    "CommodityType": comm.get("CommodityType"),
                    "CommodityNo": comm.get("CommodityNo"),
                }
                self.qryContract(req)
            else:
                print("未找到目标商品，可用商品如下：")
                for c in self.commodities[:10]:
                    comm = c.get("Commodity", {})
                    print(f"  {comm.get('ExchangeNo')} {comm.get('CommodityNo')} ({c.get('CommodityEngName')})")

    def onRspQryContract(self, session: int, error: int, last: str, data: dict) -> None:
        """合约查询回报"""
        if error != 0:
            print(f"查询合约失败，错误码：{error}")
            return

        if data:
            self.contracts.append(data)
            contract = data.get("Contract", {})
            comm = contract.get("Commodity", {})
            symbol = comm.get("CommodityNo", "") + contract.get("ContractNo1", "")
            print(f"  合约: {symbol} | "
                  f"到期日: {data.get('ContractExpDate', 'N/A')} | "
                  f"名称: {data.get('ContractName', '')}")

        if last == "Y":
            print(f"合约查询完成，共 {len(self.contracts)} 条")
            if self.contracts:
                # 订阅第一个合约（或按需求筛选）
                first = self.contracts[0]
                self._do_subscribe(first)

    def _do_subscribe(self, contract: dict) -> None:
        """执行订阅（使用服务器返回的真实合约代码）"""
        c = contract.get("Contract", {})
        comm = c.get("Commodity", {})
        tap_contract = {
            "ExchangeNo": comm.get("ExchangeNo"),
            "CommodityType": comm.get("CommodityType"),
            "CommodityNo": comm.get("CommodityNo"),
            "ContractNo1": c.get("ContractNo1"),
            "CallOrPutFlag1": "0",
            "CallOrPutFlag2": "0",
            "StrikePrice1": "0",   # ← 从 0 改为 "0"
            "StrikePrice2": "0",   # ← 从 0 改为 "0"
        }
        symbol = comm.get("CommodityNo", "") + c.get("ContractNo1", "")
        print(f"订阅行情: {symbol}")
        self.subscribeQuote(tap_contract)

    def onRspSubscribeQuote(self, session: int, error: int, last: str, data: dict) -> None:
        if error != 0:
            print(f"订阅行情失败，错误码：{error}")
            return
        comm = data.get("Commodity", {})
        symbol = comm.get("CommodityNo", "") + data.get("ContractNo1", "")
        print(f"订阅成功：{symbol}")

    def onRtnQuote(self, data: dict) -> None:
        contract = data.get("Contract", {})
        comm = contract.get("Commodity", {})
        symbol = comm.get("CommodityNo", "") + contract.get("ContractNo1", "")
        print(f"[{data.get('DateTimeStamp', 'N/A')}] {symbol} | "
              f"最新价={data.get('QLastPrice', 'N/A')} | "
              f"成交量={data.get('QTotalQty', 'N/A')} | "
              f"买一={data.get('QBidPrice', [None])[0]}/{data.get('QBidQty', [None])[0]} | "
              f"卖一={data.get('QAskPrice', [None])[0]}/{data.get('QAskQty', [None])[0]}")

    def connect(self, host: str, port: int, username: str, password: str, auth_code: str = "") -> None:
        if self.connect_status:
            print("已连接，跳过重复连接")
            return

        self.init()

        req = {
            "AuthCode": auth_code,
            "KeyOperationLogPath": "",
            "LogLevel": 0
        }
        self.createTapQuoteAPI(req)

        self.setHostAddress(host, port)
        self.login({
            "UserNo": username,
            "Password": password,
            "ISModifyPassword": "N",
            "ISDDA": "N"
        })
        print(f"正在连接行情服务器 {host}:{port} ...")

    def close(self) -> None:
        if self.connect_status:
            self.disconnect()
            self.exit()
            self.connect_status = False


def main():
    config = {
        "host": "61.163.243.173",
        "port": 7171,
        "username": "ES",
        "password": "123456",
        "auth_code": "B112F916FE7D27BCE7B97EB620206457946CED32E26C1EAC946CED32E26C1EAC946CED32E26C1EAC5211AF9FEE541DDE9D6F622F72E25D5DEF7F47AA93A738EF5A51B81D8526AB6A9D19E65B41F59D6A946CED32E26C1EACCAF8D4C61E28E2B1ABD9B8F170E14F8847D3EA0BF4E191F5DCB1B791E63DC196D1576DEAF5EC563CA3E560313C0C3411B45076795F550EB050A62C4F74D5892D2D14892E812723FAC858DEBD8D4AF9410729FB849D5D8D6EA48A1B8DC67E037381A279CE9426070929D5DA085659772E24A6F5EA52CF92A4D403F9E46083F27B19A88AD99812DADA44100324759F9FD1964EBD4F2F0FB50B51CD31C0B02BB437"
    }

    api = TapQuoteApi()
    api.connect(config["host"], config["port"], config["username"], config["password"], config["auth_code"])

    print("等待登录并完成合约查询...")
    timeout = 30
    while timeout > 0:
        time.sleep(1)
        timeout -= 1
        # 当合约列表非空且已登录时，说明查询流程已走完
        if api.contracts and api.login_status:
            break

    if not api.contracts:
        print("未获取到合约列表，退出")
        api.close()
        return

    print(f"\n开始接收行情，运行 60 秒...")
    time.sleep(60)

    api.close()
    print("程序结束")


if __name__ == "__main__":
    main()