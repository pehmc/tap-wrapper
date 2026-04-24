#include "tapmd.h"


///-------------------------------------------------------------------------------------
///C++的回调函数将数据保存到队列中
///-------------------------------------------------------------------------------------

void MdApi::OnRspLogin(TAPIINT32 errorCode, const TapAPIQuotLoginRspInfo *info)
{
	Task task = Task();
	task.task_name = ONRSPLOGIN;
	task.task_error = errorCode;
	if (info) {
		task.task_data = new TapAPIQuotLoginRspInfo(*info);
	}
	this->task_queue.push(task);
};

void MdApi::OnAPIReady()
{
	Task task = Task();
	task.task_name = ONAPIREADY;
	this->task_queue.push(task);
};

void MdApi::OnDisconnect(TAPIINT32 reasonCode)
{
	Task task = Task();
	task.task_name = ONDISCONNECT;
	task.task_int = reasonCode;
	this->task_queue.push(task);
};

void MdApi::OnRspQryCommodity(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteCommodityInfo *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYCOMMODITY;
	task.task_id = sessionID;
	task.task_error = errorCode;
	task.task_last = isLast;
	if (info) {
		task.task_data = new TapAPIQuoteCommodityInfo(*info);
	}
	this->task_queue.push(task);
};

void MdApi::OnRspQryContract(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteContractInfo *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYCONTRACT;
	task.task_id = sessionID;
	task.task_error = errorCode;
	task.task_last = isLast;
	if (info) {
		task.task_data = new TapAPIQuoteContractInfo(*info);
	}
	this->task_queue.push(task);
};

void MdApi::OnRspSubscribeQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteWhole *info)
{
	Task task = Task();
	task.task_name = ONRSPSUBSCRIBEQUOTE;
	task.task_id = sessionID;
	task.task_error = errorCode;
	task.task_last = isLast;
	if (info) {
		task.task_data = new TapAPIQuoteWhole(*info);
	}
	this->task_queue.push(task);
};

void MdApi::OnRspUnSubscribeQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIContract *info)
{
	Task task = Task();
	task.task_name = ONRSPUNSUBSCRIBEQUOTE;
	task.task_id = sessionID;
	task.task_error = errorCode;
	task.task_last = isLast;
	if (info) {
		task.task_data = new TapAPIContract(*info);
	}
	this->task_queue.push(task);
};

void MdApi::OnRtnQuote(const TapAPIQuoteWhole *info)
{
	Task task = Task();
	task.task_name = ONRTNQUOTE;
	if (info) {
		task.task_data = new TapAPIQuoteWhole(*info);
	}
	this->task_queue.push(task);
};

///-------------------------------------------------------------------------------------
///工作线程从队列中取出数据，转化为python对象后，进行推送
///-------------------------------------------------------------------------------------

void MdApi::processTask()
{
    try
    {
        while (this->active)
        {
            Task task = this->task_queue.pop();
            switch (task.task_name)
            {
case ONRSPLOGIN:
{
	this->processRspLogin(&task);
	break;
}

case ONAPIREADY:
{
	this->processAPIReady(&task);
	break;
}

case ONDISCONNECT:
{
	this->processDisconnect(&task);
	break;
}

case ONRSPQRYCOMMODITY:
{
	this->processRspQryCommodity(&task);
	break;
}

case ONRSPQRYCONTRACT:
{
	this->processRspQryContract(&task);
	break;
}

case ONRSPSUBSCRIBEQUOTE:
{
	this->processRspSubscribeQuote(&task);
	break;
}

case ONRSPUNSUBSCRIBEQUOTE:
{
	this->processRspUnSubscribeQuote(&task);
	break;
}

case ONRTNQUOTE:
{
	this->processRtnQuote(&task);
	break;
}
            }
        }
    }
    catch (const TerminatedError&) {}
}

void MdApi::processRspLogin(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		TapAPIQuotLoginRspInfo *p = (TapAPIQuotLoginRspInfo*)task->task_data;
		info["UserNo"] = std::string(p->UserNo);
		info["UserType"] = p->UserType;
		info["UserName"] = std::string(p->UserName);
		info["QuoteTempPassword"] = std::string(p->QuoteTempPassword);
		info["ReservedInfo"] = std::string(p->ReservedInfo);
		info["LastLoginIP"] = std::string(p->LastLoginIP);
		info["LastLoginProt"] = p->LastLoginProt;
		info["LastLoginTime"] = std::string(p->LastLoginTime);
		info["LastLogoutTime"] = std::string(p->LastLogoutTime);
		info["TradeDate"] = std::string(p->TradeDate);
		info["LastSettleTime"] = std::string(p->LastSettleTime);
		info["StartTime"] = std::string(p->StartTime);
		info["InitTime"] = std::string(p->InitTime);
		delete p;
	}
	this->onRspLogin(task->task_error, info);
};

void MdApi::processAPIReady(Task *task)
{
	this->onAPIReady();
};

void MdApi::processDisconnect(Task *task)
{
	gil_scoped_acquire acquire;
	this->onDisconnect(task->task_int);
};

void MdApi::processRspQryCommodity(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		TapAPIQuoteCommodityInfo *p = (TapAPIQuoteCommodityInfo*)task->task_data;
		pybind11::dict info_Commodity_dict;
		info_Commodity_dict["ExchangeNo"] = std::string(p->Commodity.ExchangeNo);
		info_Commodity_dict["CommodityType"] = p->Commodity.CommodityType;
		info_Commodity_dict["CommodityNo"] = std::string(p->Commodity.CommodityNo);
		info["Commodity"] = info_Commodity_dict;
		info["CommodityName"] = std::string(p->CommodityName);
		info["CommodityEngName"] = std::string(p->CommodityEngName);
		info["ContractSize"] = p->ContractSize;
		info["CommodityTickSize"] = p->CommodityTickSize;
		info["CommodityDenominator"] = p->CommodityDenominator;
		info["CmbDirect"] = p->CmbDirect;
		info["CommodityContractLen"] = p->CommodityContractLen;
		info["IsDST"] = p->IsDST;
		pybind11::dict info_RelateCommodity1_dict;
		info_RelateCommodity1_dict["ExchangeNo"] = std::string(p->RelateCommodity1.ExchangeNo);
		info_RelateCommodity1_dict["CommodityType"] = p->RelateCommodity1.CommodityType;
		info_RelateCommodity1_dict["CommodityNo"] = std::string(p->RelateCommodity1.CommodityNo);
		info["RelateCommodity1"] = info_RelateCommodity1_dict;
		pybind11::dict info_RelateCommodity2_dict;
		info_RelateCommodity2_dict["ExchangeNo"] = std::string(p->RelateCommodity2.ExchangeNo);
		info_RelateCommodity2_dict["CommodityType"] = p->RelateCommodity2.CommodityType;
		info_RelateCommodity2_dict["CommodityNo"] = std::string(p->RelateCommodity2.CommodityNo);
		info["RelateCommodity2"] = info_RelateCommodity2_dict;
		delete p;
	}
	this->onRspQryCommodity(task->task_id, task->task_error, task->task_last, info);
};

void MdApi::processRspQryContract(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		TapAPIQuoteContractInfo *p = (TapAPIQuoteContractInfo*)task->task_data;
		pybind11::dict info_Contract_dict;
		pybind11::dict info_Contract_dict_Commodity_dict;
		info_Contract_dict_Commodity_dict["ExchangeNo"] = std::string(p->Contract.Commodity.ExchangeNo);
		info_Contract_dict_Commodity_dict["CommodityType"] = p->Contract.Commodity.CommodityType;
		info_Contract_dict_Commodity_dict["CommodityNo"] = std::string(p->Contract.Commodity.CommodityNo);
		info_Contract_dict["Commodity"] = info_Contract_dict_Commodity_dict;
		info_Contract_dict["ContractNo1"] = std::string(p->Contract.ContractNo1);
		info_Contract_dict["StrikePrice1"] = std::string(p->Contract.StrikePrice1);
		info_Contract_dict["CallOrPutFlag1"] = p->Contract.CallOrPutFlag1;
		info_Contract_dict["ContractNo2"] = std::string(p->Contract.ContractNo2);
		info_Contract_dict["StrikePrice2"] = std::string(p->Contract.StrikePrice2);
		info_Contract_dict["CallOrPutFlag2"] = p->Contract.CallOrPutFlag2;
		info["Contract"] = info_Contract_dict;
		info["ContractType"] = p->ContractType;
		info["QuoteUnderlyingContract"] = std::string(p->QuoteUnderlyingContract);
		info["ContractName"] = std::string(p->ContractName);
		info["ContractExpDate"] = std::string(p->ContractExpDate);
		info["LastTradeDate"] = std::string(p->LastTradeDate);
		info["FirstNoticeDate"] = std::string(p->FirstNoticeDate);
		delete p;
	}
	this->onRspQryContract(task->task_id, task->task_error, task->task_last, info);
};

void MdApi::processRspSubscribeQuote(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		TapAPIQuoteWhole *p = (TapAPIQuoteWhole*)task->task_data;
		pybind11::dict info_Contract_dict;
		pybind11::dict info_Contract_dict_Commodity_dict;
		info_Contract_dict_Commodity_dict["ExchangeNo"] = std::string(p->Contract.Commodity.ExchangeNo);
		info_Contract_dict_Commodity_dict["CommodityType"] = p->Contract.Commodity.CommodityType;
		info_Contract_dict_Commodity_dict["CommodityNo"] = std::string(p->Contract.Commodity.CommodityNo);
		info_Contract_dict["Commodity"] = info_Contract_dict_Commodity_dict;
		info_Contract_dict["ContractNo1"] = std::string(p->Contract.ContractNo1);
		info_Contract_dict["StrikePrice1"] = std::string(p->Contract.StrikePrice1);
		info_Contract_dict["CallOrPutFlag1"] = p->Contract.CallOrPutFlag1;
		info_Contract_dict["ContractNo2"] = std::string(p->Contract.ContractNo2);
		info_Contract_dict["StrikePrice2"] = std::string(p->Contract.StrikePrice2);
		info_Contract_dict["CallOrPutFlag2"] = p->Contract.CallOrPutFlag2;
		info["Contract"] = info_Contract_dict;
		info["CurrencyNo"] = std::string(p->CurrencyNo);
		info["TradingState"] = p->TradingState;
		info["DateTimeStamp"] = std::string(p->DateTimeStamp);
		info["QPreClosingPrice"] = p->QPreClosingPrice;
		info["QPreSettlePrice"] = p->QPreSettlePrice;
		info["QPrePositionQty"] = p->QPrePositionQty;
		info["QOpeningPrice"] = p->QOpeningPrice;
		info["QLastPrice"] = p->QLastPrice;
		info["QHighPrice"] = p->QHighPrice;
		info["QLowPrice"] = p->QLowPrice;
		info["QHisHighPrice"] = p->QHisHighPrice;
		info["QHisLowPrice"] = p->QHisLowPrice;
		info["QLimitUpPrice"] = p->QLimitUpPrice;
		info["QLimitDownPrice"] = p->QLimitDownPrice;
		info["QTotalQty"] = p->QTotalQty;
		info["QTotalTurnover"] = p->QTotalTurnover;
		info["QPositionQty"] = p->QPositionQty;
		info["QAveragePrice"] = p->QAveragePrice;
		info["QClosingPrice"] = p->QClosingPrice;
		info["QSettlePrice"] = p->QSettlePrice;
		info["QLastQty"] = p->QLastQty;
		info["QBidPrice"] = p->QBidPrice;
		info["QBidQty"] = p->QBidQty;
		info["QAskPrice"] = p->QAskPrice;
		info["QAskQty"] = p->QAskQty;
		info["QImpliedBidPrice"] = p->QImpliedBidPrice;
		info["QImpliedBidQty"] = p->QImpliedBidQty;
		info["QImpliedAskPrice"] = p->QImpliedAskPrice;
		info["QImpliedAskQty"] = p->QImpliedAskQty;
		info["QPreDelta"] = p->QPreDelta;
		info["QCurrDelta"] = p->QCurrDelta;
		info["QInsideQty"] = p->QInsideQty;
		info["QOutsideQty"] = p->QOutsideQty;
		info["QTurnoverRate"] = p->QTurnoverRate;
		info["Q5DAvgQty"] = p->Q5DAvgQty;
		info["QPERatio"] = p->QPERatio;
		info["QTotalValue"] = p->QTotalValue;
		info["QNegotiableValue"] = p->QNegotiableValue;
		info["QPositionTrend"] = p->QPositionTrend;
		info["QChangeSpeed"] = p->QChangeSpeed;
		info["QChangeRate"] = p->QChangeRate;
		info["QChangeValue"] = p->QChangeValue;
		info["QSwing"] = p->QSwing;
		info["QTotalBidQty"] = p->QTotalBidQty;
		info["QTotalAskQty"] = p->QTotalAskQty;
		pybind11::dict info_UnderlyContract_dict;
		pybind11::dict info_UnderlyContract_dict_Commodity_dict;
		info_UnderlyContract_dict_Commodity_dict["ExchangeNo"] = std::string(p->UnderlyContract.Commodity.ExchangeNo);
		info_UnderlyContract_dict_Commodity_dict["CommodityType"] = p->UnderlyContract.Commodity.CommodityType;
		info_UnderlyContract_dict_Commodity_dict["CommodityNo"] = std::string(p->UnderlyContract.Commodity.CommodityNo);
		info_UnderlyContract_dict["Commodity"] = info_UnderlyContract_dict_Commodity_dict;
		info_UnderlyContract_dict["ContractNo1"] = std::string(p->UnderlyContract.ContractNo1);
		info_UnderlyContract_dict["StrikePrice1"] = std::string(p->UnderlyContract.StrikePrice1);
		info_UnderlyContract_dict["CallOrPutFlag1"] = p->UnderlyContract.CallOrPutFlag1;
		info_UnderlyContract_dict["ContractNo2"] = std::string(p->UnderlyContract.ContractNo2);
		info_UnderlyContract_dict["StrikePrice2"] = std::string(p->UnderlyContract.StrikePrice2);
		info_UnderlyContract_dict["CallOrPutFlag2"] = p->UnderlyContract.CallOrPutFlag2;
		info["UnderlyContract"] = info_UnderlyContract_dict;
		delete p;
	}
	this->onRspSubscribeQuote(task->task_id, task->task_error, task->task_last, info);
};

void MdApi::processRspUnSubscribeQuote(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		TapAPIContract *p = (TapAPIContract*)task->task_data;
		pybind11::dict info_Commodity_dict;
		info_Commodity_dict["ExchangeNo"] = std::string(p->Commodity.ExchangeNo);
		info_Commodity_dict["CommodityType"] = p->Commodity.CommodityType;
		info_Commodity_dict["CommodityNo"] = std::string(p->Commodity.CommodityNo);
		info["Commodity"] = info_Commodity_dict;
		info["ContractNo1"] = std::string(p->ContractNo1);
		info["StrikePrice1"] = std::string(p->StrikePrice1);
		info["CallOrPutFlag1"] = p->CallOrPutFlag1;
		info["ContractNo2"] = std::string(p->ContractNo2);
		info["StrikePrice2"] = std::string(p->StrikePrice2);
		info["CallOrPutFlag2"] = p->CallOrPutFlag2;
		delete p;
	}
	this->onRspUnSubscribeQuote(task->task_id, task->task_error, task->task_last, info);
};

void MdApi::processRtnQuote(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		TapAPIQuoteWhole *p = (TapAPIQuoteWhole*)task->task_data;
		pybind11::dict info_Contract_dict;
		pybind11::dict info_Contract_dict_Commodity_dict;
		info_Contract_dict_Commodity_dict["ExchangeNo"] = std::string(p->Contract.Commodity.ExchangeNo);
		info_Contract_dict_Commodity_dict["CommodityType"] = p->Contract.Commodity.CommodityType;
		info_Contract_dict_Commodity_dict["CommodityNo"] = std::string(p->Contract.Commodity.CommodityNo);
		info_Contract_dict["Commodity"] = info_Contract_dict_Commodity_dict;
		info_Contract_dict["ContractNo1"] = std::string(p->Contract.ContractNo1);
		info_Contract_dict["StrikePrice1"] = std::string(p->Contract.StrikePrice1);
		info_Contract_dict["CallOrPutFlag1"] = p->Contract.CallOrPutFlag1;
		info_Contract_dict["ContractNo2"] = std::string(p->Contract.ContractNo2);
		info_Contract_dict["StrikePrice2"] = std::string(p->Contract.StrikePrice2);
		info_Contract_dict["CallOrPutFlag2"] = p->Contract.CallOrPutFlag2;
		info["Contract"] = info_Contract_dict;
		info["CurrencyNo"] = std::string(p->CurrencyNo);
		info["TradingState"] = p->TradingState;
		info["DateTimeStamp"] = std::string(p->DateTimeStamp);
		info["QPreClosingPrice"] = p->QPreClosingPrice;
		info["QPreSettlePrice"] = p->QPreSettlePrice;
		info["QPrePositionQty"] = p->QPrePositionQty;
		info["QOpeningPrice"] = p->QOpeningPrice;
		info["QLastPrice"] = p->QLastPrice;
		info["QHighPrice"] = p->QHighPrice;
		info["QLowPrice"] = p->QLowPrice;
		info["QHisHighPrice"] = p->QHisHighPrice;
		info["QHisLowPrice"] = p->QHisLowPrice;
		info["QLimitUpPrice"] = p->QLimitUpPrice;
		info["QLimitDownPrice"] = p->QLimitDownPrice;
		info["QTotalQty"] = p->QTotalQty;
		info["QTotalTurnover"] = p->QTotalTurnover;
		info["QPositionQty"] = p->QPositionQty;
		info["QAveragePrice"] = p->QAveragePrice;
		info["QClosingPrice"] = p->QClosingPrice;
		info["QSettlePrice"] = p->QSettlePrice;
		info["QLastQty"] = p->QLastQty;
		info["QBidPrice"] = p->QBidPrice;
		info["QBidQty"] = p->QBidQty;
		info["QAskPrice"] = p->QAskPrice;
		info["QAskQty"] = p->QAskQty;
		info["QImpliedBidPrice"] = p->QImpliedBidPrice;
		info["QImpliedBidQty"] = p->QImpliedBidQty;
		info["QImpliedAskPrice"] = p->QImpliedAskPrice;
		info["QImpliedAskQty"] = p->QImpliedAskQty;
		info["QPreDelta"] = p->QPreDelta;
		info["QCurrDelta"] = p->QCurrDelta;
		info["QInsideQty"] = p->QInsideQty;
		info["QOutsideQty"] = p->QOutsideQty;
		info["QTurnoverRate"] = p->QTurnoverRate;
		info["Q5DAvgQty"] = p->Q5DAvgQty;
		info["QPERatio"] = p->QPERatio;
		info["QTotalValue"] = p->QTotalValue;
		info["QNegotiableValue"] = p->QNegotiableValue;
		info["QPositionTrend"] = p->QPositionTrend;
		info["QChangeSpeed"] = p->QChangeSpeed;
		info["QChangeRate"] = p->QChangeRate;
		info["QChangeValue"] = p->QChangeValue;
		info["QSwing"] = p->QSwing;
		info["QTotalBidQty"] = p->QTotalBidQty;
		info["QTotalAskQty"] = p->QTotalAskQty;
		pybind11::dict info_UnderlyContract_dict;
		pybind11::dict info_UnderlyContract_dict_Commodity_dict;
		info_UnderlyContract_dict_Commodity_dict["ExchangeNo"] = std::string(p->UnderlyContract.Commodity.ExchangeNo);
		info_UnderlyContract_dict_Commodity_dict["CommodityType"] = p->UnderlyContract.Commodity.CommodityType;
		info_UnderlyContract_dict_Commodity_dict["CommodityNo"] = std::string(p->UnderlyContract.Commodity.CommodityNo);
		info_UnderlyContract_dict["Commodity"] = info_UnderlyContract_dict_Commodity_dict;
		info_UnderlyContract_dict["ContractNo1"] = std::string(p->UnderlyContract.ContractNo1);
		info_UnderlyContract_dict["StrikePrice1"] = std::string(p->UnderlyContract.StrikePrice1);
		info_UnderlyContract_dict["CallOrPutFlag1"] = p->UnderlyContract.CallOrPutFlag1;
		info_UnderlyContract_dict["ContractNo2"] = std::string(p->UnderlyContract.ContractNo2);
		info_UnderlyContract_dict["StrikePrice2"] = std::string(p->UnderlyContract.StrikePrice2);
		info_UnderlyContract_dict["CallOrPutFlag2"] = p->UnderlyContract.CallOrPutFlag2;
		info["UnderlyContract"] = info_UnderlyContract_dict;
		delete p;
	}
	this->onRtnQuote(info);
};

///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

int MdApi::setAPINotify()
{
	int i = this->api->SetAPINotify(this);
	return i;
};

int MdApi::setHostAddress(const string &IP, unsigned short port)
{
	int i = this->api->SetHostAddress(const_cast<char*>(IP.c_str()), port);
	return i;
};

int MdApi::login(const dict &loginAuth)
{
	TapAPIQuoteLoginAuth loginAuth_req = {};
	getString(loginAuth, "UserNo", loginAuth_req.UserNo);
	getChar(loginAuth, "ISModifyPassword", &loginAuth_req.ISModifyPassword);
	getString(loginAuth, "Password", loginAuth_req.Password);
	getString(loginAuth, "NewPassword", loginAuth_req.NewPassword);
	getString(loginAuth, "QuoteTempPassword", loginAuth_req.QuoteTempPassword);
	getChar(loginAuth, "ISDDA", &loginAuth_req.ISDDA);
	getString(loginAuth, "DDASerialNo", loginAuth_req.DDASerialNo);
	int i = this->api->Login(&loginAuth_req);
	return i;
};

int MdApi::disconnect()
{
	int i = this->api->Disconnect();
	return i;
};

int MdApi::qryCommodity()
{
	TAPIUINT32 session;
	int i = this->api->QryCommodity(&session);
	return i;
};

int MdApi::qryContract(const dict &qryReq)
{
	TAPIUINT32 session;
	TapAPICommodity qryReq_req = {};
	getString(qryReq, "ExchangeNo", qryReq_req.ExchangeNo);
	getChar(qryReq, "CommodityType", &qryReq_req.CommodityType);
	getString(qryReq, "CommodityNo", qryReq_req.CommodityNo);
	int i = this->api->QryContract(&session, &qryReq_req);
	return i;
};

int MdApi::subscribeQuote(const dict &contract)
{
	TAPIUINT32 session;
	TapAPIContract contract_req = {};
	// TODO: unsupported type "TapAPICommodity" for field "Commodity"
	getString(contract, "ContractNo1", contract_req.ContractNo1);
	getString(contract, "StrikePrice1", contract_req.StrikePrice1);
	getChar(contract, "CallOrPutFlag1", &contract_req.CallOrPutFlag1);
	getString(contract, "ContractNo2", contract_req.ContractNo2);
	getString(contract, "StrikePrice2", contract_req.StrikePrice2);
	getChar(contract, "CallOrPutFlag2", &contract_req.CallOrPutFlag2);
	int i = this->api->SubscribeQuote(&session, &contract_req);
	return i;
};

int MdApi::unSubscribeQuote(const dict &contract)
{
	TAPIUINT32 session;
	TapAPIContract contract_req = {};
	// TODO: unsupported type "TapAPICommodity" for field "Commodity"
	getString(contract, "ContractNo1", contract_req.ContractNo1);
	getString(contract, "StrikePrice1", contract_req.StrikePrice1);
	getChar(contract, "CallOrPutFlag1", &contract_req.CallOrPutFlag1);
	getString(contract, "ContractNo2", contract_req.ContractNo2);
	getString(contract, "StrikePrice2", contract_req.StrikePrice2);
	getChar(contract, "CallOrPutFlag2", &contract_req.CallOrPutFlag2);
	int i = this->api->UnSubscribeQuote(&session, &contract_req);
	return i;
};

int MdApi::createTapQuoteAPI(const dict &req)
                    {
                    TAPIINT32 iResult = 0;
                    TapAPIApplicationInfo appInfo;
                    memset(&appInfo, 0, sizeof(appInfo));
                    	getString(req, "AuthCode", appInfo.AuthCode);
	getString(req, "KeyOperationLogPath", appInfo.KeyOperationLogPath);

	this->api = CreateTapQuoteAPI(&appInfo, iResult);
                    	if (this->api)
                    	{
                    		this->api->SetAPINotify(this);
                    	}
                    	return iResult;
                    };
                    string MdApi::getTapQuoteAPIVersion()
                    {
                    const char *v = GetTapQuoteAPIVersion();
                    return std::string(v ? v : "");
                    };
                    int MdApi::setTapQuoteAPIDataPath(const string &path)
                    {
                    return SetTapQuoteAPIDataPath(path.c_str());
                    };
                    int MdApi::setTapQuoteAPILogLevel(int level)
                    {
                    return SetTapQuoteAPILogLevel(static_cast<TAPILOGLEVEL>(level));
                    };
                    void MdApi::init()
            {
            this->active = true;
            this->task_thread = thread(&MdApi::processTask, this);
            };

///-------------------------------------------------------------------------------------
///pybind11封装
///-------------------------------------------------------------------------------------

class PyMdApi : public MdApi
{
public:
    using MdApi::MdApi;

void onRspLogin(int errorCode, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspLogin, errorCode, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onAPIReady() override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onAPIReady);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onDisconnect(int reasonCode) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onDisconnect, reasonCode);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryCommodity(unsigned int sessionID, int errorCode, char isLast, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspQryCommodity, sessionID, errorCode, isLast, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryContract(unsigned int sessionID, int errorCode, char isLast, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspQryContract, sessionID, errorCode, isLast, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSubscribeQuote(unsigned int sessionID, int errorCode, char isLast, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspSubscribeQuote, sessionID, errorCode, isLast, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspUnSubscribeQuote(unsigned int sessionID, int errorCode, char isLast, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspUnSubscribeQuote, sessionID, errorCode, isLast, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnQuote(const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRtnQuote, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};
};

PYBIND11_MODULE(tapmd, m)
{
// TODO: FreeTapQuoteAPI has parameters, manual binding recommended
	// m.def("freeTapQuoteAPI", &FreeTapQuoteAPI);
    class_<MdApi, PyMdApi> tapmd(m, "MdApi", module_local());
    tapmd
        .def(init<>())
.def("setAPINotify", &MdApi::setAPINotify)
	.def("setHostAddress", &MdApi::setHostAddress)
	.def("login", &MdApi::login)
	.def("disconnect", &MdApi::disconnect)
	.def("qryCommodity", &MdApi::qryCommodity)
	.def("qryContract", &MdApi::qryContract)
	.def("subscribeQuote", &MdApi::subscribeQuote)
	.def("unSubscribeQuote", &MdApi::unSubscribeQuote)

	.def("onRspLogin", &MdApi::onRspLogin)
	.def("onAPIReady", &MdApi::onAPIReady)
	.def("onDisconnect", &MdApi::onDisconnect)
	.def("onRspQryCommodity", &MdApi::onRspQryCommodity)
	.def("onRspQryContract", &MdApi::onRspQryContract)
	.def("onRspSubscribeQuote", &MdApi::onRspSubscribeQuote)
	.def("onRspUnSubscribeQuote", &MdApi::onRspUnSubscribeQuote)
	.def("onRtnQuote", &MdApi::onRtnQuote)

	.def("createTapQuoteAPI", &MdApi::createTapQuoteAPI)
	.def("getTapQuoteAPIVersion", &MdApi::getTapQuoteAPIVersion)
	.def("setTapQuoteAPIDataPath", &MdApi::setTapQuoteAPIDataPath)
	.def("setTapQuoteAPILogLevel", &MdApi::setTapQuoteAPILogLevel)
	.def("init", &MdApi::init)
;
}