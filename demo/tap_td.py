"""
Copyright (c) 2026 pehmc. Apache 2.0 License.
See LICENSE file in the project root for full license information.
"""

import os
import sys
import time
from pathlib import Path

# 添加tap目录到Python路径
sys.path.insert(0, str(Path(__file__).parent.parent))

from tap.api import tdapi


class TapTradeApi(tdapi.ITapTradeAPINotify):
    """TAP 交易 API 封装"""

    def __init__(self):
        super().__init__()
        self.connect_status = False
        self.login_status = False
        self._api = None

    def init(self):
        """初始化API"""
        pass

    def createTapTradeAPI(self, req):
        """创建交易API"""
        app_info = tdapi.TapAPIApplicationInfo()
        app_info.AuthCode = req.get("AuthCode", "")
        app_info.KeyOperationLogPath = req.get("KeyOperationLogPath", "/tmp/tap_log")
        app_info.LogLevel = req.get("LogLevel", "N")           # APILOGLEVEL_NONE
        app_info.APPID = req.get("APPID", "")                  # 申请授权时分配的APPID
        app_info.ReConnectCount = req.get("ReConnectCount", 0)
        app_info.ReConnectSeconds = req.get("ReConnectSeconds", 0)
    
        log_path = Path(app_info.KeyOperationLogPath)
        log_path.mkdir(parents=True, exist_ok=True)
    
        iResult = [0]
        try:
            self._api = tdapi.CreateITapTradeAPI(app_info, iResult)
        except Exception as e:
            print(f"[DEBUG] CreateITapTradeAPI 异常: {e}")
            self._api = None
    
        err_code = iResult[0]
        print(f"[DEBUG] iResult={err_code}")
    
        if not self._api:
            try:
                err_desc = tdapi.GetITapErrorDescribe(err_code)
                print(f"[DEBUG] 错误描述={err_desc}")
            except Exception as e:
                print(f"[DEBUG] GetITapErrorDescribe 异常: {e}")
                err_desc = "N/A"

            print(f"创建交易API失败，错误码: {err_code}, 描述: {err_desc}")
            return False
    
        self._api.SetAPINotify(self)
        print("交易API创建成功")
        return True

    def setHostAddress(self, host, port):
        """设置服务器地址"""
        self._api.SetHostAddress(host, port)

    def login(self, auth):
        """登录"""
        req = tdapi.TapAPITradeLoginAuth()
        req.UserNo = auth.get("UserNo", "")
        req.Password = auth.get("Password", "")
        req.ISModifyPassword = auth.get("ISModifyPassword", "N")
        req.ISDDA = auth.get("ISDDA", "N")
        self._api.Login(req)

    def disconnect(self):
        """断开连接"""
        if self._api:
            self._api.Disconnect()

    def exit(self):
        """退出API"""
        if self._api:
            tdapi.FreeITapTradeAPI(self._api)
            self._api = None

    def qryAccount(self):
        """查询账户"""
        session_id = [0]
        self._api.QryAccount(session_id)

    def qryPosition(self):
        """查询持仓"""
        session_id = [0]
        self._api.QryPosition(session_id)

    def qryOrder(self):
        """查询委托"""
        session_id = [0]
        self._api.QryOrder(session_id)

    def insertOrder(self, order):
        """报单"""
        req = tdapi.TapAPINewOrder()
        req.OrderRef = order.get("OrderRef", "")
        req.AccountNo = order.get("AccountNo", "")
        req.ExchangeNo = order.get("ExchangeNo", "")
        req.CommodityType = order.get("CommodityType", "")
        req.CommodityNo = order.get("CommodityNo", "")
        req.ContractNo1 = order.get("ContractNo1", "")
        req.CallOrPutFlag1 = order.get("CallOrPutFlag1", "0")
        req.StrikePrice1 = order.get("StrikePrice1", "0")
        req.ContractNo2 = order.get("ContractNo2", "")
        req.CallOrPutFlag2 = order.get("CallOrPutFlag2", "0")
        req.StrikePrice2 = order.get("StrikePrice2", "0")
        req.OrderType = order.get("OrderType", "")
        req.OrderPrice = order.get("OrderPrice", "0")
        req.OrderQty = order.get("OrderQty", 0)
        req.OrderSide = order.get("OrderSide", "")
        req.PositionEffect = order.get("PositionEffect", "")
        req.HedgeFlag = order.get("HedgeFlag", "")
        req.TimeInForce = order.get("TimeInForce", "")
        req.StopPrice = order.get("StopPrice", "0")
        
        session_id = [0]
        self._api.InsertOrder(session_id, req)

    def cancelOrder(self, order):
        """撤单"""
        req = tdapi.TapAPIOrderCancelReq()
        req.OrderRef = order.get("OrderRef", "")
        req.ServerOrderID = order.get("ServerOrderID", "")
        
        session_id = [0]
        self._api.CancelOrder(session_id, req)

    def OnAPIReady(self):
        """API就绪"""
        print("交易API已就绪")
        self.connect_status = True

    def OnDisconnect(self, reason):
        """连接断开"""
        print(f"交易服务器连接断开，原因码：{reason}")
        self.connect_status = False
        self.login_status = False

    def OnRspLogin(self, errorCode, loginRspInfo):
        """登录响应"""
        if errorCode != 0:
            print(f"交易服务器登录失败，错误码：{errorCode}")
            self.login_status = False
        else:
            print("交易服务器登录成功")
            self.login_status = True
            self.connect_status = True

    def OnRtnAccount(self, account):
        """账户回报"""
        if account:
            print(f"账户回报: 账号={account.get('AccountNo', '')}, "
                  f"余额={account.get('Balance', 0)}, "
                  f"可用={account.get('Available', 0)}")

    def OnRtnPosition(self, position):
        """持仓回报"""
        if position:
            print(f"持仓回报: 合约={position.get('ContractNo', '')}, "
                  f"方向={position.get('PositionEffect', '')}, "
                  f"数量={position.get('PositionQty', 0)}")

    def OnRtnOrder(self, order):
        """委托回报"""
        if order:
            print(f"委托回报: 委托号={order.get('OrderRef', '')}, "
                  f"状态={order.get('OrderState', '')}, "
                  f"数量={order.get('OrderQty', 0)}")

    def OnRtnFill(self, fill):
        """成交回报"""
        if fill:
            print(f"成交回报: 委托号={fill.get('OrderRef', '')}, "
                  f"成交价={fill.get('MatchPrice', 0)}, "
                  f"成交量={fill.get('MatchQty', 0)}")


def main():
    """主函数"""
    config = {
        "host": "61.163.243.173",
        "port": 8383,
        "username": "",
        "password": "",
        "auth_code": "67EA896065459BECDFDB924B29CB7DF1946CED32E26C1EAC946CED32E26C1EAC946CED32E26C1EAC946CED32E26C1EAC09E90175BD6CC3F223D25C73D4646495946CED32E26C1EAC63FF7F329FA574E75D029CC71D67FCD4946CED32E26C1EACD33D6030790F8965ECC6DBD13654DBBB47D3EA0BF4E191F5B6283AFD517BCFF1515307896C6135B94367E24FD5E6D36F2667387F4BCF6E87B68877B14D02786846A25AA8D29ACBCD36579ACCA416C3065425C2C2C94B60617845C2CF151D1952B457B0653C26D4D35D7980DBDDBD9131B33410F3E56243148BD991DE4FBC2E524098CB9DD883D95C9CB00CC3ADF605B44F479609D204E725907C5A2FDDC498C1"
    }

    api = TapTradeApi()

    try:
        # 初始化API
        api.init()
        print("交易API初始化成功")

        # 创建API，使用auth_code
        req = {
            "AuthCode": config["auth_code"],
            "KeyOperationLogPath": "/tmp/tap_log",
            "LogLevel": "N",
            "APPID": "",  
        }
        if not api.createTapTradeAPI(req):
            print("交易API创建失败，无法继续测试")
            return

        # 设置服务器地址
        api.setHostAddress(config["host"], config["port"])
        print(f"设置交易服务器地址: {config['host']}:{config['port']}")

        # 登录
        auth = {
            "UserNo": config["username"],
            "Password": config["password"],
            "ISModifyPassword": "N",
            "ISDDA": "N"
        }
        api.login(auth)
        print(f"登录交易服务器: {config['username']}")

        # 等待连接和登录完成
        timeout = 10
        start_time = time.time()
        while not (api.connect_status and api.login_status):
            if time.time() - start_time > timeout:
                print("等待连接和登录超时")
                break
            time.sleep(0.5)

        if api.connect_status and api.login_status:
            print("交易服务器连接和登录成功")

            # 查询账户
            print("查询账户...")
            api.qryAccount()

            # 查询持仓
            print("查询持仓...")
            api.qryPosition()

            # 查询委托
            print("查询委托...")
            api.qryOrder()

            # 等待查询结果
            time.sleep(2)

        else:
            print("交易服务器连接或登录失败")

    except Exception as e:
        print(f"交易API测试失败: {e}")
        import traceback
        traceback.print_exc()

    finally:
        # 断开连接
        api.disconnect()
        print("断开交易服务器连接")

        # 退出API
        api.exit()
        print("退出交易API")


if __name__ == "__main__":
    main()