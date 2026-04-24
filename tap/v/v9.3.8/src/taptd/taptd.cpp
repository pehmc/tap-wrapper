#include "taptd.h"

using namespace ITapTrade;

///-------------------------------------------------------------------------------------
///C++的回调函数将数据保存到队列中
///-------------------------------------------------------------------------------------

void TdApi::OnConnect(const ITapTrade::TAPISTR_40 HostAddress)
{
	Task task = Task();
	task.task_name = ONCONNECT;
	task.task_string = std::string(HostAddress);
	this->task_queue.push(task);
};

void TdApi::OnRspLogin(ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPITradeLoginRspInfo *loginRspInfo)
{
	Task task = Task();
	task.task_name = ONRSPLOGIN;
	task.task_error = errorCode;
	if (loginRspInfo) {
		task.task_data = new ITapTrade::TapAPITradeLoginRspInfo(*loginRspInfo);
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnContactInfo(ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TAPISTR_40 ContactInfo)
{
	Task task = Task();
	task.task_name = ONRTNCONTACTINFO;
	task.task_error = errorCode;
	task.task_last = isLast;
	task.task_string = std::string(ContactInfo);
	this->task_queue.push(task);
};

void TdApi::OnRspRequestVertificateCode(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const TapAPIRequestVertificateCodeRsp *rsp)
{
	Task task = Task();
	task.task_name = ONRSPREQUESTVERTIFICATECODE;
	task.task_id = sessionID;
	task.task_error = errorCode;
	if (rsp) {
		task.task_data = new ITapTrade::TapAPIRequestVertificateCodeRsp(*rsp);
	}
	this->task_queue.push(task);
};

void TdApi::OnExpriationDate(ITapTrade::TAPIDATE date, int days)
{
	Task task = Task();
	task.task_name = ONEXPRIATIONDATE;
	task.task_string = std::string(date);
	task.task_int = days;
	this->task_queue.push(task);
};

void TdApi::OnAPIReady(ITapTrade::TAPIINT32 errorCode)
{
	Task task = Task();
	task.task_name = ONAPIREADY;
	task.task_error = errorCode;
	this->task_queue.push(task);
};

void TdApi::OnDisconnect(ITapTrade::TAPIINT32 reasonCode)
{
	Task task = Task();
	task.task_name = ONDISCONNECT;
	task.task_int = reasonCode;
	this->task_queue.push(task);
};

void TdApi::OnRspChangePassword(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode)
{
	Task task = Task();
	task.task_name = ONRSPCHANGEPASSWORD;
	task.task_id = sessionID;
	task.task_error = errorCode;
	this->task_queue.push(task);
};

void TdApi::OnRspAuthPassword(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode)
{
	Task task = Task();
	task.task_name = ONRSPAUTHPASSWORD;
	task.task_id = sessionID;
	task.task_error = errorCode;
	this->task_queue.push(task);
};

void TdApi::OnRspQryTradingDate(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPITradingCalendarQryRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYTRADINGDATE;
	task.task_id = sessionID;
	task.task_error = errorCode;
	if (info) {
		task.task_data = new ITapTrade::TapAPITradingCalendarQryRsp(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspSetReservedInfo(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TAPISTR_50 info)
{
	Task task = Task();
	task.task_name = ONRSPSETRESERVEDINFO;
	task.task_id = sessionID;
	task.task_error = errorCode;
	task.task_string = std::string(info);
	this->task_queue.push(task);
};

void TdApi::OnRspQryAccount(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIUINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountInfo *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYACCOUNT;
	task.task_id = sessionID;
	task.task_error = errorCode;
	task.task_last = isLast;
	if (info) {
		task.task_data = new ITapTrade::TapAPIAccountInfo(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryFund(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIFundData *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYFUND;
	task.task_id = sessionID;
	task.task_error = errorCode;
	task.task_last = isLast;
	if (info) {
		task.task_data = new ITapTrade::TapAPIFundData(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnFund(const ITapTrade::TapAPIFundData *info)
{
	Task task = Task();
	task.task_name = ONRTNFUND;
	if (info) {
		task.task_data = new ITapTrade::TapAPIFundData(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryExchange(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIExchangeInfo *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYEXCHANGE;
	task.task_id = sessionID;
	task.task_error = errorCode;
	task.task_last = isLast;
	if (info) {
		task.task_data = new ITapTrade::TapAPIExchangeInfo(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryCommodity(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPICommodityInfo *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYCOMMODITY;
	task.task_id = sessionID;
	task.task_error = errorCode;
	task.task_last = isLast;
	if (info) {
		task.task_data = new ITapTrade::TapAPICommodityInfo(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryContract(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPITradeContractInfo *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYCONTRACT;
	task.task_id = sessionID;
	task.task_error = errorCode;
	task.task_last = isLast;
	if (info) {
		task.task_data = new ITapTrade::TapAPITradeContractInfo(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnContract(const ITapTrade::TapAPITradeContractInfo *info)
{
	Task task = Task();
	task.task_name = ONRTNCONTRACT;
	if (info) {
		task.task_data = new ITapTrade::TapAPITradeContractInfo(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspOrderAction(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderActionRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPORDERACTION;
	task.task_id = sessionID;
	task.task_error = errorCode;
	if (info) {
		task.task_data = new ITapTrade::TapAPIOrderActionRsp(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnOrder(const ITapTrade::TapAPIOrderInfoNotice *info)
{
	Task task = Task();
	task.task_name = ONRTNORDER;
	if (info) {
		task.task_data = new ITapTrade::TapAPIOrderInfoNotice(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryOrder(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIOrderInfo *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYORDER;
	task.task_id = sessionID;
	task.task_error = errorCode;
	task.task_last = isLast;
	if (info) {
		task.task_data = new ITapTrade::TapAPIOrderInfo(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryOrderProcess(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIOrderInfo *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYORDERPROCESS;
	task.task_id = sessionID;
	task.task_error = errorCode;
	task.task_last = isLast;
	if (info) {
		task.task_data = new ITapTrade::TapAPIOrderInfo(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryFill(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIFillInfo *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYFILL;
	task.task_id = sessionID;
	task.task_error = errorCode;
	task.task_last = isLast;
	if (info) {
		task.task_data = new ITapTrade::TapAPIFillInfo(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnFill(const ITapTrade::TapAPIFillInfo *info)
{
	Task task = Task();
	task.task_name = ONRTNFILL;
	if (info) {
		task.task_data = new ITapTrade::TapAPIFillInfo(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryPosition(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIPositionInfo *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYPOSITION;
	task.task_id = sessionID;
	task.task_error = errorCode;
	task.task_last = isLast;
	if (info) {
		task.task_data = new ITapTrade::TapAPIPositionInfo(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnPosition(const ITapTrade::TapAPIPositionInfo *info)
{
	Task task = Task();
	task.task_name = ONRTNPOSITION;
	if (info) {
		task.task_data = new ITapTrade::TapAPIPositionInfo(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryPositionSummary(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIPositionSummary *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYPOSITIONSUMMARY;
	task.task_id = sessionID;
	task.task_error = errorCode;
	task.task_last = isLast;
	if (info) {
		task.task_data = new ITapTrade::TapAPIPositionSummary(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnPositionSummary(const TapAPIPositionSummary *info)
{
	Task task = Task();
	task.task_name = ONRTNPOSITIONSUMMARY;
	if (info) {
		task.task_data = new ITapTrade::TapAPIPositionSummary(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnPositionProfit(const ITapTrade::TapAPIPositionProfitNotice *info)
{
	Task task = Task();
	task.task_name = ONRTNPOSITIONPROFIT;
	if (info) {
		task.task_data = new ITapTrade::TapAPIPositionProfitNotice(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryCurrency(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPICurrencyInfo *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYCURRENCY;
	task.task_id = sessionID;
	task.task_error = errorCode;
	task.task_last = isLast;
	if (info) {
		task.task_data = new ITapTrade::TapAPICurrencyInfo(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryTradeMessage(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPITradeMessage *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYTRADEMESSAGE;
	task.task_id = sessionID;
	task.task_error = errorCode;
	task.task_last = isLast;
	if (info) {
		task.task_data = new ITapTrade::TapAPITradeMessage(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnTradeMessage(const ITapTrade::TapAPITradeMessage *info)
{
	Task task = Task();
	task.task_name = ONRTNTRADEMESSAGE;
	if (info) {
		task.task_data = new ITapTrade::TapAPITradeMessage(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryHisOrder(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisOrderQryRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYHISORDER;
	task.task_id = sessionID;
	task.task_error = errorCode;
	task.task_last = isLast;
	if (info) {
		task.task_data = new ITapTrade::TapAPIHisOrderQryRsp(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryHisOrderProcess(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisOrderProcessQryRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYHISORDERPROCESS;
	task.task_id = sessionID;
	task.task_error = errorCode;
	task.task_last = isLast;
	if (info) {
		task.task_data = new ITapTrade::TapAPIHisOrderQryRsp(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryHisMatch(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisMatchQryRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYHISMATCH;
	task.task_id = sessionID;
	task.task_error = errorCode;
	task.task_last = isLast;
	if (info) {
		task.task_data = new ITapTrade::TapAPIHisMatchQryRsp(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryHisPosition(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisPositionQryRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYHISPOSITION;
	task.task_id = sessionID;
	task.task_error = errorCode;
	task.task_last = isLast;
	if (info) {
		task.task_data = new ITapTrade::TapAPIHisPositionQryRsp(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryHisDelivery(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisDeliveryQryRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYHISDELIVERY;
	task.task_id = sessionID;
	task.task_error = errorCode;
	task.task_last = isLast;
	if (info) {
		task.task_data = new ITapTrade::TapAPIHisDeliveryQryRsp(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryHisFund(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisFundQryRsp* info)
{
	Task task = Task();
	task.task_name = ONRSPQRYHISFUND;
	task.task_id = sessionID;
	task.task_error = errorCode;
	task.task_last = isLast;
	if (info) {
		task.task_data = new ITapTrade::TapAPIHisFundQryRsp(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryAccountCashAdjust(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountCashAdjustQryRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYACCOUNTCASHADJUST;
	task.task_id = sessionID;
	task.task_error = errorCode;
	task.task_last = isLast;
	if (info) {
		task.task_data = new ITapTrade::TapAPIAccountCashAdjustQryRsp(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryBill(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIBillQryRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYBILL;
	task.task_id = sessionID;
	task.task_error = errorCode;
	task.task_last = isLast;
	if (info) {
		task.task_data = new ITapTrade::TapAPIBillQryRsp(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryAccountFeeRent(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountFeeRentQryRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYACCOUNTFEERENT;
	task.task_id = sessionID;
	task.task_error = errorCode;
	task.task_last = isLast;
	if (info) {
		task.task_data = new ITapTrade::TapAPIAccountFeeRentQryRsp(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryAccountMarginRent(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountMarginRentQryRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYACCOUNTMARGINRENT;
	task.task_id = sessionID;
	task.task_error = errorCode;
	task.task_last = isLast;
	if (info) {
		task.task_data = new ITapTrade::TapAPIAccountMarginRentQryRsp(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspHKMarketOrderInsert(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderMarketInsertRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPHKMARKETORDERINSERT;
	task.task_id = sessionID;
	task.task_error = errorCode;
	if (info) {
		task.task_data = new ITapTrade::TapAPIOrderMarketInsertRsp(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspHKMarketOrderDelete(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderMarketDeleteRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPHKMARKETORDERDELETE;
	task.task_id = sessionID;
	task.task_error = errorCode;
	if (info) {
		task.task_data = new ITapTrade::TapAPIOrderMarketInsertRsp(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnHKMarketQuoteNotice(const ITapTrade::TapAPIOrderQuoteMarketNotice *info)
{
	Task task = Task();
	task.task_name = ONHKMARKETQUOTENOTICE;
	if (info) {
		task.task_data = new ITapTrade::TapAPIOrderQuoteMarketNotice(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspOrderLocalRemove(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderLocalRemoveRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPORDERLOCALREMOVE;
	task.task_id = sessionID;
	task.task_error = errorCode;
	if (info) {
		task.task_data = new ITapTrade::TapAPIOrderLocalRemoveRsp(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspOrderLocalInput(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderLocalInputRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPORDERLOCALINPUT;
	task.task_id = sessionID;
	task.task_error = errorCode;
	if (info) {
		task.task_data = new ITapTrade::TapAPIOrderInfo(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspOrderLocalModify(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderLocalModifyRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPORDERLOCALMODIFY;
	task.task_id = sessionID;
	task.task_error = errorCode;
	if (info) {
		task.task_data = new ITapTrade::TapAPIOrderInfo(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspOrderLocalTransfer(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderLocalTransferRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPORDERLOCALTRANSFER;
	task.task_id = sessionID;
	task.task_error = errorCode;
	if (info) {
		task.task_data = new ITapTrade::TapAPIOrderInfo(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspFillLocalInput(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIFillLocalInputRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPFILLLOCALINPUT;
	task.task_id = sessionID;
	task.task_error = errorCode;
	if (info) {
		task.task_data = new ITapTrade::TapAPIFillLocalInputReq(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspFillLocalRemove(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIFillLocalRemoveRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPFILLLOCALREMOVE;
	task.task_id = sessionID;
	task.task_error = errorCode;
	if (info) {
		task.task_data = new ITapTrade::TapAPIFillLocalRemoveReq(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQrySpotLock(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPISpotLockDataRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYSPOTLOCK;
	task.task_id = sessionID;
	task.task_error = errorCode;
	task.task_last = isLast;
	if (info) {
		task.task_data = new ITapTrade::TapAPISpotLockDataRsp(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnSpotLock(const ITapTrade::TapAPISpotLockDataRsp *info)
{
	Task task = Task();
	task.task_name = ONRTNSPOTLOCK;
	if (info) {
		task.task_data = new ITapTrade::TapAPISpotLockDataRsp(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspSubmitUserLoginInfo(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPISubmitUserLoginRspInfo * info)
{
	Task task = Task();
	task.task_name = ONRSPSUBMITUSERLOGININFO;
	task.task_id = sessionID;
	task.task_error = errorCode;
	task.task_last = isLast;
	if (info) {
		task.task_data = new ITapTrade::TapAPISubmitUserLoginRspInfo(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspSpecialOrderAction(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPISpecialOrderInfo *info)
{
	Task task = Task();
	task.task_name = ONRSPSPECIALORDERACTION;
	task.task_id = sessionID;
	task.task_error = errorCode;
	if (info) {
		task.task_data = new ITapTrade::TapAPISpecialOrderInfo(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnSpecialOrder(const ITapTrade::TapAPISpecialOrderInfo *info)
{
	Task task = Task();
	task.task_name = ONRTNSPECIALORDER;
	if (info) {
		task.task_data = new ITapTrade::TapAPISpecialOrderInfo(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQrySpecialOrder(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPISpecialOrderInfo *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYSPECIALORDER;
	task.task_id = sessionID;
	task.task_error = errorCode;
	task.task_last = isLast;
	if (info) {
		task.task_data = new ITapTrade::TapAPISpecialOrderInfo(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryCombinePosition(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const  ITapTrade::TapAPICombinePositionInfo *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYCOMBINEPOSITION;
	task.task_id = sessionID;
	task.task_error = errorCode;
	task.task_last = isLast;
	if (info) {
		task.task_data = new ITapTrade::TapAPICombinePositionInfo(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnCombinePosition(const ITapTrade::TapAPICombinePositionInfo *info)
{
	Task task = Task();
	task.task_name = ONRTNCOMBINEPOSITION;
	if (info) {
		task.task_data = new ITapTrade::TapAPICombinePositionInfo(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryUserTrustDevice(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const  ITapTrade::TapAPIUserTrustDeviceQryRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYUSERTRUSTDEVICE;
	task.task_id = sessionID;
	task.task_error = errorCode;
	task.task_last = isLast;
	if (info) {
		task.task_data = new ITapTrade::TapAPIUserTrustDeviceQryRsp(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspAddUserTrustDevice(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIUserTrustDeviceAddRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPADDUSERTRUSTDEVICE;
	task.task_id = sessionID;
	task.task_error = errorCode;
	if (info) {
		task.task_data = new ITapTrade::TapAPIUserTrustDeviceQryRsp(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspDelUserTrustDevice(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIUserTrustDeviceDelRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPDELUSERTRUSTDEVICE;
	task.task_id = sessionID;
	task.task_error = errorCode;
	if (info) {
		task.task_data = new ITapTrade::TapAPIUserTrustDeviceDelReq(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnAddUserTrustDevice(const ITapTrade::TapAPIUserTrustDeviceAddRsp *info)
{
	Task task = Task();
	task.task_name = ONRTNADDUSERTRUSTDEVICE;
	if (info) {
		task.task_data = new ITapTrade::TapAPIUserTrustDeviceQryRsp(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnDelUserTrustDevice(const ITapTrade::TapAPIUserTrustDeviceDelRsp *info)
{
	Task task = Task();
	task.task_name = ONRTNDELUSERTRUSTDEVICE;
	if (info) {
		task.task_data = new ITapTrade::TapAPIUserTrustDeviceDelReq(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryIPOInfo(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIIPOInfoQryRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYIPOINFO;
	task.task_id = sessionID;
	task.task_error = errorCode;
	task.task_last = isLast;
	if (info) {
		task.task_data = new ITapTrade::TapAPIIPOInfoQryRsp(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryIPOStockQty(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAvailableApplyQryRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYIPOSTOCKQTY;
	task.task_id = sessionID;
	task.task_error = errorCode;
	task.task_last = isLast;
	if (info) {
		task.task_data = new ITapTrade::TapAPIAvailableApplyQryRsp(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryAccountIPO(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountIPOQryRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYACCOUNTIPO;
	task.task_id = sessionID;
	task.task_error = errorCode;
	task.task_last = isLast;
	if (info) {
		task.task_data = new ITapTrade::TapAPIAccountIPOQryRsp(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspAddAccountIPO(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIAccountIPOAddRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPADDACCOUNTIPO;
	task.task_id = sessionID;
	task.task_error = errorCode;
	if (info) {
		task.task_data = new ITapTrade::TapAPIAccountIPOQryRsp(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspCancelAccountIPO(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIAccountIPOCancelRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPCANCELACCOUNTIPO;
	task.task_id = sessionID;
	task.task_error = errorCode;
	if (info) {
		task.task_data = new ITapTrade::TapAPIAccountIPOQryRsp(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnAddAccountIPO(const ITapTrade::TapAPIAccountIPOAddNotice *info)
{
	Task task = Task();
	task.task_name = ONRTNADDACCOUNTIPO;
	if (info) {
		task.task_data = new ITapTrade::TapAPIAccountIPOQryRsp(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnCancelAccountIPO(const ITapTrade::TapAPIAccountIPOCancelNotice *info)
{
	Task task = Task();
	task.task_name = ONRTNCANCELACCOUNTIPO;
	if (info) {
		task.task_data = new ITapTrade::TapAPIAccountIPOQryRsp(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRspSelfPasswordInfoOperate(ITapTrade::TAPIINT32 errorCode)
{
	Task task = Task();
	task.task_name = ONRSPSELFPASSWORDINFOOPERATE;
	task.task_error = errorCode;
	this->task_queue.push(task);
};

void TdApi::OnRspVerificateIdentityInfo(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode)
{
	Task task = Task();
	task.task_name = ONRSPVERIFICATEIDENTITYINFO;
	task.task_id = sessionID;
	task.task_error = errorCode;
	this->task_queue.push(task);
};

void TdApi::OnRspSetVertificateCode(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode)
{
	Task task = Task();
	task.task_name = ONRSPSETVERTIFICATECODE;
	task.task_id = sessionID;
	task.task_error = errorCode;
	this->task_queue.push(task);
};

void TdApi::OnRspResetPassword(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode)
{
	Task task = Task();
	task.task_name = ONRSPRESETPASSWORD;
	task.task_id = sessionID;
	task.task_error = errorCode;
	this->task_queue.push(task);
};

void TdApi::OnRspQryExchangeStateInfo(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIExchangeStateInfoQryRsp* info)
{
	Task task = Task();
	task.task_name = ONRSPQRYEXCHANGESTATEINFO;
	task.task_id = sessionID;
	task.task_error = errorCode;
	task.task_last = isLast;
	if (info) {
		task.task_data = new ITapTrade::TapAPIExchangeStateInfoQryRsp(*info);
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnExchangeStateInfo(const ITapTrade::TapAPIExchangeStateInfoAddNotice* info)
{
	Task task = Task();
	task.task_name = ONRTNEXCHANGESTATEINFO;
	if (info) {
		task.task_data = new ITapTrade::TapAPIExchangeStateInfoQryRsp(*info);
	}
	this->task_queue.push(task);
};

///-------------------------------------------------------------------------------------
///工作线程从队列中取出数据，转化为python对象后，进行推送
///-------------------------------------------------------------------------------------

void TdApi::processTask()
{
    try
    {
        while (this->active)
        {
            Task task = this->task_queue.pop();
            switch (task.task_name)
            {
case ONCONNECT:
{
	this->processConnect(&task);
	break;
}

case ONRSPLOGIN:
{
	this->processRspLogin(&task);
	break;
}

case ONRTNCONTACTINFO:
{
	this->processRtnContactInfo(&task);
	break;
}

case ONRSPREQUESTVERTIFICATECODE:
{
	this->processRspRequestVertificateCode(&task);
	break;
}

case ONEXPRIATIONDATE:
{
	this->processExpriationDate(&task);
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

case ONRSPCHANGEPASSWORD:
{
	this->processRspChangePassword(&task);
	break;
}

case ONRSPAUTHPASSWORD:
{
	this->processRspAuthPassword(&task);
	break;
}

case ONRSPQRYTRADINGDATE:
{
	this->processRspQryTradingDate(&task);
	break;
}

case ONRSPSETRESERVEDINFO:
{
	this->processRspSetReservedInfo(&task);
	break;
}

case ONRSPQRYACCOUNT:
{
	this->processRspQryAccount(&task);
	break;
}

case ONRSPQRYFUND:
{
	this->processRspQryFund(&task);
	break;
}

case ONRTNFUND:
{
	this->processRtnFund(&task);
	break;
}

case ONRSPQRYEXCHANGE:
{
	this->processRspQryExchange(&task);
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

case ONRTNCONTRACT:
{
	this->processRtnContract(&task);
	break;
}

case ONRSPORDERACTION:
{
	this->processRspOrderAction(&task);
	break;
}

case ONRTNORDER:
{
	this->processRtnOrder(&task);
	break;
}

case ONRSPQRYORDER:
{
	this->processRspQryOrder(&task);
	break;
}

case ONRSPQRYORDERPROCESS:
{
	this->processRspQryOrderProcess(&task);
	break;
}

case ONRSPQRYFILL:
{
	this->processRspQryFill(&task);
	break;
}

case ONRTNFILL:
{
	this->processRtnFill(&task);
	break;
}

case ONRSPQRYPOSITION:
{
	this->processRspQryPosition(&task);
	break;
}

case ONRTNPOSITION:
{
	this->processRtnPosition(&task);
	break;
}

case ONRSPQRYPOSITIONSUMMARY:
{
	this->processRspQryPositionSummary(&task);
	break;
}

case ONRTNPOSITIONSUMMARY:
{
	this->processRtnPositionSummary(&task);
	break;
}

case ONRTNPOSITIONPROFIT:
{
	this->processRtnPositionProfit(&task);
	break;
}

case ONRSPQRYCURRENCY:
{
	this->processRspQryCurrency(&task);
	break;
}

case ONRSPQRYTRADEMESSAGE:
{
	this->processRspQryTradeMessage(&task);
	break;
}

case ONRTNTRADEMESSAGE:
{
	this->processRtnTradeMessage(&task);
	break;
}

case ONRSPQRYHISORDER:
{
	this->processRspQryHisOrder(&task);
	break;
}

case ONRSPQRYHISORDERPROCESS:
{
	this->processRspQryHisOrderProcess(&task);
	break;
}

case ONRSPQRYHISMATCH:
{
	this->processRspQryHisMatch(&task);
	break;
}

case ONRSPQRYHISPOSITION:
{
	this->processRspQryHisPosition(&task);
	break;
}

case ONRSPQRYHISDELIVERY:
{
	this->processRspQryHisDelivery(&task);
	break;
}

case ONRSPQRYHISFUND:
{
	this->processRspQryHisFund(&task);
	break;
}

case ONRSPQRYACCOUNTCASHADJUST:
{
	this->processRspQryAccountCashAdjust(&task);
	break;
}

case ONRSPQRYBILL:
{
	this->processRspQryBill(&task);
	break;
}

case ONRSPQRYACCOUNTFEERENT:
{
	this->processRspQryAccountFeeRent(&task);
	break;
}

case ONRSPQRYACCOUNTMARGINRENT:
{
	this->processRspQryAccountMarginRent(&task);
	break;
}

case ONRSPHKMARKETORDERINSERT:
{
	this->processRspHKMarketOrderInsert(&task);
	break;
}

case ONRSPHKMARKETORDERDELETE:
{
	this->processRspHKMarketOrderDelete(&task);
	break;
}

case ONHKMARKETQUOTENOTICE:
{
	this->processHKMarketQuoteNotice(&task);
	break;
}

case ONRSPORDERLOCALREMOVE:
{
	this->processRspOrderLocalRemove(&task);
	break;
}

case ONRSPORDERLOCALINPUT:
{
	this->processRspOrderLocalInput(&task);
	break;
}

case ONRSPORDERLOCALMODIFY:
{
	this->processRspOrderLocalModify(&task);
	break;
}

case ONRSPORDERLOCALTRANSFER:
{
	this->processRspOrderLocalTransfer(&task);
	break;
}

case ONRSPFILLLOCALINPUT:
{
	this->processRspFillLocalInput(&task);
	break;
}

case ONRSPFILLLOCALREMOVE:
{
	this->processRspFillLocalRemove(&task);
	break;
}

case ONRSPQRYSPOTLOCK:
{
	this->processRspQrySpotLock(&task);
	break;
}

case ONRTNSPOTLOCK:
{
	this->processRtnSpotLock(&task);
	break;
}

case ONRSPSUBMITUSERLOGININFO:
{
	this->processRspSubmitUserLoginInfo(&task);
	break;
}

case ONRSPSPECIALORDERACTION:
{
	this->processRspSpecialOrderAction(&task);
	break;
}

case ONRTNSPECIALORDER:
{
	this->processRtnSpecialOrder(&task);
	break;
}

case ONRSPQRYSPECIALORDER:
{
	this->processRspQrySpecialOrder(&task);
	break;
}

case ONRSPQRYCOMBINEPOSITION:
{
	this->processRspQryCombinePosition(&task);
	break;
}

case ONRTNCOMBINEPOSITION:
{
	this->processRtnCombinePosition(&task);
	break;
}

case ONRSPQRYUSERTRUSTDEVICE:
{
	this->processRspQryUserTrustDevice(&task);
	break;
}

case ONRSPADDUSERTRUSTDEVICE:
{
	this->processRspAddUserTrustDevice(&task);
	break;
}

case ONRSPDELUSERTRUSTDEVICE:
{
	this->processRspDelUserTrustDevice(&task);
	break;
}

case ONRTNADDUSERTRUSTDEVICE:
{
	this->processRtnAddUserTrustDevice(&task);
	break;
}

case ONRTNDELUSERTRUSTDEVICE:
{
	this->processRtnDelUserTrustDevice(&task);
	break;
}

case ONRSPQRYIPOINFO:
{
	this->processRspQryIPOInfo(&task);
	break;
}

case ONRSPQRYIPOSTOCKQTY:
{
	this->processRspQryIPOStockQty(&task);
	break;
}

case ONRSPQRYACCOUNTIPO:
{
	this->processRspQryAccountIPO(&task);
	break;
}

case ONRSPADDACCOUNTIPO:
{
	this->processRspAddAccountIPO(&task);
	break;
}

case ONRSPCANCELACCOUNTIPO:
{
	this->processRspCancelAccountIPO(&task);
	break;
}

case ONRTNADDACCOUNTIPO:
{
	this->processRtnAddAccountIPO(&task);
	break;
}

case ONRTNCANCELACCOUNTIPO:
{
	this->processRtnCancelAccountIPO(&task);
	break;
}

case ONRSPSELFPASSWORDINFOOPERATE:
{
	this->processRspSelfPasswordInfoOperate(&task);
	break;
}

case ONRSPVERIFICATEIDENTITYINFO:
{
	this->processRspVerificateIdentityInfo(&task);
	break;
}

case ONRSPSETVERTIFICATECODE:
{
	this->processRspSetVertificateCode(&task);
	break;
}

case ONRSPRESETPASSWORD:
{
	this->processRspResetPassword(&task);
	break;
}

case ONRSPQRYEXCHANGESTATEINFO:
{
	this->processRspQryExchangeStateInfo(&task);
	break;
}

case ONRTNEXCHANGESTATEINFO:
{
	this->processRtnExchangeStateInfo(&task);
	break;
}
            }
        }
    }
    catch (const TerminatedError&) {}
}

void TdApi::processConnect(Task *task)
{
	gil_scoped_acquire acquire;
	this->onConnect(task->task_string);
};

void TdApi::processRspLogin(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict loginRspInfo;
	if (task->task_data) {
		ITapTrade::TapAPITradeLoginRspInfo *p = (ITapTrade::TapAPITradeLoginRspInfo*)task->task_data;
		loginRspInfo["UserNo"] = std::string(p->UserNo);
		loginRspInfo["UserType"] = p->UserType;
		loginRspInfo["UserName"] = std::string(p->UserName);
		loginRspInfo["ReservedInfo"] = std::string(p->ReservedInfo);
		loginRspInfo["LastLoginIP"] = std::string(p->LastLoginIP);
		loginRspInfo["LastLoginProt"] = p->LastLoginProt;
		loginRspInfo["LastLoginTime"] = std::string(p->LastLoginTime);
		loginRspInfo["LastLogoutTime"] = std::string(p->LastLogoutTime);
		loginRspInfo["TradeDate"] = std::string(p->TradeDate);
		loginRspInfo["LastSettleTime"] = std::string(p->LastSettleTime);
		loginRspInfo["StartTime"] = std::string(p->StartTime);
		loginRspInfo["NextSecondDate"] = std::string(p->NextSecondDate);
		loginRspInfo["LastLoginInfo"] = std::string(p->LastLoginInfo);
		delete p;
	}
	this->onRspLogin(task->task_error, loginRspInfo);
};

void TdApi::processRtnContactInfo(Task *task)
{
	gil_scoped_acquire acquire;
	this->onRtnContactInfo(task->task_error, task->task_last, task->task_string);
};

void TdApi::processRspRequestVertificateCode(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict rsp;
	if (task->task_data) {
		ITapTrade::TapAPIRequestVertificateCodeRsp *p = (ITapTrade::TapAPIRequestVertificateCodeRsp*)task->task_data;
		rsp["SecondSerialID"] = std::string(p->SecondSerialID);
		rsp["Effective"] = p->Effective;
		delete p;
	}
	this->onRspRequestVertificateCode(task->task_id, task->task_error, rsp);
};

void TdApi::processExpriationDate(Task *task)
{
	gil_scoped_acquire acquire;
	this->onExpriationDate(task->task_string, task->task_int);
};

void TdApi::processAPIReady(Task *task)
{
	gil_scoped_acquire acquire;
	this->onAPIReady(task->task_error);
};

void TdApi::processDisconnect(Task *task)
{
	gil_scoped_acquire acquire;
	this->onDisconnect(task->task_int);
};

void TdApi::processRspChangePassword(Task *task)
{
	gil_scoped_acquire acquire;
	this->onRspChangePassword(task->task_id, task->task_error);
};

void TdApi::processRspAuthPassword(Task *task)
{
	gil_scoped_acquire acquire;
	this->onRspAuthPassword(task->task_id, task->task_error);
};

void TdApi::processRspQryTradingDate(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPITradingCalendarQryRsp *p = (ITapTrade::TapAPITradingCalendarQryRsp*)task->task_data;
		info["CurrTradeDate"] = std::string(p->CurrTradeDate);
		info["LastSettlementDate"] = std::string(p->LastSettlementDate);
		info["PromptDate"] = std::string(p->PromptDate);
		info["LastPromptDate"] = std::string(p->LastPromptDate);
		delete p;
	}
	this->onRspQryTradingDate(task->task_id, task->task_error, info);
};

void TdApi::processRspSetReservedInfo(Task *task)
{
	gil_scoped_acquire acquire;
	this->onRspSetReservedInfo(task->task_id, task->task_error, task->task_string);
};

void TdApi::processRspQryAccount(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIAccountInfo *p = (ITapTrade::TapAPIAccountInfo*)task->task_data;
		info["AccountNo"] = std::string(p->AccountNo);
		info["AccountType"] = p->AccountType;
		info["AccountState"] = p->AccountState;
		info["AccountTradeRight"] = p->AccountTradeRight;
		info["CommodityGroupNo"] = std::string(p->CommodityGroupNo);
		info["AccountShortName"] = std::string(p->AccountShortName);
		info["AccountEnShortName"] = std::string(p->AccountEnShortName);
		delete p;
	}
	this->onRspQryAccount(task->task_id, task->task_error, task->task_last, info);
};

void TdApi::processRspQryFund(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIFundData *p = (ITapTrade::TapAPIFundData*)task->task_data;
		info["AccountNo"] = std::string(p->AccountNo);
		info["CurrencyGroupNo"] = std::string(p->CurrencyGroupNo);
		info["CurrencyNo"] = std::string(p->CurrencyNo);
		info["TradeRate"] = p->TradeRate;
		info["FutureAlg"] = p->FutureAlg;
		info["OptionAlg"] = p->OptionAlg;
		info["PreBalance"] = p->PreBalance;
		info["PreUnExpProfit"] = p->PreUnExpProfit;
		info["PreLMEPositionProfit"] = p->PreLMEPositionProfit;
		info["PreEquity"] = p->PreEquity;
		info["PreAvailable1"] = p->PreAvailable1;
		info["PreMarketEquity"] = p->PreMarketEquity;
		info["CashInValue"] = p->CashInValue;
		info["CashOutValue"] = p->CashOutValue;
		info["CashAdjustValue"] = p->CashAdjustValue;
		info["CashPledged"] = p->CashPledged;
		info["FrozenFee"] = p->FrozenFee;
		info["FrozenDeposit"] = p->FrozenDeposit;
		info["AccountFee"] = p->AccountFee;
		info["SwapInValue"] = p->SwapInValue;
		info["SwapOutValue"] = p->SwapOutValue;
		info["PremiumIncome"] = p->PremiumIncome;
		info["PremiumPay"] = p->PremiumPay;
		info["CloseProfit"] = p->CloseProfit;
		info["FrozenFund"] = p->FrozenFund;
		info["UnExpProfit"] = p->UnExpProfit;
		info["ExpProfit"] = p->ExpProfit;
		info["PositionProfit"] = p->PositionProfit;
		info["LmePositionProfit"] = p->LmePositionProfit;
		info["OptionMarketValue"] = p->OptionMarketValue;
		info["AccountIntialMargin"] = p->AccountIntialMargin;
		info["AccountMaintenanceMargin"] = p->AccountMaintenanceMargin;
		info["UpperInitalMargin"] = p->UpperInitalMargin;
		info["UpperMaintenanceMargin"] = p->UpperMaintenanceMargin;
		info["Discount"] = p->Discount;
		info["Balance"] = p->Balance;
		info["Equity"] = p->Equity;
		info["Available"] = p->Available;
		info["CanDraw"] = p->CanDraw;
		info["MarketEquity"] = p->MarketEquity;
		info["AuthMoney"] = p->AuthMoney;
		delete p;
	}
	this->onRspQryFund(task->task_id, task->task_error, task->task_last, info);
};

void TdApi::processRtnFund(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIFundData *p = (ITapTrade::TapAPIFundData*)task->task_data;
		info["AccountNo"] = std::string(p->AccountNo);
		info["CurrencyGroupNo"] = std::string(p->CurrencyGroupNo);
		info["CurrencyNo"] = std::string(p->CurrencyNo);
		info["TradeRate"] = p->TradeRate;
		info["FutureAlg"] = p->FutureAlg;
		info["OptionAlg"] = p->OptionAlg;
		info["PreBalance"] = p->PreBalance;
		info["PreUnExpProfit"] = p->PreUnExpProfit;
		info["PreLMEPositionProfit"] = p->PreLMEPositionProfit;
		info["PreEquity"] = p->PreEquity;
		info["PreAvailable1"] = p->PreAvailable1;
		info["PreMarketEquity"] = p->PreMarketEquity;
		info["CashInValue"] = p->CashInValue;
		info["CashOutValue"] = p->CashOutValue;
		info["CashAdjustValue"] = p->CashAdjustValue;
		info["CashPledged"] = p->CashPledged;
		info["FrozenFee"] = p->FrozenFee;
		info["FrozenDeposit"] = p->FrozenDeposit;
		info["AccountFee"] = p->AccountFee;
		info["SwapInValue"] = p->SwapInValue;
		info["SwapOutValue"] = p->SwapOutValue;
		info["PremiumIncome"] = p->PremiumIncome;
		info["PremiumPay"] = p->PremiumPay;
		info["CloseProfit"] = p->CloseProfit;
		info["FrozenFund"] = p->FrozenFund;
		info["UnExpProfit"] = p->UnExpProfit;
		info["ExpProfit"] = p->ExpProfit;
		info["PositionProfit"] = p->PositionProfit;
		info["LmePositionProfit"] = p->LmePositionProfit;
		info["OptionMarketValue"] = p->OptionMarketValue;
		info["AccountIntialMargin"] = p->AccountIntialMargin;
		info["AccountMaintenanceMargin"] = p->AccountMaintenanceMargin;
		info["UpperInitalMargin"] = p->UpperInitalMargin;
		info["UpperMaintenanceMargin"] = p->UpperMaintenanceMargin;
		info["Discount"] = p->Discount;
		info["Balance"] = p->Balance;
		info["Equity"] = p->Equity;
		info["Available"] = p->Available;
		info["CanDraw"] = p->CanDraw;
		info["MarketEquity"] = p->MarketEquity;
		info["AuthMoney"] = p->AuthMoney;
		delete p;
	}
	this->onRtnFund(info);
};

void TdApi::processRspQryExchange(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIExchangeInfo *p = (ITapTrade::TapAPIExchangeInfo*)task->task_data;
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["ExchangeName"] = std::string(p->ExchangeName);
		delete p;
	}
	this->onRspQryExchange(task->task_id, task->task_error, task->task_last, info);
};

void TdApi::processRspQryCommodity(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPICommodityInfo *p = (ITapTrade::TapAPICommodityInfo*)task->task_data;
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["CommodityName"] = std::string(p->CommodityName);
		info["CommodityEngName"] = std::string(p->CommodityEngName);
		info["RelateExchangeNo"] = std::string(p->RelateExchangeNo);
		info["RelateCommodityType"] = p->RelateCommodityType;
		info["RelateCommodityNo"] = std::string(p->RelateCommodityNo);
		info["RelateExchangeNo2"] = std::string(p->RelateExchangeNo2);
		info["RelateCommodityType2"] = p->RelateCommodityType2;
		info["RelateCommodityNo2"] = std::string(p->RelateCommodityNo2);
		info["CurrencyGroupNo"] = std::string(p->CurrencyGroupNo);
		info["TradeCurrency"] = std::string(p->TradeCurrency);
		info["ContractSize"] = p->ContractSize;
		info["OpenCloseMode"] = p->OpenCloseMode;
		info["StrikePriceTimes"] = p->StrikePriceTimes;
		info["CommodityTickSize"] = p->CommodityTickSize;
		info["CommodityDenominator"] = p->CommodityDenominator;
		info["CmbDirect"] = p->CmbDirect;
		info["DeliveryMode"] = p->DeliveryMode;
		info["DeliveryDays"] = p->DeliveryDays;
		info["AddOneTime"] = std::string(p->AddOneTime);
		info["CommodityTimeZone"] = p->CommodityTimeZone;
		info["IsAddOne"] = p->IsAddOne;
		info["OptionType"] = p->OptionType;
		delete p;
	}
	this->onRspQryCommodity(task->task_id, task->task_error, task->task_last, info);
};

void TdApi::processRspQryContract(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPITradeContractInfo *p = (ITapTrade::TapAPITradeContractInfo*)task->task_data;
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["ContractNo1"] = std::string(p->ContractNo1);
		info["StrikePrice1"] = std::string(p->StrikePrice1);
		info["CallOrPutFlag1"] = p->CallOrPutFlag1;
		info["ContractNo2"] = std::string(p->ContractNo2);
		info["StrikePrice2"] = std::string(p->StrikePrice2);
		info["CallOrPutFlag2"] = p->CallOrPutFlag2;
		info["ContractType"] = p->ContractType;
		info["QuoteUnderlyingContract"] = std::string(p->QuoteUnderlyingContract);
		info["ContractName"] = std::string(p->ContractName);
		info["ContractExpDate"] = std::string(p->ContractExpDate);
		info["LastTradeDate"] = std::string(p->LastTradeDate);
		info["FirstNoticeDate"] = std::string(p->FirstNoticeDate);
		info["ContractSize"] = p->ContractSize;
		delete p;
	}
	this->onRspQryContract(task->task_id, task->task_error, task->task_last, info);
};

void TdApi::processRtnContract(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPITradeContractInfo *p = (ITapTrade::TapAPITradeContractInfo*)task->task_data;
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["ContractNo1"] = std::string(p->ContractNo1);
		info["StrikePrice1"] = std::string(p->StrikePrice1);
		info["CallOrPutFlag1"] = p->CallOrPutFlag1;
		info["ContractNo2"] = std::string(p->ContractNo2);
		info["StrikePrice2"] = std::string(p->StrikePrice2);
		info["CallOrPutFlag2"] = p->CallOrPutFlag2;
		info["ContractType"] = p->ContractType;
		info["QuoteUnderlyingContract"] = std::string(p->QuoteUnderlyingContract);
		info["ContractName"] = std::string(p->ContractName);
		info["ContractExpDate"] = std::string(p->ContractExpDate);
		info["LastTradeDate"] = std::string(p->LastTradeDate);
		info["FirstNoticeDate"] = std::string(p->FirstNoticeDate);
		info["ContractSize"] = p->ContractSize;
		delete p;
	}
	this->onRtnContract(info);
};

void TdApi::processRspOrderAction(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIOrderActionRsp *p = (ITapTrade::TapAPIOrderActionRsp*)task->task_data;
		info["ActionType"] = p->ActionType;
		// TODO: unsupported type "dict" for field "OrderInfo"
		delete p;
	}
	this->onRspOrderAction(task->task_id, task->task_error, info);
};

void TdApi::processRtnOrder(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIOrderInfoNotice *p = (ITapTrade::TapAPIOrderInfoNotice*)task->task_data;
		info["SessionID"] = p->SessionID;
		info["ErrorCode"] = p->ErrorCode;
		// TODO: unsupported type "dict" for field "OrderInfo"
		delete p;
	}
	this->onRtnOrder(info);
};

void TdApi::processRspQryOrder(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIOrderInfo *p = (ITapTrade::TapAPIOrderInfo*)task->task_data;
		info["AccountNo"] = std::string(p->AccountNo);
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["ContractNo"] = std::string(p->ContractNo);
		info["StrikePrice"] = std::string(p->StrikePrice);
		info["CallOrPutFlag"] = p->CallOrPutFlag;
		info["ContractNo2"] = std::string(p->ContractNo2);
		info["StrikePrice2"] = std::string(p->StrikePrice2);
		info["CallOrPutFlag2"] = p->CallOrPutFlag2;
		info["OrderType"] = p->OrderType;
		info["OrderSource"] = p->OrderSource;
		info["TimeInForce"] = p->TimeInForce;
		info["ExpireTime"] = std::string(p->ExpireTime);
		info["IsRiskOrder"] = p->IsRiskOrder;
		info["OrderSide"] = p->OrderSide;
		info["PositionEffect"] = p->PositionEffect;
		info["PositionEffect2"] = p->PositionEffect2;
		info["InquiryNo"] = std::string(p->InquiryNo);
		info["HedgeFlag"] = p->HedgeFlag;
		info["OrderPrice"] = p->OrderPrice;
		info["OrderPrice2"] = p->OrderPrice2;
		info["StopPrice"] = p->StopPrice;
		info["OrderQty"] = p->OrderQty;
		info["OrderMinQty"] = p->OrderMinQty;
		info["RefInt"] = p->RefInt;
		info["RefDouble"] = p->RefDouble;
		info["RefString"] = std::string(p->RefString);
		info["MinClipSize"] = p->MinClipSize;
		info["MaxClipSize"] = p->MaxClipSize;
		info["LicenseNo"] = std::string(p->LicenseNo);
		info["ServerFlag"] = p->ServerFlag;
		info["OrderNo"] = std::string(p->OrderNo);
		info["ClientOrderNo"] = std::string(p->ClientOrderNo);
		info["ClientID"] = std::string(p->ClientID);
		info["TacticsType"] = p->TacticsType;
		info["TriggerCondition"] = p->TriggerCondition;
		info["TriggerPriceType"] = p->TriggerPriceType;
		info["AddOneIsValid"] = p->AddOneIsValid;
		info["ClientLocalIP"] = std::string(p->ClientLocalIP);
		info["ClientMac"] = std::string(p->ClientMac);
		info["ClientIP"] = std::string(p->ClientIP);
		info["OrderStreamID"] = p->OrderStreamID;
		info["UpperNo"] = std::string(p->UpperNo);
		info["UpperChannelNo"] = std::string(p->UpperChannelNo);
		info["OrderLocalNo"] = std::string(p->OrderLocalNo);
		info["UpperStreamID"] = p->UpperStreamID;
		info["OrderSystemNo"] = std::string(p->OrderSystemNo);
		info["OrderExchangeSystemNo"] = std::string(p->OrderExchangeSystemNo);
		info["OrderParentSystemNo"] = std::string(p->OrderParentSystemNo);
		info["OrderInsertUserNo"] = std::string(p->OrderInsertUserNo);
		info["OrderInsertTime"] = std::string(p->OrderInsertTime);
		info["OrderCommandUserNo"] = std::string(p->OrderCommandUserNo);
		info["OrderUpdateUserNo"] = std::string(p->OrderUpdateUserNo);
		info["OrderUpdateTime"] = std::string(p->OrderUpdateTime);
		info["OrderState"] = p->OrderState;
		info["OrderMatchPrice"] = p->OrderMatchPrice;
		info["OrderMatchPrice2"] = p->OrderMatchPrice2;
		info["OrderMatchQty"] = p->OrderMatchQty;
		info["OrderMatchQty2"] = p->OrderMatchQty2;
		info["ErrorCode"] = p->ErrorCode;
		info["ErrorText"] = std::string(p->ErrorText);
		info["IsBackInput"] = p->IsBackInput;
		info["IsDeleted"] = p->IsDeleted;
		info["IsAddOne"] = p->IsAddOne;
		info["ClientLocationID"] = std::string(p->ClientLocationID);
		delete p;
	}
	this->onRspQryOrder(task->task_id, task->task_error, task->task_last, info);
};

void TdApi::processRspQryOrderProcess(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIOrderInfo *p = (ITapTrade::TapAPIOrderInfo*)task->task_data;
		info["AccountNo"] = std::string(p->AccountNo);
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["ContractNo"] = std::string(p->ContractNo);
		info["StrikePrice"] = std::string(p->StrikePrice);
		info["CallOrPutFlag"] = p->CallOrPutFlag;
		info["ContractNo2"] = std::string(p->ContractNo2);
		info["StrikePrice2"] = std::string(p->StrikePrice2);
		info["CallOrPutFlag2"] = p->CallOrPutFlag2;
		info["OrderType"] = p->OrderType;
		info["OrderSource"] = p->OrderSource;
		info["TimeInForce"] = p->TimeInForce;
		info["ExpireTime"] = std::string(p->ExpireTime);
		info["IsRiskOrder"] = p->IsRiskOrder;
		info["OrderSide"] = p->OrderSide;
		info["PositionEffect"] = p->PositionEffect;
		info["PositionEffect2"] = p->PositionEffect2;
		info["InquiryNo"] = std::string(p->InquiryNo);
		info["HedgeFlag"] = p->HedgeFlag;
		info["OrderPrice"] = p->OrderPrice;
		info["OrderPrice2"] = p->OrderPrice2;
		info["StopPrice"] = p->StopPrice;
		info["OrderQty"] = p->OrderQty;
		info["OrderMinQty"] = p->OrderMinQty;
		info["RefInt"] = p->RefInt;
		info["RefDouble"] = p->RefDouble;
		info["RefString"] = std::string(p->RefString);
		info["MinClipSize"] = p->MinClipSize;
		info["MaxClipSize"] = p->MaxClipSize;
		info["LicenseNo"] = std::string(p->LicenseNo);
		info["ServerFlag"] = p->ServerFlag;
		info["OrderNo"] = std::string(p->OrderNo);
		info["ClientOrderNo"] = std::string(p->ClientOrderNo);
		info["ClientID"] = std::string(p->ClientID);
		info["TacticsType"] = p->TacticsType;
		info["TriggerCondition"] = p->TriggerCondition;
		info["TriggerPriceType"] = p->TriggerPriceType;
		info["AddOneIsValid"] = p->AddOneIsValid;
		info["ClientLocalIP"] = std::string(p->ClientLocalIP);
		info["ClientMac"] = std::string(p->ClientMac);
		info["ClientIP"] = std::string(p->ClientIP);
		info["OrderStreamID"] = p->OrderStreamID;
		info["UpperNo"] = std::string(p->UpperNo);
		info["UpperChannelNo"] = std::string(p->UpperChannelNo);
		info["OrderLocalNo"] = std::string(p->OrderLocalNo);
		info["UpperStreamID"] = p->UpperStreamID;
		info["OrderSystemNo"] = std::string(p->OrderSystemNo);
		info["OrderExchangeSystemNo"] = std::string(p->OrderExchangeSystemNo);
		info["OrderParentSystemNo"] = std::string(p->OrderParentSystemNo);
		info["OrderInsertUserNo"] = std::string(p->OrderInsertUserNo);
		info["OrderInsertTime"] = std::string(p->OrderInsertTime);
		info["OrderCommandUserNo"] = std::string(p->OrderCommandUserNo);
		info["OrderUpdateUserNo"] = std::string(p->OrderUpdateUserNo);
		info["OrderUpdateTime"] = std::string(p->OrderUpdateTime);
		info["OrderState"] = p->OrderState;
		info["OrderMatchPrice"] = p->OrderMatchPrice;
		info["OrderMatchPrice2"] = p->OrderMatchPrice2;
		info["OrderMatchQty"] = p->OrderMatchQty;
		info["OrderMatchQty2"] = p->OrderMatchQty2;
		info["ErrorCode"] = p->ErrorCode;
		info["ErrorText"] = std::string(p->ErrorText);
		info["IsBackInput"] = p->IsBackInput;
		info["IsDeleted"] = p->IsDeleted;
		info["IsAddOne"] = p->IsAddOne;
		info["ClientLocationID"] = std::string(p->ClientLocationID);
		delete p;
	}
	this->onRspQryOrderProcess(task->task_id, task->task_error, task->task_last, info);
};

void TdApi::processRspQryFill(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIFillInfo *p = (ITapTrade::TapAPIFillInfo*)task->task_data;
		info["AccountNo"] = std::string(p->AccountNo);
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["ContractNo"] = std::string(p->ContractNo);
		info["StrikePrice"] = std::string(p->StrikePrice);
		info["CallOrPutFlag"] = p->CallOrPutFlag;
		info["MatchSource"] = p->MatchSource;
		info["MatchSide"] = p->MatchSide;
		info["PositionEffect"] = p->PositionEffect;
		info["ServerFlag"] = p->ServerFlag;
		info["OrderNo"] = std::string(p->OrderNo);
		info["OrderSystemNo"] = std::string(p->OrderSystemNo);
		info["MatchNo"] = std::string(p->MatchNo);
		info["UpperMatchNo"] = std::string(p->UpperMatchNo);
		info["ExchangeMatchNo"] = std::string(p->ExchangeMatchNo);
		info["MatchDateTime"] = std::string(p->MatchDateTime);
		info["UpperMatchDateTime"] = std::string(p->UpperMatchDateTime);
		info["UpperNo"] = std::string(p->UpperNo);
		info["MatchPrice"] = p->MatchPrice;
		info["MatchQty"] = p->MatchQty;
		info["IsDeleted"] = p->IsDeleted;
		info["IsAddOne"] = p->IsAddOne;
		info["FeeCurrencyGroup"] = std::string(p->FeeCurrencyGroup);
		info["FeeCurrency"] = std::string(p->FeeCurrency);
		info["FeeValue"] = p->FeeValue;
		info["IsManualFee"] = p->IsManualFee;
		info["ClosePrositionPrice"] = p->ClosePrositionPrice;
		info["CloseProfit"] = p->CloseProfit;
		delete p;
	}
	this->onRspQryFill(task->task_id, task->task_error, task->task_last, info);
};

void TdApi::processRtnFill(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIFillInfo *p = (ITapTrade::TapAPIFillInfo*)task->task_data;
		info["AccountNo"] = std::string(p->AccountNo);
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["ContractNo"] = std::string(p->ContractNo);
		info["StrikePrice"] = std::string(p->StrikePrice);
		info["CallOrPutFlag"] = p->CallOrPutFlag;
		info["MatchSource"] = p->MatchSource;
		info["MatchSide"] = p->MatchSide;
		info["PositionEffect"] = p->PositionEffect;
		info["ServerFlag"] = p->ServerFlag;
		info["OrderNo"] = std::string(p->OrderNo);
		info["OrderSystemNo"] = std::string(p->OrderSystemNo);
		info["MatchNo"] = std::string(p->MatchNo);
		info["UpperMatchNo"] = std::string(p->UpperMatchNo);
		info["ExchangeMatchNo"] = std::string(p->ExchangeMatchNo);
		info["MatchDateTime"] = std::string(p->MatchDateTime);
		info["UpperMatchDateTime"] = std::string(p->UpperMatchDateTime);
		info["UpperNo"] = std::string(p->UpperNo);
		info["MatchPrice"] = p->MatchPrice;
		info["MatchQty"] = p->MatchQty;
		info["IsDeleted"] = p->IsDeleted;
		info["IsAddOne"] = p->IsAddOne;
		info["FeeCurrencyGroup"] = std::string(p->FeeCurrencyGroup);
		info["FeeCurrency"] = std::string(p->FeeCurrency);
		info["FeeValue"] = p->FeeValue;
		info["IsManualFee"] = p->IsManualFee;
		info["ClosePrositionPrice"] = p->ClosePrositionPrice;
		info["CloseProfit"] = p->CloseProfit;
		delete p;
	}
	this->onRtnFill(info);
};

void TdApi::processRspQryPosition(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIPositionInfo *p = (ITapTrade::TapAPIPositionInfo*)task->task_data;
		info["AccountNo"] = std::string(p->AccountNo);
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["ContractNo"] = std::string(p->ContractNo);
		info["StrikePrice"] = std::string(p->StrikePrice);
		info["CallOrPutFlag"] = p->CallOrPutFlag;
		info["MatchSide"] = p->MatchSide;
		info["HedgeFlag"] = p->HedgeFlag;
		info["PositionNo"] = std::string(p->PositionNo);
		info["ServerFlag"] = p->ServerFlag;
		info["OrderNo"] = std::string(p->OrderNo);
		info["MatchNo"] = std::string(p->MatchNo);
		info["UpperNo"] = std::string(p->UpperNo);
		info["PositionPrice"] = p->PositionPrice;
		info["PositionQty"] = p->PositionQty;
		info["PositionStreamId"] = p->PositionStreamId;
		info["CommodityCurrencyGroup"] = std::string(p->CommodityCurrencyGroup);
		info["CommodityCurrency"] = std::string(p->CommodityCurrency);
		info["CalculatePrice"] = p->CalculatePrice;
		info["AccountInitialMargin"] = p->AccountInitialMargin;
		info["AccountMaintenanceMargin"] = p->AccountMaintenanceMargin;
		info["UpperInitialMargin"] = p->UpperInitialMargin;
		info["UpperMaintenanceMargin"] = p->UpperMaintenanceMargin;
		info["PositionProfit"] = p->PositionProfit;
		info["LMEPositionProfit"] = p->LMEPositionProfit;
		info["OptionMarketValue"] = p->OptionMarketValue;
		info["IsHistory"] = p->IsHistory;
		delete p;
	}
	this->onRspQryPosition(task->task_id, task->task_error, task->task_last, info);
};

void TdApi::processRtnPosition(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIPositionInfo *p = (ITapTrade::TapAPIPositionInfo*)task->task_data;
		info["AccountNo"] = std::string(p->AccountNo);
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["ContractNo"] = std::string(p->ContractNo);
		info["StrikePrice"] = std::string(p->StrikePrice);
		info["CallOrPutFlag"] = p->CallOrPutFlag;
		info["MatchSide"] = p->MatchSide;
		info["HedgeFlag"] = p->HedgeFlag;
		info["PositionNo"] = std::string(p->PositionNo);
		info["ServerFlag"] = p->ServerFlag;
		info["OrderNo"] = std::string(p->OrderNo);
		info["MatchNo"] = std::string(p->MatchNo);
		info["UpperNo"] = std::string(p->UpperNo);
		info["PositionPrice"] = p->PositionPrice;
		info["PositionQty"] = p->PositionQty;
		info["PositionStreamId"] = p->PositionStreamId;
		info["CommodityCurrencyGroup"] = std::string(p->CommodityCurrencyGroup);
		info["CommodityCurrency"] = std::string(p->CommodityCurrency);
		info["CalculatePrice"] = p->CalculatePrice;
		info["AccountInitialMargin"] = p->AccountInitialMargin;
		info["AccountMaintenanceMargin"] = p->AccountMaintenanceMargin;
		info["UpperInitialMargin"] = p->UpperInitialMargin;
		info["UpperMaintenanceMargin"] = p->UpperMaintenanceMargin;
		info["PositionProfit"] = p->PositionProfit;
		info["LMEPositionProfit"] = p->LMEPositionProfit;
		info["OptionMarketValue"] = p->OptionMarketValue;
		info["IsHistory"] = p->IsHistory;
		delete p;
	}
	this->onRtnPosition(info);
};

void TdApi::processRspQryPositionSummary(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIPositionSummary *p = (ITapTrade::TapAPIPositionSummary*)task->task_data;
		info["AccountNo"] = std::string(p->AccountNo);
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["ContractNo"] = std::string(p->ContractNo);
		info["StrikePrice"] = std::string(p->StrikePrice);
		info["CallOrPutFlag"] = p->CallOrPutFlag;
		info["MatchSide"] = p->MatchSide;
		info["PositionPrice"] = p->PositionPrice;
		info["PositionQty"] = p->PositionQty;
		info["HisPositionQty"] = p->HisPositionQty;
		info["CalculatePrice"] = p->CalculatePrice;
		info["PositionProfit"] = p->PositionProfit;
		delete p;
	}
	this->onRspQryPositionSummary(task->task_id, task->task_error, task->task_last, info);
};

void TdApi::processRtnPositionSummary(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIPositionSummary *p = (ITapTrade::TapAPIPositionSummary*)task->task_data;
		info["AccountNo"] = std::string(p->AccountNo);
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["ContractNo"] = std::string(p->ContractNo);
		info["StrikePrice"] = std::string(p->StrikePrice);
		info["CallOrPutFlag"] = p->CallOrPutFlag;
		info["MatchSide"] = p->MatchSide;
		info["PositionPrice"] = p->PositionPrice;
		info["PositionQty"] = p->PositionQty;
		info["HisPositionQty"] = p->HisPositionQty;
		info["CalculatePrice"] = p->CalculatePrice;
		info["PositionProfit"] = p->PositionProfit;
		delete p;
	}
	this->onRtnPositionSummary(info);
};

void TdApi::processRtnPositionProfit(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIPositionProfitNotice *p = (ITapTrade::TapAPIPositionProfitNotice*)task->task_data;
		info["IsLast"] = p->IsLast;
		// TODO: unsupported type "dict" for field "Data"
		delete p;
	}
	this->onRtnPositionProfit(info);
};

void TdApi::processRspQryCurrency(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPICurrencyInfo *p = (ITapTrade::TapAPICurrencyInfo*)task->task_data;
		info["CurrencyNo"] = std::string(p->CurrencyNo);
		info["CurrencyGroupNo"] = std::string(p->CurrencyGroupNo);
		info["TradeRate"] = p->TradeRate;
		info["TradeRate2"] = p->TradeRate2;
		info["FutureAlg"] = p->FutureAlg;
		info["OptionAlg"] = p->OptionAlg;
		delete p;
	}
	this->onRspQryCurrency(task->task_id, task->task_error, task->task_last, info);
};

void TdApi::processRspQryTradeMessage(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPITradeMessage *p = (ITapTrade::TapAPITradeMessage*)task->task_data;
		info["SerialID"] = p->SerialID;
		info["AccountNo"] = std::string(p->AccountNo);
		info["TMsgValidDateTime"] = std::string(p->TMsgValidDateTime);
		info["TMsgTitle"] = std::string(p->TMsgTitle);
		info["TMsgContent"] = std::string(p->TMsgContent);
		info["TMsgType"] = p->TMsgType;
		info["TMsgLevel"] = p->TMsgLevel;
		info["IsSendBySMS"] = p->IsSendBySMS;
		info["IsSendByEMail"] = p->IsSendByEMail;
		info["Sender"] = std::string(p->Sender);
		info["SendDateTime"] = std::string(p->SendDateTime);
		delete p;
	}
	this->onRspQryTradeMessage(task->task_id, task->task_error, task->task_last, info);
};

void TdApi::processRtnTradeMessage(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPITradeMessage *p = (ITapTrade::TapAPITradeMessage*)task->task_data;
		info["SerialID"] = p->SerialID;
		info["AccountNo"] = std::string(p->AccountNo);
		info["TMsgValidDateTime"] = std::string(p->TMsgValidDateTime);
		info["TMsgTitle"] = std::string(p->TMsgTitle);
		info["TMsgContent"] = std::string(p->TMsgContent);
		info["TMsgType"] = p->TMsgType;
		info["TMsgLevel"] = p->TMsgLevel;
		info["IsSendBySMS"] = p->IsSendBySMS;
		info["IsSendByEMail"] = p->IsSendByEMail;
		info["Sender"] = std::string(p->Sender);
		info["SendDateTime"] = std::string(p->SendDateTime);
		delete p;
	}
	this->onRtnTradeMessage(info);
};

void TdApi::processRspQryHisOrder(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIHisOrderQryRsp *p = (ITapTrade::TapAPIHisOrderQryRsp*)task->task_data;
		info["Date"] = std::string(p->Date);
		info["AccountNo"] = std::string(p->AccountNo);
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["ContractNo"] = std::string(p->ContractNo);
		info["StrikePrice"] = std::string(p->StrikePrice);
		info["CallOrPutFlag"] = p->CallOrPutFlag;
		info["ContractNo2"] = std::string(p->ContractNo2);
		info["StrikePrice2"] = std::string(p->StrikePrice2);
		info["CallOrPutFlag2"] = p->CallOrPutFlag2;
		info["OrderType"] = p->OrderType;
		info["OrderSource"] = p->OrderSource;
		info["TimeInForce"] = p->TimeInForce;
		info["ExpireTime"] = std::string(p->ExpireTime);
		info["IsRiskOrder"] = p->IsRiskOrder;
		info["OrderSide"] = p->OrderSide;
		info["PositionEffect"] = p->PositionEffect;
		info["PositionEffect2"] = p->PositionEffect2;
		info["InquiryNo"] = std::string(p->InquiryNo);
		info["HedgeFlag"] = p->HedgeFlag;
		info["OrderPrice"] = p->OrderPrice;
		info["OrderPrice2"] = p->OrderPrice2;
		info["StopPrice"] = p->StopPrice;
		info["OrderQty"] = p->OrderQty;
		info["OrderMinQty"] = p->OrderMinQty;
		info["OrderCanceledQty"] = p->OrderCanceledQty;
		info["RefInt"] = p->RefInt;
		info["RefDouble"] = p->RefDouble;
		info["RefString"] = std::string(p->RefString);
		info["ServerFlag"] = p->ServerFlag;
		info["OrderNo"] = std::string(p->OrderNo);
		info["OrderStreamID"] = p->OrderStreamID;
		info["UpperNo"] = std::string(p->UpperNo);
		info["UpperChannelNo"] = std::string(p->UpperChannelNo);
		info["OrderLocalNo"] = std::string(p->OrderLocalNo);
		info["UpperStreamID"] = p->UpperStreamID;
		info["OrderSystemNo"] = std::string(p->OrderSystemNo);
		info["OrderExchangeSystemNo"] = std::string(p->OrderExchangeSystemNo);
		info["OrderParentSystemNo"] = std::string(p->OrderParentSystemNo);
		info["OrderInsertUserNo"] = std::string(p->OrderInsertUserNo);
		info["OrderInsertTime"] = std::string(p->OrderInsertTime);
		info["OrderCommandUserNo"] = std::string(p->OrderCommandUserNo);
		info["OrderUpdateUserNo"] = std::string(p->OrderUpdateUserNo);
		info["OrderUpdateTime"] = std::string(p->OrderUpdateTime);
		info["OrderState"] = p->OrderState;
		info["OrderMatchPrice"] = p->OrderMatchPrice;
		info["OrderMatchPrice2"] = p->OrderMatchPrice2;
		info["OrderMatchQty"] = p->OrderMatchQty;
		info["OrderMatchQty2"] = p->OrderMatchQty2;
		info["ErrorCode"] = p->ErrorCode;
		info["ErrorText"] = std::string(p->ErrorText);
		info["IsBackInput"] = p->IsBackInput;
		info["IsDeleted"] = p->IsDeleted;
		info["IsAddOne"] = p->IsAddOne;
		info["AddOneIsValid"] = p->AddOneIsValid;
		info["MinClipSize"] = p->MinClipSize;
		info["MaxClipSize"] = p->MaxClipSize;
		info["LicenseNo"] = std::string(p->LicenseNo);
		info["TacticsType"] = p->TacticsType;
		info["TriggerCondition"] = p->TriggerCondition;
		info["TriggerPriceType"] = p->TriggerPriceType;
		info["ClientLocalIP"] = std::string(p->ClientLocalIP);
		info["ClientMac"] = std::string(p->ClientMac);
		info["ClientIP"] = std::string(p->ClientIP);
		info["SuperiorAccount"] = std::string(p->SuperiorAccount);
		info["ClientOrderNo"] = std::string(p->ClientOrderNo);
		delete p;
	}
	this->onRspQryHisOrder(task->task_id, task->task_error, task->task_last, info);
};

void TdApi::processRspQryHisOrderProcess(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIHisOrderQryRsp *p = (ITapTrade::TapAPIHisOrderQryRsp*)task->task_data;
		info["Date"] = std::string(p->Date);
		info["AccountNo"] = std::string(p->AccountNo);
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["ContractNo"] = std::string(p->ContractNo);
		info["StrikePrice"] = std::string(p->StrikePrice);
		info["CallOrPutFlag"] = p->CallOrPutFlag;
		info["ContractNo2"] = std::string(p->ContractNo2);
		info["StrikePrice2"] = std::string(p->StrikePrice2);
		info["CallOrPutFlag2"] = p->CallOrPutFlag2;
		info["OrderType"] = p->OrderType;
		info["OrderSource"] = p->OrderSource;
		info["TimeInForce"] = p->TimeInForce;
		info["ExpireTime"] = std::string(p->ExpireTime);
		info["IsRiskOrder"] = p->IsRiskOrder;
		info["OrderSide"] = p->OrderSide;
		info["PositionEffect"] = p->PositionEffect;
		info["PositionEffect2"] = p->PositionEffect2;
		info["InquiryNo"] = std::string(p->InquiryNo);
		info["HedgeFlag"] = p->HedgeFlag;
		info["OrderPrice"] = p->OrderPrice;
		info["OrderPrice2"] = p->OrderPrice2;
		info["StopPrice"] = p->StopPrice;
		info["OrderQty"] = p->OrderQty;
		info["OrderMinQty"] = p->OrderMinQty;
		info["OrderCanceledQty"] = p->OrderCanceledQty;
		info["RefInt"] = p->RefInt;
		info["RefDouble"] = p->RefDouble;
		info["RefString"] = std::string(p->RefString);
		info["ServerFlag"] = p->ServerFlag;
		info["OrderNo"] = std::string(p->OrderNo);
		info["OrderStreamID"] = p->OrderStreamID;
		info["UpperNo"] = std::string(p->UpperNo);
		info["UpperChannelNo"] = std::string(p->UpperChannelNo);
		info["OrderLocalNo"] = std::string(p->OrderLocalNo);
		info["UpperStreamID"] = p->UpperStreamID;
		info["OrderSystemNo"] = std::string(p->OrderSystemNo);
		info["OrderExchangeSystemNo"] = std::string(p->OrderExchangeSystemNo);
		info["OrderParentSystemNo"] = std::string(p->OrderParentSystemNo);
		info["OrderInsertUserNo"] = std::string(p->OrderInsertUserNo);
		info["OrderInsertTime"] = std::string(p->OrderInsertTime);
		info["OrderCommandUserNo"] = std::string(p->OrderCommandUserNo);
		info["OrderUpdateUserNo"] = std::string(p->OrderUpdateUserNo);
		info["OrderUpdateTime"] = std::string(p->OrderUpdateTime);
		info["OrderState"] = p->OrderState;
		info["OrderMatchPrice"] = p->OrderMatchPrice;
		info["OrderMatchPrice2"] = p->OrderMatchPrice2;
		info["OrderMatchQty"] = p->OrderMatchQty;
		info["OrderMatchQty2"] = p->OrderMatchQty2;
		info["ErrorCode"] = p->ErrorCode;
		info["ErrorText"] = std::string(p->ErrorText);
		info["IsBackInput"] = p->IsBackInput;
		info["IsDeleted"] = p->IsDeleted;
		info["IsAddOne"] = p->IsAddOne;
		info["AddOneIsValid"] = p->AddOneIsValid;
		info["MinClipSize"] = p->MinClipSize;
		info["MaxClipSize"] = p->MaxClipSize;
		info["LicenseNo"] = std::string(p->LicenseNo);
		info["TacticsType"] = p->TacticsType;
		info["TriggerCondition"] = p->TriggerCondition;
		info["TriggerPriceType"] = p->TriggerPriceType;
		info["ClientLocalIP"] = std::string(p->ClientLocalIP);
		info["ClientMac"] = std::string(p->ClientMac);
		info["ClientIP"] = std::string(p->ClientIP);
		info["SuperiorAccount"] = std::string(p->SuperiorAccount);
		info["ClientOrderNo"] = std::string(p->ClientOrderNo);
		delete p;
	}
	this->onRspQryHisOrderProcess(task->task_id, task->task_error, task->task_last, info);
};

void TdApi::processRspQryHisMatch(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIHisMatchQryRsp *p = (ITapTrade::TapAPIHisMatchQryRsp*)task->task_data;
		info["SettleDate"] = std::string(p->SettleDate);
		info["TradeDate"] = std::string(p->TradeDate);
		info["AccountNo"] = std::string(p->AccountNo);
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["ContractNo"] = std::string(p->ContractNo);
		info["StrikePrice"] = std::string(p->StrikePrice);
		info["CallOrPutFlag"] = p->CallOrPutFlag;
		info["MatchSource"] = p->MatchSource;
		info["MatchSide"] = p->MatchSide;
		info["PositionEffect"] = p->PositionEffect;
		info["HedgeFlag"] = p->HedgeFlag;
		info["MatchPrice"] = p->MatchPrice;
		info["MatchQty"] = p->MatchQty;
		info["OrderNo"] = std::string(p->OrderNo);
		info["MatchNo"] = std::string(p->MatchNo);
		info["MatchStreamID"] = p->MatchStreamID;
		info["UpperNo"] = std::string(p->UpperNo);
		info["MatchCmbNo"] = std::string(p->MatchCmbNo);
		info["ExchangeMatchNo"] = std::string(p->ExchangeMatchNo);
		info["MatchUpperStreamID"] = p->MatchUpperStreamID;
		info["CommodityCurrencyGroup"] = std::string(p->CommodityCurrencyGroup);
		info["CommodityCurrency"] = std::string(p->CommodityCurrency);
		info["Turnover"] = p->Turnover;
		info["PremiumIncome"] = p->PremiumIncome;
		info["PremiumPay"] = p->PremiumPay;
		info["AccountFee"] = p->AccountFee;
		info["AccountFeeCurrencyGroup"] = std::string(p->AccountFeeCurrencyGroup);
		info["AccountFeeCurrency"] = std::string(p->AccountFeeCurrency);
		info["IsManualFee"] = p->IsManualFee;
		info["AccountOtherFee"] = p->AccountOtherFee;
		info["UpperFee"] = p->UpperFee;
		info["UpperFeeCurrencyGroup"] = std::string(p->UpperFeeCurrencyGroup);
		info["UpperFeeCurrency"] = std::string(p->UpperFeeCurrency);
		info["IsUpperManualFee"] = p->IsUpperManualFee;
		info["UpperOtherFee"] = p->UpperOtherFee;
		info["MatchDateTime"] = std::string(p->MatchDateTime);
		info["UpperMatchDateTime"] = std::string(p->UpperMatchDateTime);
		info["CloseProfit"] = p->CloseProfit;
		info["ClosePrice"] = p->ClosePrice;
		info["CloseQty"] = p->CloseQty;
		info["SettleGroupNo"] = std::string(p->SettleGroupNo);
		info["OperatorNo"] = std::string(p->OperatorNo);
		info["OperateTime"] = std::string(p->OperateTime);
		delete p;
	}
	this->onRspQryHisMatch(task->task_id, task->task_error, task->task_last, info);
};

void TdApi::processRspQryHisPosition(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIHisPositionQryRsp *p = (ITapTrade::TapAPIHisPositionQryRsp*)task->task_data;
		info["SettleDate"] = std::string(p->SettleDate);
		info["OpenDate"] = std::string(p->OpenDate);
		info["AccountNo"] = std::string(p->AccountNo);
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["ContractNo"] = std::string(p->ContractNo);
		info["StrikePrice"] = std::string(p->StrikePrice);
		info["CallOrPutFlag"] = p->CallOrPutFlag;
		info["MatchSide"] = p->MatchSide;
		info["HedgeFlag"] = p->HedgeFlag;
		info["PositionPrice"] = p->PositionPrice;
		info["PositionQty"] = p->PositionQty;
		info["OrderNo"] = std::string(p->OrderNo);
		info["PositionNo"] = std::string(p->PositionNo);
		info["UpperNo"] = std::string(p->UpperNo);
		info["CurrencyGroup"] = std::string(p->CurrencyGroup);
		info["Currency"] = std::string(p->Currency);
		info["PreSettlePrice"] = p->PreSettlePrice;
		info["SettlePrice"] = p->SettlePrice;
		info["PositionDProfit"] = p->PositionDProfit;
		info["LMEPositionProfit"] = p->LMEPositionProfit;
		info["OptionMarketValue"] = p->OptionMarketValue;
		info["AccountInitialMargin"] = p->AccountInitialMargin;
		info["AccountMaintenanceMargin"] = p->AccountMaintenanceMargin;
		info["UpperInitialMargin"] = p->UpperInitialMargin;
		info["UpperMaintenanceMargin"] = p->UpperMaintenanceMargin;
		info["SettleGroupNo"] = std::string(p->SettleGroupNo);
		info["ServerFlag"] = p->ServerFlag;
		info["SuperiorAccount"] = std::string(p->SuperiorAccount);
		delete p;
	}
	this->onRspQryHisPosition(task->task_id, task->task_error, task->task_last, info);
};

void TdApi::processRspQryHisDelivery(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIHisDeliveryQryRsp *p = (ITapTrade::TapAPIHisDeliveryQryRsp*)task->task_data;
		info["DeliveryDate"] = std::string(p->DeliveryDate);
		info["OpenDate"] = std::string(p->OpenDate);
		info["AccountNo"] = std::string(p->AccountNo);
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["ContractNo"] = std::string(p->ContractNo);
		info["StrikePrice"] = std::string(p->StrikePrice);
		info["CallOrPutFlag"] = p->CallOrPutFlag;
		info["MatchSource"] = p->MatchSource;
		info["OpenSide"] = p->OpenSide;
		info["OpenPrice"] = p->OpenPrice;
		info["DeliveryPrice"] = p->DeliveryPrice;
		info["DeliveryQty"] = p->DeliveryQty;
		info["FrozenQty"] = p->FrozenQty;
		info["OpenNo"] = std::string(p->OpenNo);
		info["UpperNo"] = std::string(p->UpperNo);
		info["CommodityCurrencyGroupy"] = std::string(p->CommodityCurrencyGroupy);
		info["CommodityCurrency"] = std::string(p->CommodityCurrency);
		info["PreSettlePrice"] = p->PreSettlePrice;
		info["DeliveryProfit"] = p->DeliveryProfit;
		info["AccountFrozenInitialMargin"] = p->AccountFrozenInitialMargin;
		info["AccountFrozenMaintenanceMargin"] = p->AccountFrozenMaintenanceMargin;
		info["UpperFrozenInitialMargin"] = p->UpperFrozenInitialMargin;
		info["UpperFrozenMaintenanceMargin"] = p->UpperFrozenMaintenanceMargin;
		info["AccountFeeCurrencyGroup"] = std::string(p->AccountFeeCurrencyGroup);
		info["AccountFeeCurrency"] = std::string(p->AccountFeeCurrency);
		info["AccountDeliveryFee"] = p->AccountDeliveryFee;
		info["UpperFeeCurrencyGroup"] = std::string(p->UpperFeeCurrencyGroup);
		info["UpperFeeCurrency"] = std::string(p->UpperFeeCurrency);
		info["UpperDeliveryFee"] = p->UpperDeliveryFee;
		info["DeliveryMode"] = p->DeliveryMode;
		info["OperatorNo"] = std::string(p->OperatorNo);
		info["OperateTime"] = std::string(p->OperateTime);
		info["SettleGourpNo"] = std::string(p->SettleGourpNo);
		info["FutureContractNo"] = std::string(p->FutureContractNo);
		info["OptionStrikePrice"] = std::string(p->OptionStrikePrice);
		info["SuperiorAccount"] = std::string(p->SuperiorAccount);
		delete p;
	}
	this->onRspQryHisDelivery(task->task_id, task->task_error, task->task_last, info);
};

void TdApi::processRspQryHisFund(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIHisFundQryRsp *p = (ITapTrade::TapAPIHisFundQryRsp*)task->task_data;
		info["Date"] = std::string(p->Date);
		info["AccountNo"] = std::string(p->AccountNo);
		info["CurrencyGroupNo"] = std::string(p->CurrencyGroupNo);
		info["CurrencyNo"] = std::string(p->CurrencyNo);
		info["PreBalance"] = p->PreBalance;
		info["PreUnExpProfit"] = p->PreUnExpProfit;
		info["PreLMEPositionProfit"] = p->PreLMEPositionProfit;
		info["PreEquity"] = p->PreEquity;
		info["PreAvailable1"] = p->PreAvailable1;
		info["PreAvailable2"] = p->PreAvailable2;
		info["PreMarketEquity"] = p->PreMarketEquity;
		info["FutureMatchQty"] = p->FutureMatchQty;
		info["OptionMatchQty"] = p->OptionMatchQty;
		info["FuturePositionQty"] = p->FuturePositionQty;
		info["OptionPositionQty"] = p->OptionPositionQty;
		info["FutureTurnover"] = p->FutureTurnover;
		info["CashInValue"] = p->CashInValue;
		info["CashOutValue"] = p->CashOutValue;
		info["AdjustValue"] = p->AdjustValue;
		info["CashPledged"] = p->CashPledged;
		info["CashSwapIn"] = p->CashSwapIn;
		info["CashSwapOut"] = p->CashSwapOut;
		info["AccountFee"] = p->AccountFee;
		info["ExchangeFee"] = p->ExchangeFee;
		info["AccountDeliveryFee"] = p->AccountDeliveryFee;
		info["UpperFee"] = p->UpperFee;
		info["UpperDeliveryFee"] = p->UpperDeliveryFee;
		info["NetFee"] = p->NetFee;
		info["PremiumIncome"] = p->PremiumIncome;
		info["PremiumPay"] = p->PremiumPay;
		info["CloseProfit"] = p->CloseProfit;
		info["DeliveryProfit"] = p->DeliveryProfit;
		info["UnExpProfit"] = p->UnExpProfit;
		info["ExpProfit"] = p->ExpProfit;
		info["PositionProfit"] = p->PositionProfit;
		info["LmePositionProfit"] = p->LmePositionProfit;
		info["AccountIntialMargin"] = p->AccountIntialMargin;
		info["AccountMaintenanceMargin"] = p->AccountMaintenanceMargin;
		info["UpperInitalMargin"] = p->UpperInitalMargin;
		info["UpperMaintenanceMargin"] = p->UpperMaintenanceMargin;
		info["AccountFrozenInitialMargin"] = p->AccountFrozenInitialMargin;
		info["AccountFrozenMaintenanceMargin"] = p->AccountFrozenMaintenanceMargin;
		info["UpperFrozenInitialMargin"] = p->UpperFrozenInitialMargin;
		info["UpperFrozenMaintenanceMargin"] = p->UpperFrozenMaintenanceMargin;
		info["Balance"] = p->Balance;
		info["Equity"] = p->Equity;
		info["Frozen"] = p->Frozen;
		info["Available1"] = p->Available1;
		info["Available2"] = p->Available2;
		info["CanDraw"] = p->CanDraw;
		info["SettleRate"] = p->SettleRate;
		info["Discount"] = p->Discount;
		info["OptionMarketValue"] = p->OptionMarketValue;
		info["OriginalCashInOut"] = p->OriginalCashInOut;
		info["MarketEquity"] = p->MarketEquity;
		info["AccountOtherFee"] = p->AccountOtherFee;
		info["UpperOtherFee"] = p->UpperOtherFee;
		info["AccountAuthCash"] = p->AccountAuthCash;
		info["Interest"] = p->Interest;
		info["CurInterest"] = p->CurInterest;
		info["SettleGroupNo"] = std::string(p->SettleGroupNo);
		info["SuperiorAccount"] = std::string(p->SuperiorAccount);
		delete p;
	}
	this->onRspQryHisFund(task->task_id, task->task_error, task->task_last, info);
};

void TdApi::processRspQryAccountCashAdjust(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIAccountCashAdjustQryRsp *p = (ITapTrade::TapAPIAccountCashAdjustQryRsp*)task->task_data;
		info["Date"] = std::string(p->Date);
		info["AccountNo"] = std::string(p->AccountNo);
		info["CashAdjustType"] = p->CashAdjustType;
		info["CurrencyGroupNo"] = std::string(p->CurrencyGroupNo);
		info["CurrencyNo"] = std::string(p->CurrencyNo);
		info["CashAdjustValue"] = p->CashAdjustValue;
		info["CashAdjustRemark"] = std::string(p->CashAdjustRemark);
		info["OperateTime"] = std::string(p->OperateTime);
		info["OperatorNo"] = std::string(p->OperatorNo);
		info["AccountBank"] = std::string(p->AccountBank);
		info["BankAccount"] = std::string(p->BankAccount);
		info["AccountLWFlag"] = p->AccountLWFlag;
		info["CompanyBank"] = std::string(p->CompanyBank);
		info["InternalBankAccount"] = std::string(p->InternalBankAccount);
		info["CompanyLWFlag"] = p->CompanyLWFlag;
		delete p;
	}
	this->onRspQryAccountCashAdjust(task->task_id, task->task_error, task->task_last, info);
};

void TdApi::processRspQryBill(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIBillQryRsp *p = (ITapTrade::TapAPIBillQryRsp*)task->task_data;
		pybind11::dict info_Reqdata_dict;
		info_Reqdata_dict["UserNo"] = std::string(p->Reqdata.UserNo);
		info_Reqdata_dict["BillType"] = p->Reqdata.BillType;
		info_Reqdata_dict["BillDate"] = std::string(p->Reqdata.BillDate);
		info_Reqdata_dict["BillFileType"] = p->Reqdata.BillFileType;
		info["Reqdata"] = info_Reqdata_dict;
		info["BillLen"] = p->BillLen;
		info["BillText"] = p->BillText;
		delete p;
	}
	this->onRspQryBill(task->task_id, task->task_error, task->task_last, info);
};

void TdApi::processRspQryAccountFeeRent(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIAccountFeeRentQryRsp *p = (ITapTrade::TapAPIAccountFeeRentQryRsp*)task->task_data;
		info["AccountNo"] = std::string(p->AccountNo);
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["MatchSource"] = p->MatchSource;
		info["CalculateMode"] = p->CalculateMode;
		info["CurrencyGroupNo"] = std::string(p->CurrencyGroupNo);
		info["CurrencyNo"] = std::string(p->CurrencyNo);
		info["OpenCloseFee"] = p->OpenCloseFee;
		info["CloseTodayFee"] = p->CloseTodayFee;
		info["ContractNo"] = std::string(p->ContractNo);
		delete p;
	}
	this->onRspQryAccountFeeRent(task->task_id, task->task_error, task->task_last, info);
};

void TdApi::processRspQryAccountMarginRent(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIAccountMarginRentQryRsp *p = (ITapTrade::TapAPIAccountMarginRentQryRsp*)task->task_data;
		info["AccountNo"] = std::string(p->AccountNo);
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["ContractNo"] = std::string(p->ContractNo);
		info["StrikePrice"] = std::string(p->StrikePrice);
		info["CallOrPutFlag"] = p->CallOrPutFlag;
		info["CalculateMode"] = p->CalculateMode;
		info["CurrencyGroupNo"] = std::string(p->CurrencyGroupNo);
		info["CurrencyNo"] = std::string(p->CurrencyNo);
		info["InitialMargin"] = p->InitialMargin;
		info["MaintenanceMargin"] = p->MaintenanceMargin;
		info["SellInitialMargin"] = p->SellInitialMargin;
		info["SellMaintenanceMargin"] = p->SellMaintenanceMargin;
		info["LockMargin"] = p->LockMargin;
		delete p;
	}
	this->onRspQryAccountMarginRent(task->task_id, task->task_error, task->task_last, info);
};

void TdApi::processRspHKMarketOrderInsert(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIOrderMarketInsertRsp *p = (ITapTrade::TapAPIOrderMarketInsertRsp*)task->task_data;
		info["AccountNo"] = std::string(p->AccountNo);
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["ContractNo"] = std::string(p->ContractNo);
		info["StrikePrice"] = std::string(p->StrikePrice);
		info["CallOrPutFlag"] = p->CallOrPutFlag;
		info["OrderType"] = p->OrderType;
		info["TimeInForce"] = p->TimeInForce;
		info["ExpireTime"] = std::string(p->ExpireTime);
		info["OrderSource"] = p->OrderSource;
		info["BuyPositionEffect"] = p->BuyPositionEffect;
		info["SellPositionEffect"] = p->SellPositionEffect;
		info["OrderBuyPrice"] = p->OrderBuyPrice;
		info["OrderSellPrice"] = p->OrderSellPrice;
		info["OrderBuyQty"] = p->OrderBuyQty;
		info["OrderSellQty"] = p->OrderSellQty;
		info["ServerFlag"] = p->ServerFlag;
		info["OrderBuyNo"] = std::string(p->OrderBuyNo);
		info["OrderSellNo"] = std::string(p->OrderSellNo);
		info["AddOneIsValid"] = p->AddOneIsValid;
		info["OrderMarketUserNo"] = std::string(p->OrderMarketUserNo);
		info["OrderMarketTime"] = std::string(p->OrderMarketTime);
		info["RefInt"] = p->RefInt;
		info["RefDouble"] = p->RefDouble;
		info["RefString"] = std::string(p->RefString);
		info["ClientBuyOrderNo"] = std::string(p->ClientBuyOrderNo);
		info["ClientSellOrderNo"] = std::string(p->ClientSellOrderNo);
		info["ErrorCode"] = p->ErrorCode;
		info["ErrorText"] = std::string(p->ErrorText);
		info["ClientLocalIP"] = std::string(p->ClientLocalIP);
		info["ClientMac"] = std::string(p->ClientMac);
		info["ClientIP"] = std::string(p->ClientIP);
		info["Remark"] = std::string(p->Remark);
		delete p;
	}
	this->onRspHKMarketOrderInsert(task->task_id, task->task_error, info);
};

void TdApi::processRspHKMarketOrderDelete(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIOrderMarketInsertRsp *p = (ITapTrade::TapAPIOrderMarketInsertRsp*)task->task_data;
		info["AccountNo"] = std::string(p->AccountNo);
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["ContractNo"] = std::string(p->ContractNo);
		info["StrikePrice"] = std::string(p->StrikePrice);
		info["CallOrPutFlag"] = p->CallOrPutFlag;
		info["OrderType"] = p->OrderType;
		info["TimeInForce"] = p->TimeInForce;
		info["ExpireTime"] = std::string(p->ExpireTime);
		info["OrderSource"] = p->OrderSource;
		info["BuyPositionEffect"] = p->BuyPositionEffect;
		info["SellPositionEffect"] = p->SellPositionEffect;
		info["OrderBuyPrice"] = p->OrderBuyPrice;
		info["OrderSellPrice"] = p->OrderSellPrice;
		info["OrderBuyQty"] = p->OrderBuyQty;
		info["OrderSellQty"] = p->OrderSellQty;
		info["ServerFlag"] = p->ServerFlag;
		info["OrderBuyNo"] = std::string(p->OrderBuyNo);
		info["OrderSellNo"] = std::string(p->OrderSellNo);
		info["AddOneIsValid"] = p->AddOneIsValid;
		info["OrderMarketUserNo"] = std::string(p->OrderMarketUserNo);
		info["OrderMarketTime"] = std::string(p->OrderMarketTime);
		info["RefInt"] = p->RefInt;
		info["RefDouble"] = p->RefDouble;
		info["RefString"] = std::string(p->RefString);
		info["ClientBuyOrderNo"] = std::string(p->ClientBuyOrderNo);
		info["ClientSellOrderNo"] = std::string(p->ClientSellOrderNo);
		info["ErrorCode"] = p->ErrorCode;
		info["ErrorText"] = std::string(p->ErrorText);
		info["ClientLocalIP"] = std::string(p->ClientLocalIP);
		info["ClientMac"] = std::string(p->ClientMac);
		info["ClientIP"] = std::string(p->ClientIP);
		info["Remark"] = std::string(p->Remark);
		delete p;
	}
	this->onRspHKMarketOrderDelete(task->task_id, task->task_error, info);
};

void TdApi::processHKMarketQuoteNotice(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIOrderQuoteMarketNotice *p = (ITapTrade::TapAPIOrderQuoteMarketNotice*)task->task_data;
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["ContractNo"] = std::string(p->ContractNo);
		info["StrikePrice"] = std::string(p->StrikePrice);
		info["CallOrPutFlag"] = p->CallOrPutFlag;
		info["OrderSide"] = p->OrderSide;
		info["OrderQty"] = p->OrderQty;
		delete p;
	}
	this->onHKMarketQuoteNotice(info);
};

void TdApi::processRspOrderLocalRemove(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIOrderLocalRemoveRsp *p = (ITapTrade::TapAPIOrderLocalRemoveRsp*)task->task_data;
		pybind11::dict info_req_dict;
		info_req_dict["ServerFlag"] = p->req.ServerFlag;
		info_req_dict["OrderNo"] = std::string(p->req.OrderNo);
		info["req"] = info_req_dict;
		info["ClientLocalIP"] = std::string(p->ClientLocalIP);
		info["ClientMac"] = std::string(p->ClientMac);
		info["ClientIP"] = std::string(p->ClientIP);
		delete p;
	}
	this->onRspOrderLocalRemove(task->task_id, task->task_error, info);
};

void TdApi::processRspOrderLocalInput(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIOrderInfo *p = (ITapTrade::TapAPIOrderInfo*)task->task_data;
		info["AccountNo"] = std::string(p->AccountNo);
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["ContractNo"] = std::string(p->ContractNo);
		info["StrikePrice"] = std::string(p->StrikePrice);
		info["CallOrPutFlag"] = p->CallOrPutFlag;
		info["ContractNo2"] = std::string(p->ContractNo2);
		info["StrikePrice2"] = std::string(p->StrikePrice2);
		info["CallOrPutFlag2"] = p->CallOrPutFlag2;
		info["OrderType"] = p->OrderType;
		info["OrderSource"] = p->OrderSource;
		info["TimeInForce"] = p->TimeInForce;
		info["ExpireTime"] = std::string(p->ExpireTime);
		info["IsRiskOrder"] = p->IsRiskOrder;
		info["OrderSide"] = p->OrderSide;
		info["PositionEffect"] = p->PositionEffect;
		info["PositionEffect2"] = p->PositionEffect2;
		info["InquiryNo"] = std::string(p->InquiryNo);
		info["HedgeFlag"] = p->HedgeFlag;
		info["OrderPrice"] = p->OrderPrice;
		info["OrderPrice2"] = p->OrderPrice2;
		info["StopPrice"] = p->StopPrice;
		info["OrderQty"] = p->OrderQty;
		info["OrderMinQty"] = p->OrderMinQty;
		info["RefInt"] = p->RefInt;
		info["RefDouble"] = p->RefDouble;
		info["RefString"] = std::string(p->RefString);
		info["MinClipSize"] = p->MinClipSize;
		info["MaxClipSize"] = p->MaxClipSize;
		info["LicenseNo"] = std::string(p->LicenseNo);
		info["ServerFlag"] = p->ServerFlag;
		info["OrderNo"] = std::string(p->OrderNo);
		info["ClientOrderNo"] = std::string(p->ClientOrderNo);
		info["ClientID"] = std::string(p->ClientID);
		info["TacticsType"] = p->TacticsType;
		info["TriggerCondition"] = p->TriggerCondition;
		info["TriggerPriceType"] = p->TriggerPriceType;
		info["AddOneIsValid"] = p->AddOneIsValid;
		info["ClientLocalIP"] = std::string(p->ClientLocalIP);
		info["ClientMac"] = std::string(p->ClientMac);
		info["ClientIP"] = std::string(p->ClientIP);
		info["OrderStreamID"] = p->OrderStreamID;
		info["UpperNo"] = std::string(p->UpperNo);
		info["UpperChannelNo"] = std::string(p->UpperChannelNo);
		info["OrderLocalNo"] = std::string(p->OrderLocalNo);
		info["UpperStreamID"] = p->UpperStreamID;
		info["OrderSystemNo"] = std::string(p->OrderSystemNo);
		info["OrderExchangeSystemNo"] = std::string(p->OrderExchangeSystemNo);
		info["OrderParentSystemNo"] = std::string(p->OrderParentSystemNo);
		info["OrderInsertUserNo"] = std::string(p->OrderInsertUserNo);
		info["OrderInsertTime"] = std::string(p->OrderInsertTime);
		info["OrderCommandUserNo"] = std::string(p->OrderCommandUserNo);
		info["OrderUpdateUserNo"] = std::string(p->OrderUpdateUserNo);
		info["OrderUpdateTime"] = std::string(p->OrderUpdateTime);
		info["OrderState"] = p->OrderState;
		info["OrderMatchPrice"] = p->OrderMatchPrice;
		info["OrderMatchPrice2"] = p->OrderMatchPrice2;
		info["OrderMatchQty"] = p->OrderMatchQty;
		info["OrderMatchQty2"] = p->OrderMatchQty2;
		info["ErrorCode"] = p->ErrorCode;
		info["ErrorText"] = std::string(p->ErrorText);
		info["IsBackInput"] = p->IsBackInput;
		info["IsDeleted"] = p->IsDeleted;
		info["IsAddOne"] = p->IsAddOne;
		info["ClientLocationID"] = std::string(p->ClientLocationID);
		delete p;
	}
	this->onRspOrderLocalInput(task->task_id, task->task_error, info);
};

void TdApi::processRspOrderLocalModify(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIOrderInfo *p = (ITapTrade::TapAPIOrderInfo*)task->task_data;
		info["AccountNo"] = std::string(p->AccountNo);
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["ContractNo"] = std::string(p->ContractNo);
		info["StrikePrice"] = std::string(p->StrikePrice);
		info["CallOrPutFlag"] = p->CallOrPutFlag;
		info["ContractNo2"] = std::string(p->ContractNo2);
		info["StrikePrice2"] = std::string(p->StrikePrice2);
		info["CallOrPutFlag2"] = p->CallOrPutFlag2;
		info["OrderType"] = p->OrderType;
		info["OrderSource"] = p->OrderSource;
		info["TimeInForce"] = p->TimeInForce;
		info["ExpireTime"] = std::string(p->ExpireTime);
		info["IsRiskOrder"] = p->IsRiskOrder;
		info["OrderSide"] = p->OrderSide;
		info["PositionEffect"] = p->PositionEffect;
		info["PositionEffect2"] = p->PositionEffect2;
		info["InquiryNo"] = std::string(p->InquiryNo);
		info["HedgeFlag"] = p->HedgeFlag;
		info["OrderPrice"] = p->OrderPrice;
		info["OrderPrice2"] = p->OrderPrice2;
		info["StopPrice"] = p->StopPrice;
		info["OrderQty"] = p->OrderQty;
		info["OrderMinQty"] = p->OrderMinQty;
		info["RefInt"] = p->RefInt;
		info["RefDouble"] = p->RefDouble;
		info["RefString"] = std::string(p->RefString);
		info["MinClipSize"] = p->MinClipSize;
		info["MaxClipSize"] = p->MaxClipSize;
		info["LicenseNo"] = std::string(p->LicenseNo);
		info["ServerFlag"] = p->ServerFlag;
		info["OrderNo"] = std::string(p->OrderNo);
		info["ClientOrderNo"] = std::string(p->ClientOrderNo);
		info["ClientID"] = std::string(p->ClientID);
		info["TacticsType"] = p->TacticsType;
		info["TriggerCondition"] = p->TriggerCondition;
		info["TriggerPriceType"] = p->TriggerPriceType;
		info["AddOneIsValid"] = p->AddOneIsValid;
		info["ClientLocalIP"] = std::string(p->ClientLocalIP);
		info["ClientMac"] = std::string(p->ClientMac);
		info["ClientIP"] = std::string(p->ClientIP);
		info["OrderStreamID"] = p->OrderStreamID;
		info["UpperNo"] = std::string(p->UpperNo);
		info["UpperChannelNo"] = std::string(p->UpperChannelNo);
		info["OrderLocalNo"] = std::string(p->OrderLocalNo);
		info["UpperStreamID"] = p->UpperStreamID;
		info["OrderSystemNo"] = std::string(p->OrderSystemNo);
		info["OrderExchangeSystemNo"] = std::string(p->OrderExchangeSystemNo);
		info["OrderParentSystemNo"] = std::string(p->OrderParentSystemNo);
		info["OrderInsertUserNo"] = std::string(p->OrderInsertUserNo);
		info["OrderInsertTime"] = std::string(p->OrderInsertTime);
		info["OrderCommandUserNo"] = std::string(p->OrderCommandUserNo);
		info["OrderUpdateUserNo"] = std::string(p->OrderUpdateUserNo);
		info["OrderUpdateTime"] = std::string(p->OrderUpdateTime);
		info["OrderState"] = p->OrderState;
		info["OrderMatchPrice"] = p->OrderMatchPrice;
		info["OrderMatchPrice2"] = p->OrderMatchPrice2;
		info["OrderMatchQty"] = p->OrderMatchQty;
		info["OrderMatchQty2"] = p->OrderMatchQty2;
		info["ErrorCode"] = p->ErrorCode;
		info["ErrorText"] = std::string(p->ErrorText);
		info["IsBackInput"] = p->IsBackInput;
		info["IsDeleted"] = p->IsDeleted;
		info["IsAddOne"] = p->IsAddOne;
		info["ClientLocationID"] = std::string(p->ClientLocationID);
		delete p;
	}
	this->onRspOrderLocalModify(task->task_id, task->task_error, info);
};

void TdApi::processRspOrderLocalTransfer(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIOrderInfo *p = (ITapTrade::TapAPIOrderInfo*)task->task_data;
		info["AccountNo"] = std::string(p->AccountNo);
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["ContractNo"] = std::string(p->ContractNo);
		info["StrikePrice"] = std::string(p->StrikePrice);
		info["CallOrPutFlag"] = p->CallOrPutFlag;
		info["ContractNo2"] = std::string(p->ContractNo2);
		info["StrikePrice2"] = std::string(p->StrikePrice2);
		info["CallOrPutFlag2"] = p->CallOrPutFlag2;
		info["OrderType"] = p->OrderType;
		info["OrderSource"] = p->OrderSource;
		info["TimeInForce"] = p->TimeInForce;
		info["ExpireTime"] = std::string(p->ExpireTime);
		info["IsRiskOrder"] = p->IsRiskOrder;
		info["OrderSide"] = p->OrderSide;
		info["PositionEffect"] = p->PositionEffect;
		info["PositionEffect2"] = p->PositionEffect2;
		info["InquiryNo"] = std::string(p->InquiryNo);
		info["HedgeFlag"] = p->HedgeFlag;
		info["OrderPrice"] = p->OrderPrice;
		info["OrderPrice2"] = p->OrderPrice2;
		info["StopPrice"] = p->StopPrice;
		info["OrderQty"] = p->OrderQty;
		info["OrderMinQty"] = p->OrderMinQty;
		info["RefInt"] = p->RefInt;
		info["RefDouble"] = p->RefDouble;
		info["RefString"] = std::string(p->RefString);
		info["MinClipSize"] = p->MinClipSize;
		info["MaxClipSize"] = p->MaxClipSize;
		info["LicenseNo"] = std::string(p->LicenseNo);
		info["ServerFlag"] = p->ServerFlag;
		info["OrderNo"] = std::string(p->OrderNo);
		info["ClientOrderNo"] = std::string(p->ClientOrderNo);
		info["ClientID"] = std::string(p->ClientID);
		info["TacticsType"] = p->TacticsType;
		info["TriggerCondition"] = p->TriggerCondition;
		info["TriggerPriceType"] = p->TriggerPriceType;
		info["AddOneIsValid"] = p->AddOneIsValid;
		info["ClientLocalIP"] = std::string(p->ClientLocalIP);
		info["ClientMac"] = std::string(p->ClientMac);
		info["ClientIP"] = std::string(p->ClientIP);
		info["OrderStreamID"] = p->OrderStreamID;
		info["UpperNo"] = std::string(p->UpperNo);
		info["UpperChannelNo"] = std::string(p->UpperChannelNo);
		info["OrderLocalNo"] = std::string(p->OrderLocalNo);
		info["UpperStreamID"] = p->UpperStreamID;
		info["OrderSystemNo"] = std::string(p->OrderSystemNo);
		info["OrderExchangeSystemNo"] = std::string(p->OrderExchangeSystemNo);
		info["OrderParentSystemNo"] = std::string(p->OrderParentSystemNo);
		info["OrderInsertUserNo"] = std::string(p->OrderInsertUserNo);
		info["OrderInsertTime"] = std::string(p->OrderInsertTime);
		info["OrderCommandUserNo"] = std::string(p->OrderCommandUserNo);
		info["OrderUpdateUserNo"] = std::string(p->OrderUpdateUserNo);
		info["OrderUpdateTime"] = std::string(p->OrderUpdateTime);
		info["OrderState"] = p->OrderState;
		info["OrderMatchPrice"] = p->OrderMatchPrice;
		info["OrderMatchPrice2"] = p->OrderMatchPrice2;
		info["OrderMatchQty"] = p->OrderMatchQty;
		info["OrderMatchQty2"] = p->OrderMatchQty2;
		info["ErrorCode"] = p->ErrorCode;
		info["ErrorText"] = std::string(p->ErrorText);
		info["IsBackInput"] = p->IsBackInput;
		info["IsDeleted"] = p->IsDeleted;
		info["IsAddOne"] = p->IsAddOne;
		info["ClientLocationID"] = std::string(p->ClientLocationID);
		delete p;
	}
	this->onRspOrderLocalTransfer(task->task_id, task->task_error, info);
};

void TdApi::processRspFillLocalInput(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIFillLocalInputReq *p = (ITapTrade::TapAPIFillLocalInputReq*)task->task_data;
		info["AccountNo"] = std::string(p->AccountNo);
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["ContractNo"] = std::string(p->ContractNo);
		info["StrikePrice"] = std::string(p->StrikePrice);
		info["CallOrPutFlag"] = p->CallOrPutFlag;
		info["MatchSide"] = p->MatchSide;
		info["PositionEffect"] = p->PositionEffect;
		info["HedgeFlag"] = p->HedgeFlag;
		info["MatchPrice"] = p->MatchPrice;
		info["MatchQty"] = p->MatchQty;
		info["OrderSystemNo"] = std::string(p->OrderSystemNo);
		info["UpperMatchNo"] = std::string(p->UpperMatchNo);
		info["MatchDateTime"] = std::string(p->MatchDateTime);
		info["UpperMatchDateTime"] = std::string(p->UpperMatchDateTime);
		info["UpperNo"] = std::string(p->UpperNo);
		info["IsAddOne"] = p->IsAddOne;
		info["FeeCurrencyGroup"] = std::string(p->FeeCurrencyGroup);
		info["FeeCurrency"] = std::string(p->FeeCurrency);
		info["FeeValue"] = p->FeeValue;
		info["IsManualFee"] = p->IsManualFee;
		info["ClosePositionPrice"] = p->ClosePositionPrice;
		delete p;
	}
	this->onRspFillLocalInput(task->task_id, task->task_error, info);
};

void TdApi::processRspFillLocalRemove(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIFillLocalRemoveReq *p = (ITapTrade::TapAPIFillLocalRemoveReq*)task->task_data;
		info["ServerFlag"] = p->ServerFlag;
		info["MatchNo"] = std::string(p->MatchNo);
		delete p;
	}
	this->onRspFillLocalRemove(task->task_id, task->task_error, info);
};

void TdApi::processRspQrySpotLock(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPISpotLockDataRsp *p = (ITapTrade::TapAPISpotLockDataRsp*)task->task_data;
		info["AccountNo"] = std::string(p->AccountNo);
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["LockQty"] = p->LockQty;
		info["FrozenQty"] = p->FrozenQty;
		info["CanUnLockQty"] = p->CanUnLockQty;
		delete p;
	}
	this->onRspQrySpotLock(task->task_id, task->task_error, task->task_last, info);
};

void TdApi::processRtnSpotLock(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPISpotLockDataRsp *p = (ITapTrade::TapAPISpotLockDataRsp*)task->task_data;
		info["AccountNo"] = std::string(p->AccountNo);
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["LockQty"] = p->LockQty;
		info["FrozenQty"] = p->FrozenQty;
		info["CanUnLockQty"] = p->CanUnLockQty;
		delete p;
	}
	this->onRtnSpotLock(info);
};

void TdApi::processRspSubmitUserLoginInfo(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPISubmitUserLoginRspInfo *p = (ITapTrade::TapAPISubmitUserLoginRspInfo*)task->task_data;
		info["UserNo"] = std::string(p->UserNo);
		delete p;
	}
	this->onRspSubmitUserLoginInfo(task->task_id, task->task_error, task->task_last, info);
};

void TdApi::processRspSpecialOrderAction(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPISpecialOrderInfo *p = (ITapTrade::TapAPISpecialOrderInfo*)task->task_data;
		info["SessionID"] = p->SessionID;
		info["ErrorCode"] = p->ErrorCode;
		info["ErrorText"] = std::string(p->ErrorText);
		info["AccountNo"] = std::string(p->AccountNo);
		info["ServerFlag"] = p->ServerFlag;
		info["OrderNo"] = std::string(p->OrderNo);
		info["ClientOrderNo"] = std::string(p->ClientOrderNo);
		info["SpecialOrderType"] = p->SpecialOrderType;
		info["OrderSource"] = p->OrderSource;
		info["CombineStrategy"] = std::string(p->CombineStrategy);
		info["CombineNo"] = std::string(p->CombineNo);
		info["OrderQty"] = p->OrderQty;
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["ContractNo"] = std::string(p->ContractNo);
		info["StrikePrice"] = std::string(p->StrikePrice);
		info["CallOrPutFlag"] = p->CallOrPutFlag;
		info["OrderSide1"] = p->OrderSide1;
		info["CombineQty1"] = p->CombineQty1;
		info["HedgeFlag1"] = p->HedgeFlag1;
		info["ContractNo2"] = std::string(p->ContractNo2);
		info["StrikePrice2"] = std::string(p->StrikePrice2);
		info["CallOrPutFlag2"] = p->CallOrPutFlag2;
		info["OrderSide2"] = p->OrderSide2;
		info["CombineQty2"] = p->CombineQty2;
		info["HedgeFlag2"] = p->HedgeFlag2;
		info["LicenseNo"] = std::string(p->LicenseNo);
		info["ClientLocalIP"] = std::string(p->ClientLocalIP);
		info["ClientMac"] = std::string(p->ClientMac);
		info["ClientIP"] = std::string(p->ClientIP);
		info["OrderStreamID"] = p->OrderStreamID;
		info["UpperNo"] = std::string(p->UpperNo);
		info["UpperChannelNo"] = std::string(p->UpperChannelNo);
		info["OrderLocalNo"] = std::string(p->OrderLocalNo);
		info["OrderSystemNo"] = std::string(p->OrderSystemNo);
		info["OrderExchangeSystemNo"] = std::string(p->OrderExchangeSystemNo);
		info["OrderInsertUserNo"] = std::string(p->OrderInsertUserNo);
		info["OrderInsertTime"] = std::string(p->OrderInsertTime);
		info["OrderState"] = p->OrderState;
		delete p;
	}
	this->onRspSpecialOrderAction(task->task_id, task->task_error, info);
};

void TdApi::processRtnSpecialOrder(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPISpecialOrderInfo *p = (ITapTrade::TapAPISpecialOrderInfo*)task->task_data;
		info["SessionID"] = p->SessionID;
		info["ErrorCode"] = p->ErrorCode;
		info["ErrorText"] = std::string(p->ErrorText);
		info["AccountNo"] = std::string(p->AccountNo);
		info["ServerFlag"] = p->ServerFlag;
		info["OrderNo"] = std::string(p->OrderNo);
		info["ClientOrderNo"] = std::string(p->ClientOrderNo);
		info["SpecialOrderType"] = p->SpecialOrderType;
		info["OrderSource"] = p->OrderSource;
		info["CombineStrategy"] = std::string(p->CombineStrategy);
		info["CombineNo"] = std::string(p->CombineNo);
		info["OrderQty"] = p->OrderQty;
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["ContractNo"] = std::string(p->ContractNo);
		info["StrikePrice"] = std::string(p->StrikePrice);
		info["CallOrPutFlag"] = p->CallOrPutFlag;
		info["OrderSide1"] = p->OrderSide1;
		info["CombineQty1"] = p->CombineQty1;
		info["HedgeFlag1"] = p->HedgeFlag1;
		info["ContractNo2"] = std::string(p->ContractNo2);
		info["StrikePrice2"] = std::string(p->StrikePrice2);
		info["CallOrPutFlag2"] = p->CallOrPutFlag2;
		info["OrderSide2"] = p->OrderSide2;
		info["CombineQty2"] = p->CombineQty2;
		info["HedgeFlag2"] = p->HedgeFlag2;
		info["LicenseNo"] = std::string(p->LicenseNo);
		info["ClientLocalIP"] = std::string(p->ClientLocalIP);
		info["ClientMac"] = std::string(p->ClientMac);
		info["ClientIP"] = std::string(p->ClientIP);
		info["OrderStreamID"] = p->OrderStreamID;
		info["UpperNo"] = std::string(p->UpperNo);
		info["UpperChannelNo"] = std::string(p->UpperChannelNo);
		info["OrderLocalNo"] = std::string(p->OrderLocalNo);
		info["OrderSystemNo"] = std::string(p->OrderSystemNo);
		info["OrderExchangeSystemNo"] = std::string(p->OrderExchangeSystemNo);
		info["OrderInsertUserNo"] = std::string(p->OrderInsertUserNo);
		info["OrderInsertTime"] = std::string(p->OrderInsertTime);
		info["OrderState"] = p->OrderState;
		delete p;
	}
	this->onRtnSpecialOrder(info);
};

void TdApi::processRspQrySpecialOrder(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPISpecialOrderInfo *p = (ITapTrade::TapAPISpecialOrderInfo*)task->task_data;
		info["SessionID"] = p->SessionID;
		info["ErrorCode"] = p->ErrorCode;
		info["ErrorText"] = std::string(p->ErrorText);
		info["AccountNo"] = std::string(p->AccountNo);
		info["ServerFlag"] = p->ServerFlag;
		info["OrderNo"] = std::string(p->OrderNo);
		info["ClientOrderNo"] = std::string(p->ClientOrderNo);
		info["SpecialOrderType"] = p->SpecialOrderType;
		info["OrderSource"] = p->OrderSource;
		info["CombineStrategy"] = std::string(p->CombineStrategy);
		info["CombineNo"] = std::string(p->CombineNo);
		info["OrderQty"] = p->OrderQty;
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["ContractNo"] = std::string(p->ContractNo);
		info["StrikePrice"] = std::string(p->StrikePrice);
		info["CallOrPutFlag"] = p->CallOrPutFlag;
		info["OrderSide1"] = p->OrderSide1;
		info["CombineQty1"] = p->CombineQty1;
		info["HedgeFlag1"] = p->HedgeFlag1;
		info["ContractNo2"] = std::string(p->ContractNo2);
		info["StrikePrice2"] = std::string(p->StrikePrice2);
		info["CallOrPutFlag2"] = p->CallOrPutFlag2;
		info["OrderSide2"] = p->OrderSide2;
		info["CombineQty2"] = p->CombineQty2;
		info["HedgeFlag2"] = p->HedgeFlag2;
		info["LicenseNo"] = std::string(p->LicenseNo);
		info["ClientLocalIP"] = std::string(p->ClientLocalIP);
		info["ClientMac"] = std::string(p->ClientMac);
		info["ClientIP"] = std::string(p->ClientIP);
		info["OrderStreamID"] = p->OrderStreamID;
		info["UpperNo"] = std::string(p->UpperNo);
		info["UpperChannelNo"] = std::string(p->UpperChannelNo);
		info["OrderLocalNo"] = std::string(p->OrderLocalNo);
		info["OrderSystemNo"] = std::string(p->OrderSystemNo);
		info["OrderExchangeSystemNo"] = std::string(p->OrderExchangeSystemNo);
		info["OrderInsertUserNo"] = std::string(p->OrderInsertUserNo);
		info["OrderInsertTime"] = std::string(p->OrderInsertTime);
		info["OrderState"] = p->OrderState;
		delete p;
	}
	this->onRspQrySpecialOrder(task->task_id, task->task_error, task->task_last, info);
};

void TdApi::processRspQryCombinePosition(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPICombinePositionInfo *p = (ITapTrade::TapAPICombinePositionInfo*)task->task_data;
		info["AccountNo"] = std::string(p->AccountNo);
		info["PositionStreamID"] = p->PositionStreamID;
		info["ServerFlag"] = p->ServerFlag;
		info["UpperNo"] = std::string(p->UpperNo);
		info["CombineStrategy"] = std::string(p->CombineStrategy);
		info["CombineNo"] = std::string(p->CombineNo);
		info["PositionQty"] = p->PositionQty;
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["ContractNo"] = std::string(p->ContractNo);
		info["StrikePrice"] = std::string(p->StrikePrice);
		info["CallOrPutFlag"] = p->CallOrPutFlag;
		info["OrderSide1"] = p->OrderSide1;
		info["CombineQty1"] = p->CombineQty1;
		info["HedgeFlag1"] = p->HedgeFlag1;
		info["ContractNo2"] = std::string(p->ContractNo2);
		info["StrikePrice2"] = std::string(p->StrikePrice2);
		info["CallOrPutFlag2"] = p->CallOrPutFlag2;
		info["OrderSide2"] = p->OrderSide2;
		info["CombineQty2"] = p->CombineQty2;
		info["HedgeFlag2"] = p->HedgeFlag2;
		info["CommodityCurrencyGroup"] = std::string(p->CommodityCurrencyGroup);
		info["CommodityCurrency"] = std::string(p->CommodityCurrency);
		info["AccountInitialMargin"] = p->AccountInitialMargin;
		info["AccountMaintenanceMargin"] = p->AccountMaintenanceMargin;
		info["UpperInitialMargin"] = p->UpperInitialMargin;
		info["UpperMaintenanceMargin"] = p->UpperMaintenanceMargin;
		delete p;
	}
	this->onRspQryCombinePosition(task->task_id, task->task_error, task->task_last, info);
};

void TdApi::processRtnCombinePosition(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPICombinePositionInfo *p = (ITapTrade::TapAPICombinePositionInfo*)task->task_data;
		info["AccountNo"] = std::string(p->AccountNo);
		info["PositionStreamID"] = p->PositionStreamID;
		info["ServerFlag"] = p->ServerFlag;
		info["UpperNo"] = std::string(p->UpperNo);
		info["CombineStrategy"] = std::string(p->CombineStrategy);
		info["CombineNo"] = std::string(p->CombineNo);
		info["PositionQty"] = p->PositionQty;
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["ContractNo"] = std::string(p->ContractNo);
		info["StrikePrice"] = std::string(p->StrikePrice);
		info["CallOrPutFlag"] = p->CallOrPutFlag;
		info["OrderSide1"] = p->OrderSide1;
		info["CombineQty1"] = p->CombineQty1;
		info["HedgeFlag1"] = p->HedgeFlag1;
		info["ContractNo2"] = std::string(p->ContractNo2);
		info["StrikePrice2"] = std::string(p->StrikePrice2);
		info["CallOrPutFlag2"] = p->CallOrPutFlag2;
		info["OrderSide2"] = p->OrderSide2;
		info["CombineQty2"] = p->CombineQty2;
		info["HedgeFlag2"] = p->HedgeFlag2;
		info["CommodityCurrencyGroup"] = std::string(p->CommodityCurrencyGroup);
		info["CommodityCurrency"] = std::string(p->CommodityCurrency);
		info["AccountInitialMargin"] = p->AccountInitialMargin;
		info["AccountMaintenanceMargin"] = p->AccountMaintenanceMargin;
		info["UpperInitialMargin"] = p->UpperInitialMargin;
		info["UpperMaintenanceMargin"] = p->UpperMaintenanceMargin;
		delete p;
	}
	this->onRtnCombinePosition(info);
};

void TdApi::processRspQryUserTrustDevice(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIUserTrustDeviceQryRsp *p = (ITapTrade::TapAPIUserTrustDeviceQryRsp*)task->task_data;
		info["UserNo"] = std::string(p->UserNo);
		info["LicenseNo"] = std::string(p->LicenseNo);
		info["Mac"] = std::string(p->Mac);
		info["DeviceName"] = std::string(p->DeviceName);
		info["OperatorNo"] = std::string(p->OperatorNo);
		info["OperateTime"] = std::string(p->OperateTime);
		delete p;
	}
	this->onRspQryUserTrustDevice(task->task_id, task->task_error, task->task_last, info);
};

void TdApi::processRspAddUserTrustDevice(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIUserTrustDeviceQryRsp *p = (ITapTrade::TapAPIUserTrustDeviceQryRsp*)task->task_data;
		info["UserNo"] = std::string(p->UserNo);
		info["LicenseNo"] = std::string(p->LicenseNo);
		info["Mac"] = std::string(p->Mac);
		info["DeviceName"] = std::string(p->DeviceName);
		info["OperatorNo"] = std::string(p->OperatorNo);
		info["OperateTime"] = std::string(p->OperateTime);
		delete p;
	}
	this->onRspAddUserTrustDevice(task->task_id, task->task_error, info);
};

void TdApi::processRspDelUserTrustDevice(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIUserTrustDeviceDelReq *p = (ITapTrade::TapAPIUserTrustDeviceDelReq*)task->task_data;
		info["LicenseNo"] = std::string(p->LicenseNo);
		info["Mac"] = std::string(p->Mac);
		delete p;
	}
	this->onRspDelUserTrustDevice(task->task_id, task->task_error, info);
};

void TdApi::processRtnAddUserTrustDevice(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIUserTrustDeviceQryRsp *p = (ITapTrade::TapAPIUserTrustDeviceQryRsp*)task->task_data;
		info["UserNo"] = std::string(p->UserNo);
		info["LicenseNo"] = std::string(p->LicenseNo);
		info["Mac"] = std::string(p->Mac);
		info["DeviceName"] = std::string(p->DeviceName);
		info["OperatorNo"] = std::string(p->OperatorNo);
		info["OperateTime"] = std::string(p->OperateTime);
		delete p;
	}
	this->onRtnAddUserTrustDevice(info);
};

void TdApi::processRtnDelUserTrustDevice(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIUserTrustDeviceDelReq *p = (ITapTrade::TapAPIUserTrustDeviceDelReq*)task->task_data;
		info["LicenseNo"] = std::string(p->LicenseNo);
		info["Mac"] = std::string(p->Mac);
		delete p;
	}
	this->onRtnDelUserTrustDevice(info);
};

void TdApi::processRspQryIPOInfo(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIIPOInfoQryRsp *p = (ITapTrade::TapAPIIPOInfoQryRsp*)task->task_data;
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["CurrencyGroupNo"] = std::string(p->CurrencyGroupNo);
		info["CurrencyNo"] = std::string(p->CurrencyNo);
		info["BeginDate"] = std::string(p->BeginDate);
		info["EndDate"] = std::string(p->EndDate);
		info["IPODate"] = std::string(p->IPODate);
		info["ResultDate"] = std::string(p->ResultDate);
		info["IPOFee"] = p->IPOFee;
		info["FinancingFee"] = p->FinancingFee;
		info["LoanRatio"] = p->LoanRatio;
		info["FinancingDays"] = p->FinancingDays;
		info["MaxLoanRatio"] = p->MaxLoanRatio;
		info["MaxLoanValue"] = p->MaxLoanValue;
		info["Price"] = p->Price;
		info["OperatorNo"] = std::string(p->OperatorNo);
		info["OperateTime"] = std::string(p->OperateTime);
		delete p;
	}
	this->onRspQryIPOInfo(task->task_id, task->task_error, task->task_last, info);
};

void TdApi::processRspQryIPOStockQty(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIAvailableApplyQryRsp *p = (ITapTrade::TapAPIAvailableApplyQryRsp*)task->task_data;
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["StockQty"] = p->StockQty;
		delete p;
	}
	this->onRspQryIPOStockQty(task->task_id, task->task_error, task->task_last, info);
};

void TdApi::processRspQryAccountIPO(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIAccountIPOQryRsp *p = (ITapTrade::TapAPIAccountIPOQryRsp*)task->task_data;
		info["EndDate"] = std::string(p->EndDate);
		info["ResultDate"] = std::string(p->ResultDate);
		info["IPODate"] = std::string(p->IPODate);
		info["AccountNo"] = std::string(p->AccountNo);
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["ApplyType"] = p->ApplyType;
		info["ApplyQty"] = p->ApplyQty;
		info["ApplyCash"] = p->ApplyCash;
		info["LoanRatio"] = p->LoanRatio;
		info["LoanInterest"] = p->LoanInterest;
		info["ApplyFee"] = p->ApplyFee;
		info["ApplyStatus"] = p->ApplyStatus;
		info["ResultQty"] = p->ResultQty;
		info["OperatorNo"] = std::string(p->OperatorNo);
		info["OperateTime"] = std::string(p->OperateTime);
		delete p;
	}
	this->onRspQryAccountIPO(task->task_id, task->task_error, task->task_last, info);
};

void TdApi::processRspAddAccountIPO(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIAccountIPOQryRsp *p = (ITapTrade::TapAPIAccountIPOQryRsp*)task->task_data;
		info["EndDate"] = std::string(p->EndDate);
		info["ResultDate"] = std::string(p->ResultDate);
		info["IPODate"] = std::string(p->IPODate);
		info["AccountNo"] = std::string(p->AccountNo);
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["ApplyType"] = p->ApplyType;
		info["ApplyQty"] = p->ApplyQty;
		info["ApplyCash"] = p->ApplyCash;
		info["LoanRatio"] = p->LoanRatio;
		info["LoanInterest"] = p->LoanInterest;
		info["ApplyFee"] = p->ApplyFee;
		info["ApplyStatus"] = p->ApplyStatus;
		info["ResultQty"] = p->ResultQty;
		info["OperatorNo"] = std::string(p->OperatorNo);
		info["OperateTime"] = std::string(p->OperateTime);
		delete p;
	}
	this->onRspAddAccountIPO(task->task_id, task->task_error, info);
};

void TdApi::processRspCancelAccountIPO(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIAccountIPOQryRsp *p = (ITapTrade::TapAPIAccountIPOQryRsp*)task->task_data;
		info["EndDate"] = std::string(p->EndDate);
		info["ResultDate"] = std::string(p->ResultDate);
		info["IPODate"] = std::string(p->IPODate);
		info["AccountNo"] = std::string(p->AccountNo);
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["ApplyType"] = p->ApplyType;
		info["ApplyQty"] = p->ApplyQty;
		info["ApplyCash"] = p->ApplyCash;
		info["LoanRatio"] = p->LoanRatio;
		info["LoanInterest"] = p->LoanInterest;
		info["ApplyFee"] = p->ApplyFee;
		info["ApplyStatus"] = p->ApplyStatus;
		info["ResultQty"] = p->ResultQty;
		info["OperatorNo"] = std::string(p->OperatorNo);
		info["OperateTime"] = std::string(p->OperateTime);
		delete p;
	}
	this->onRspCancelAccountIPO(task->task_id, task->task_error, info);
};

void TdApi::processRtnAddAccountIPO(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIAccountIPOQryRsp *p = (ITapTrade::TapAPIAccountIPOQryRsp*)task->task_data;
		info["EndDate"] = std::string(p->EndDate);
		info["ResultDate"] = std::string(p->ResultDate);
		info["IPODate"] = std::string(p->IPODate);
		info["AccountNo"] = std::string(p->AccountNo);
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["ApplyType"] = p->ApplyType;
		info["ApplyQty"] = p->ApplyQty;
		info["ApplyCash"] = p->ApplyCash;
		info["LoanRatio"] = p->LoanRatio;
		info["LoanInterest"] = p->LoanInterest;
		info["ApplyFee"] = p->ApplyFee;
		info["ApplyStatus"] = p->ApplyStatus;
		info["ResultQty"] = p->ResultQty;
		info["OperatorNo"] = std::string(p->OperatorNo);
		info["OperateTime"] = std::string(p->OperateTime);
		delete p;
	}
	this->onRtnAddAccountIPO(info);
};

void TdApi::processRtnCancelAccountIPO(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIAccountIPOQryRsp *p = (ITapTrade::TapAPIAccountIPOQryRsp*)task->task_data;
		info["EndDate"] = std::string(p->EndDate);
		info["ResultDate"] = std::string(p->ResultDate);
		info["IPODate"] = std::string(p->IPODate);
		info["AccountNo"] = std::string(p->AccountNo);
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["ApplyType"] = p->ApplyType;
		info["ApplyQty"] = p->ApplyQty;
		info["ApplyCash"] = p->ApplyCash;
		info["LoanRatio"] = p->LoanRatio;
		info["LoanInterest"] = p->LoanInterest;
		info["ApplyFee"] = p->ApplyFee;
		info["ApplyStatus"] = p->ApplyStatus;
		info["ResultQty"] = p->ResultQty;
		info["OperatorNo"] = std::string(p->OperatorNo);
		info["OperateTime"] = std::string(p->OperateTime);
		delete p;
	}
	this->onRtnCancelAccountIPO(info);
};

void TdApi::processRspSelfPasswordInfoOperate(Task *task)
{
	gil_scoped_acquire acquire;
	this->onRspSelfPasswordInfoOperate(task->task_error);
};

void TdApi::processRspVerificateIdentityInfo(Task *task)
{
	gil_scoped_acquire acquire;
	this->onRspVerificateIdentityInfo(task->task_id, task->task_error);
};

void TdApi::processRspSetVertificateCode(Task *task)
{
	gil_scoped_acquire acquire;
	this->onRspSetVertificateCode(task->task_id, task->task_error);
};

void TdApi::processRspResetPassword(Task *task)
{
	gil_scoped_acquire acquire;
	this->onRspResetPassword(task->task_id, task->task_error);
};

void TdApi::processRspQryExchangeStateInfo(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIExchangeStateInfoQryRsp *p = (ITapTrade::TapAPIExchangeStateInfoQryRsp*)task->task_data;
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["ExchangeTime"] = std::string(p->ExchangeTime);
		info["TradingState"] = p->TradingState;
		info["OperatorNo"] = std::string(p->OperatorNo);
		info["OperateTime"] = std::string(p->OperateTime);
		delete p;
	}
	this->onRspQryExchangeStateInfo(task->task_id, task->task_error, task->task_last, info);
};

void TdApi::processRtnExchangeStateInfo(Task *task)
{
	gil_scoped_acquire acquire;
	pybind11::dict info;
	if (task->task_data) {
		ITapTrade::TapAPIExchangeStateInfoQryRsp *p = (ITapTrade::TapAPIExchangeStateInfoQryRsp*)task->task_data;
		info["ExchangeNo"] = std::string(p->ExchangeNo);
		info["CommodityType"] = p->CommodityType;
		info["CommodityNo"] = std::string(p->CommodityNo);
		info["ExchangeTime"] = std::string(p->ExchangeTime);
		info["TradingState"] = p->TradingState;
		info["OperatorNo"] = std::string(p->OperatorNo);
		info["OperateTime"] = std::string(p->OperateTime);
		delete p;
	}
	this->onRtnExchangeStateInfo(info);
};

///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

int TdApi::setAPINotify()
{
	int i = this->api->SetAPINotify(this);
	return i;
};

int TdApi::setHostAddress(const string &IP, unsigned short port, bool bSSL)
{
	int i = this->api->SetHostAddress(const_cast<char*>(IP.c_str()), port, bSSL);
	return i;
};

int TdApi::login(const dict &loginAuth)
{
	ITapTrade::TapAPITradeLoginAuth loginAuth_req = {};
	getString(loginAuth, "UserNo", loginAuth_req.UserNo);
	getChar(loginAuth, "ISModifyPassword", &loginAuth_req.ISModifyPassword);
	getString(loginAuth, "Password", loginAuth_req.Password);
	getString(loginAuth, "NewPassword", loginAuth_req.NewPassword);
	getString(loginAuth, "LoginIP", loginAuth_req.LoginIP);
	getString(loginAuth, "LoginMac", loginAuth_req.LoginMac);
	getString(loginAuth, "DeviceName", loginAuth_req.DeviceName);
	int i = this->api->Login(&loginAuth_req);
	return i;
};

int TdApi::requestVertificateCode(const string &ContactInfo)
{
	ITapTrade::TAPIUINT32 session;
	char ContactInfo_buf[41] = {};
	strncpy(ContactInfo_buf, ContactInfo.c_str(), 41 - 1);
	ContactInfo_buf[41 - 1] = '\0';
	int i = this->api->RequestVertificateCode(&session, ContactInfo_buf);
	return i;
};

int TdApi::setVertificateCode(const dict &req)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPISecondCertificationReq req_req = {};
	getString(req, "VertificateCode", req_req.VertificateCode);
	getChar(req, "LoginType", &req_req.LoginType);
	getChar(req, "IsTOTPCode", &req_req.IsTOTPCode);
	int i = this->api->SetVertificateCode(&session, &req_req);
	return i;
};

int TdApi::disconnect()
{
	int i = this->api->Disconnect();
	return i;
};

int TdApi::changePassword(const dict &req)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPIChangePasswordReq req_req = {};
	getChar(req, "PasswordType", &req_req.PasswordType);
	getString(req, "OldPassword", req_req.OldPassword);
	getString(req, "NewPassword", req_req.NewPassword);
	int i = this->api->ChangePassword(&session, &req_req);
	return i;
};

int TdApi::authPassword(const dict &req)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPIAuthPasswordReq req_req = {};
	getString(req, "AccountNo", req_req.AccountNo);
	getChar(req, "PasswordType", &req_req.PasswordType);
	getString(req, "Password", req_req.Password);
	int i = this->api->AuthPassword(&session, &req_req);
	return i;
};

int TdApi::haveCertainRight(int rightID)
{
	int i = this->api->HaveCertainRight(rightID);
	return i;
};

int TdApi::qryTradingDate()
{
	ITapTrade::TAPIUINT32 session;
	int i = this->api->QryTradingDate(&session);
	return i;
};

int TdApi::setReservedInfo(const string &info)
{
	ITapTrade::TAPIUINT32 session;
	char info_buf[51] = {};
	strncpy(info_buf, info.c_str(), 51 - 1);
	info_buf[51 - 1] = '\0';
	int i = this->api->SetReservedInfo(&session, info_buf);
	return i;
};

int TdApi::qryAccount(const dict &qryReq)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPIAccQryReq qryReq_req = {};
	int i = this->api->QryAccount(&session, &qryReq_req);
	return i;
};

int TdApi::qryFund(const dict &qryReq)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPIFundReq qryReq_req = {};
	getString(qryReq, "AccountNo", qryReq_req.AccountNo);
	int i = this->api->QryFund(&session, &qryReq_req);
	return i;
};

int TdApi::qryExchange()
{
	ITapTrade::TAPIUINT32 session;
	int i = this->api->QryExchange(&session);
	return i;
};

int TdApi::qryCommodity()
{
	ITapTrade::TAPIUINT32 session;
	int i = this->api->QryCommodity(&session);
	return i;
};

int TdApi::qryContract(const dict &qryReq)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPICommodity qryReq_req = {};
	getString(qryReq, "ExchangeNo", qryReq_req.ExchangeNo);
	getChar(qryReq, "CommodityType", &qryReq_req.CommodityType);
	getString(qryReq, "CommodityNo", qryReq_req.CommodityNo);
	int i = this->api->QryContract(&session, &qryReq_req);
	return i;
};

int TdApi::insertOrder(const string &ClientOrderNo, const dict &order)
{
	ITapTrade::TAPIUINT32 session;
	char ClientOrderNo_buf[51] = {};
	strncpy(ClientOrderNo_buf, ClientOrderNo.c_str(), 51 - 1);
	ClientOrderNo_buf[51 - 1] = '\0';
	ITapTrade::TapAPINewOrder order_req = {};
	getString(order, "AccountNo", order_req.AccountNo);
	getString(order, "ExchangeNo", order_req.ExchangeNo);
	getChar(order, "CommodityType", &order_req.CommodityType);
	getString(order, "CommodityNo", order_req.CommodityNo);
	getString(order, "ContractNo", order_req.ContractNo);
	getString(order, "StrikePrice", order_req.StrikePrice);
	getChar(order, "CallOrPutFlag", &order_req.CallOrPutFlag);
	getString(order, "ContractNo2", order_req.ContractNo2);
	getString(order, "StrikePrice2", order_req.StrikePrice2);
	getChar(order, "CallOrPutFlag2", &order_req.CallOrPutFlag2);
	getChar(order, "OrderType", &order_req.OrderType);
	getChar(order, "OrderSource", &order_req.OrderSource);
	getChar(order, "TimeInForce", &order_req.TimeInForce);
	getString(order, "ExpireTime", order_req.ExpireTime);
	getChar(order, "IsRiskOrder", &order_req.IsRiskOrder);
	getChar(order, "OrderSide", &order_req.OrderSide);
	getChar(order, "PositionEffect", &order_req.PositionEffect);
	getChar(order, "PositionEffect2", &order_req.PositionEffect2);
	getString(order, "InquiryNo", order_req.InquiryNo);
	getChar(order, "HedgeFlag", &order_req.HedgeFlag);
	getDouble(order, "OrderPrice", &order_req.OrderPrice);
	getDouble(order, "OrderPrice2", &order_req.OrderPrice2);
	getDouble(order, "StopPrice", &order_req.StopPrice);
	getUnsignedInt(order, "OrderQty", &order_req.OrderQty);
	getUnsignedInt(order, "OrderMinQty", &order_req.OrderMinQty);
	getUnsignedInt(order, "MinClipSize", &order_req.MinClipSize);
	getUnsignedInt(order, "MaxClipSize", &order_req.MaxClipSize);
	getInt(order, "RefInt", &order_req.RefInt);
	getDouble(order, "RefDouble", &order_req.RefDouble);
	getString(order, "RefString", order_req.RefString);
	getString(order, "ClientID", order_req.ClientID);
	getChar(order, "TacticsType", &order_req.TacticsType);
	getChar(order, "TriggerCondition", &order_req.TriggerCondition);
	getChar(order, "TriggerPriceType", &order_req.TriggerPriceType);
	getChar(order, "AddOneIsValid", &order_req.AddOneIsValid);
	getString(order, "ClientLocationID", order_req.ClientLocationID);
	int i = this->api->InsertOrder(&session, &ClientOrderNo_buf, &order_req);
	return i;
};

int TdApi::cancelOrder(const dict &order)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPIOrderCancelReq order_req = {};
	getInt(order, "RefInt", &order_req.RefInt);
	getDouble(order, "RefDouble", &order_req.RefDouble);
	getString(order, "RefString", order_req.RefString);
	getChar(order, "ServerFlag", &order_req.ServerFlag);
	getString(order, "OrderNo", order_req.OrderNo);
	int i = this->api->CancelOrder(&session, &order_req);
	return i;
};

int TdApi::amendOrder(const dict &order)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPIAmendOrder order_req = {};
	// TODO: unsupported type "TapAPINewOrder" for field "ReqData"
	getChar(order, "ServerFlag", &order_req.ServerFlag);
	getString(order, "OrderNo", order_req.OrderNo);
	int i = this->api->AmendOrder(&session, &order_req);
	return i;
};

int TdApi::activateOrder(const dict &order)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPIOrderCancelReq order_req = {};
	getInt(order, "RefInt", &order_req.RefInt);
	getDouble(order, "RefDouble", &order_req.RefDouble);
	getString(order, "RefString", order_req.RefString);
	getChar(order, "ServerFlag", &order_req.ServerFlag);
	getString(order, "OrderNo", order_req.OrderNo);
	int i = this->api->ActivateOrder(&session, &order_req);
	return i;
};

int TdApi::qryOrder(const dict &qryReq)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPIOrderQryReq qryReq_req = {};
	getString(qryReq, "AccountNo", qryReq_req.AccountNo);
	getString(qryReq, "ExchangeNo", qryReq_req.ExchangeNo);
	getChar(qryReq, "CommodityType", &qryReq_req.CommodityType);
	getString(qryReq, "CommodityNo", qryReq_req.CommodityNo);
	getChar(qryReq, "OrderType", &qryReq_req.OrderType);
	getChar(qryReq, "OrderSource", &qryReq_req.OrderSource);
	getChar(qryReq, "TimeInForce", &qryReq_req.TimeInForce);
	getString(qryReq, "ExpireTime", qryReq_req.ExpireTime);
	getChar(qryReq, "IsRiskOrder", &qryReq_req.IsRiskOrder);
	getChar(qryReq, "ServerFlag", &qryReq_req.ServerFlag);
	getString(qryReq, "OrderNo", qryReq_req.OrderNo);
	getChar(qryReq, "IsBackInput", &qryReq_req.IsBackInput);
	getChar(qryReq, "IsDeleted", &qryReq_req.IsDeleted);
	getChar(qryReq, "IsAddOne", &qryReq_req.IsAddOne);
	getChar(qryReq, "OrderQryType", &qryReq_req.OrderQryType);
	int i = this->api->QryOrder(&session, &qryReq_req);
	return i;
};

int TdApi::qryOrderProcess(const dict &qryReq)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPIOrderProcessQryReq qryReq_req = {};
	getChar(qryReq, "ServerFlag", &qryReq_req.ServerFlag);
	getString(qryReq, "OrderNo", qryReq_req.OrderNo);
	int i = this->api->QryOrderProcess(&session, &qryReq_req);
	return i;
};

int TdApi::qryFill(const dict &qryReq)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPIFillQryReq qryReq_req = {};
	getString(qryReq, "AccountNo", qryReq_req.AccountNo);
	getString(qryReq, "ExchangeNo", qryReq_req.ExchangeNo);
	getChar(qryReq, "CommodityType", &qryReq_req.CommodityType);
	getString(qryReq, "CommodityNo", qryReq_req.CommodityNo);
	getString(qryReq, "ContractNo", qryReq_req.ContractNo);
	getString(qryReq, "StrikePrice", qryReq_req.StrikePrice);
	getChar(qryReq, "CallOrPutFlag", &qryReq_req.CallOrPutFlag);
	getChar(qryReq, "MatchSource", &qryReq_req.MatchSource);
	getChar(qryReq, "MatchSide", &qryReq_req.MatchSide);
	getChar(qryReq, "PositionEffect", &qryReq_req.PositionEffect);
	getChar(qryReq, "ServerFlag", &qryReq_req.ServerFlag);
	getString(qryReq, "OrderNo", qryReq_req.OrderNo);
	getString(qryReq, "UpperNo", qryReq_req.UpperNo);
	getChar(qryReq, "IsDeleted", &qryReq_req.IsDeleted);
	getChar(qryReq, "IsAddOne", &qryReq_req.IsAddOne);
	int i = this->api->QryFill(&session, &qryReq_req);
	return i;
};

int TdApi::qryPosition(const dict &qryReq)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPIPositionQryReq qryReq_req = {};
	getString(qryReq, "AccountNo", qryReq_req.AccountNo);
	int i = this->api->QryPosition(&session, &qryReq_req);
	return i;
};

int TdApi::qryPositionSummary(const dict &qryReq)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPIPositionQryReq qryReq_req = {};
	getString(qryReq, "AccountNo", qryReq_req.AccountNo);
	int i = this->api->QryPositionSummary(&session, &qryReq_req);
	return i;
};

int TdApi::qryCurrency()
{
	ITapTrade::TAPIUINT32 session;
	int i = this->api->QryCurrency(&session);
	return i;
};

int TdApi::qryAccountCashAdjust(const dict &qryReq)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPIAccountCashAdjustQryReq qryReq_req = {};
	getUnsignedInt(qryReq, "SerialID", &qryReq_req.SerialID);
	getString(qryReq, "AccountNo", qryReq_req.AccountNo);
	getString(qryReq, "BeginDate", qryReq_req.BeginDate);
	getString(qryReq, "EndDate", qryReq_req.EndDate);
	int i = this->api->QryAccountCashAdjust(&session, &qryReq_req);
	return i;
};

int TdApi::qryTradeMessage(const dict &qryReq)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPITradeMessageReq qryReq_req = {};
	getString(qryReq, "AccountNo", qryReq_req.AccountNo);
	getString(qryReq, "BenginSendDateTime", qryReq_req.BenginSendDateTime);
	getString(qryReq, "EndSendDateTime", qryReq_req.EndSendDateTime);
	int i = this->api->QryTradeMessage(&session, &qryReq_req);
	return i;
};

int TdApi::qryBill(const dict &qryReq)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPIBillQryReq qryReq_req = {};
	getString(qryReq, "UserNo", qryReq_req.UserNo);
	getChar(qryReq, "BillType", &qryReq_req.BillType);
	getString(qryReq, "BillDate", qryReq_req.BillDate);
	getChar(qryReq, "BillFileType", &qryReq_req.BillFileType);
	int i = this->api->QryBill(&session, &qryReq_req);
	return i;
};

int TdApi::qryHisOrder(const dict &qryReq)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPIHisOrderQryReq qryReq_req = {};
	getString(qryReq, "AccountNo", qryReq_req.AccountNo);
	getString(qryReq, "BeginDate", qryReq_req.BeginDate);
	getString(qryReq, "EndDate", qryReq_req.EndDate);
	int i = this->api->QryHisOrder(&session, &qryReq_req);
	return i;
};

int TdApi::qryHisOrderProcess(const dict &qryReq)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPIHisOrderProcessQryReq qryReq_req = {};
	getString(qryReq, "Date", qryReq_req.Date);
	getString(qryReq, "OrderNo", qryReq_req.OrderNo);
	int i = this->api->QryHisOrderProcess(&session, &qryReq_req);
	return i;
};

int TdApi::qryHisMatch(const dict &qryReq)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPIHisMatchQryReq qryReq_req = {};
	getString(qryReq, "AccountNo", qryReq_req.AccountNo);
	getString(qryReq, "BeginDate", qryReq_req.BeginDate);
	getString(qryReq, "EndDate", qryReq_req.EndDate);
	int i = this->api->QryHisMatch(&session, &qryReq_req);
	return i;
};

int TdApi::qryHisPosition(const dict &qryReq)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPIHisPositionQryReq qryReq_req = {};
	getString(qryReq, "AccountNo", qryReq_req.AccountNo);
	getString(qryReq, "Date", qryReq_req.Date);
	getChar(qryReq, "SettleFlag", &qryReq_req.SettleFlag);
	int i = this->api->QryHisPosition(&session, &qryReq_req);
	return i;
};

int TdApi::qryHisDelivery(const dict &qryReq)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPIHisDeliveryQryReq qryReq_req = {};
	getString(qryReq, "AccountNo", qryReq_req.AccountNo);
	getString(qryReq, "BeginDate", qryReq_req.BeginDate);
	getString(qryReq, "EndDate", qryReq_req.EndDate);
	getChar(qryReq, "SettleFlag", &qryReq_req.SettleFlag);
	int i = this->api->QryHisDelivery(&session, &qryReq_req);
	return i;
};

int TdApi::qryHisFund(const dict &qryReq)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPIHisFundQryReq qryReq_req = {};
	getString(qryReq, "BeginDate", qryReq_req.BeginDate);
	getString(qryReq, "EndDate", qryReq_req.EndDate);
	getChar(qryReq, "SettleFlag", &qryReq_req.SettleFlag);
	int i = this->api->QryHisFund(&session, &qryReq_req);
	return i;
};

int TdApi::qryAccountFeeRent(const dict &qryReq)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPIAccountFeeRentQryReq qryReq_req = {};
	getString(qryReq, "AccountNo", qryReq_req.AccountNo);
	int i = this->api->QryAccountFeeRent(&session, &qryReq_req);
	return i;
};

int TdApi::qryAccountMarginRent(const dict &qryReq)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPIAccountMarginRentQryReq qryReq_req = {};
	getString(qryReq, "AccountNo", qryReq_req.AccountNo);
	getString(qryReq, "ExchangeNo", qryReq_req.ExchangeNo);
	getChar(qryReq, "CommodityType", &qryReq_req.CommodityType);
	getString(qryReq, "CommodityNo", qryReq_req.CommodityNo);
	int i = this->api->QryAccountMarginRent(&session, &qryReq_req);
	return i;
};

int TdApi::insertHKMarketOrder(const string &ClientBuyOrderNo, const string &ClientSellOrderNo, const dict &order)
{
	ITapTrade::TAPIUINT32 session;
	char ClientBuyOrderNo_buf[51] = {};
	strncpy(ClientBuyOrderNo_buf, ClientBuyOrderNo.c_str(), 51 - 1);
	ClientBuyOrderNo_buf[51 - 1] = '\0';
	char ClientSellOrderNo_buf[51] = {};
	strncpy(ClientSellOrderNo_buf, ClientSellOrderNo.c_str(), 51 - 1);
	ClientSellOrderNo_buf[51 - 1] = '\0';
	ITapTrade::TapAPIOrderMarketInsertReq order_req = {};
	getString(order, "AccountNo", order_req.AccountNo);
	getString(order, "ExchangeNo", order_req.ExchangeNo);
	getChar(order, "CommodityType", &order_req.CommodityType);
	getString(order, "CommodityNo", order_req.CommodityNo);
	getString(order, "ContractNo", order_req.ContractNo);
	getString(order, "StrikePrice", order_req.StrikePrice);
	getChar(order, "CallOrPutFlag", &order_req.CallOrPutFlag);
	getChar(order, "OrderType", &order_req.OrderType);
	getChar(order, "TimeInForce", &order_req.TimeInForce);
	getString(order, "ExpireTime", order_req.ExpireTime);
	getChar(order, "OrderSource", &order_req.OrderSource);
	getChar(order, "BuyPositionEffect", &order_req.BuyPositionEffect);
	getChar(order, "SellPositionEffect", &order_req.SellPositionEffect);
	getChar(order, "AddOneIsValid", &order_req.AddOneIsValid);
	getDouble(order, "OrderBuyPrice", &order_req.OrderBuyPrice);
	getDouble(order, "OrderSellPrice", &order_req.OrderSellPrice);
	getUnsignedInt(order, "OrderBuyQty", &order_req.OrderBuyQty);
	getUnsignedInt(order, "OrderSellQty", &order_req.OrderSellQty);
	getInt(order, "RefInt", &order_req.RefInt);
	getDouble(order, "RefDouble", &order_req.RefDouble);
	getString(order, "RefString", order_req.RefString);
	getString(order, "Remark", order_req.Remark);
	int i = this->api->InsertHKMarketOrder(&session, &ClientBuyOrderNo_buf, &ClientSellOrderNo_buf, &order_req);
	return i;
};

int TdApi::cancelHKMarketOrder(const dict &order)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPIOrderMarketDeleteReq order_req = {};
	getChar(order, "ServerFlag", &order_req.ServerFlag);
	getString(order, "OrderBuyNo", order_req.OrderBuyNo);
	getString(order, "OrderSellNo", order_req.OrderSellNo);
	int i = this->api->CancelHKMarketOrder(&session, &order_req);
	return i;
};

int TdApi::orderLocalRemove(const dict &order)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPIOrderLocalRemoveReq order_req = {};
	getChar(order, "ServerFlag", &order_req.ServerFlag);
	getString(order, "OrderNo", order_req.OrderNo);
	int i = this->api->OrderLocalRemove(&session, &order_req);
	return i;
};

int TdApi::orderLocalInput(const dict &order)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPIOrderLocalInputReq order_req = {};
	getString(order, "AccountNo", order_req.AccountNo);
	getString(order, "ExchangeNo", order_req.ExchangeNo);
	getChar(order, "CommodityType", &order_req.CommodityType);
	getString(order, "CommodityNo", order_req.CommodityNo);
	getString(order, "ContractNo", order_req.ContractNo);
	getString(order, "StrikePrice", order_req.StrikePrice);
	getChar(order, "CallOrPutFlag", &order_req.CallOrPutFlag);
	getString(order, "ContractNo2", order_req.ContractNo2);
	getString(order, "StrikePrice2", order_req.StrikePrice2);
	getChar(order, "CallOrPutFlag2", &order_req.CallOrPutFlag2);
	getChar(order, "OrderType", &order_req.OrderType);
	getChar(order, "OrderSource", &order_req.OrderSource);
	getChar(order, "TimeInForce", &order_req.TimeInForce);
	getString(order, "ExpireTime", order_req.ExpireTime);
	getChar(order, "IsRiskOrder", &order_req.IsRiskOrder);
	getChar(order, "OrderSide", &order_req.OrderSide);
	getChar(order, "PositionEffect", &order_req.PositionEffect);
	getChar(order, "PositionEffect2", &order_req.PositionEffect2);
	getString(order, "InquiryNo", order_req.InquiryNo);
	getChar(order, "HedgeFlag", &order_req.HedgeFlag);
	getDouble(order, "OrderPrice", &order_req.OrderPrice);
	getDouble(order, "OrderPrice2", &order_req.OrderPrice2);
	getDouble(order, "StopPrice", &order_req.StopPrice);
	getUnsignedInt(order, "OrderQty", &order_req.OrderQty);
	getUnsignedInt(order, "OrderMinQty", &order_req.OrderMinQty);
	getString(order, "OrderSystemNo", order_req.OrderSystemNo);
	getString(order, "OrderExchangeSystemNo", order_req.OrderExchangeSystemNo);
	getString(order, "UpperNo", order_req.UpperNo);
	getDouble(order, "OrderMatchPrice", &order_req.OrderMatchPrice);
	getDouble(order, "OrderMatchPrice2", &order_req.OrderMatchPrice2);
	getUnsignedInt(order, "OrderMatchQty", &order_req.OrderMatchQty);
	getUnsignedInt(order, "OrderMatchQty2", &order_req.OrderMatchQty2);
	getChar(order, "OrderState", &order_req.OrderState);
	getChar(order, "IsAddOne", &order_req.IsAddOne);
	getString(order, "LowerAccount", order_req.LowerAccount);
	int i = this->api->OrderLocalInput(&session, &order_req);
	return i;
};

int TdApi::orderLocalModify(const dict &order)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPIOrderLocalModifyReq order_req = {};
	// TODO: unsupported type "TapAPIOrderLocalInputReq" for field "req"
	getChar(order, "ServerFlag", &order_req.ServerFlag);
	getString(order, "OrderNo", order_req.OrderNo);
	int i = this->api->OrderLocalModify(&session, &order_req);
	return i;
};

int TdApi::orderLocalTransfer(const dict &order)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPIOrderLocalTransferReq order_req = {};
	getString(order, "AccountNo", order_req.AccountNo);
	getChar(order, "ServerFlag", &order_req.ServerFlag);
	getString(order, "OrderNo", order_req.OrderNo);
	int i = this->api->OrderLocalTransfer(&session, &order_req);
	return i;
};

int TdApi::fillLocalInput(const dict &fill)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPIFillLocalInputReq fill_req = {};
	getString(fill, "AccountNo", fill_req.AccountNo);
	getString(fill, "ExchangeNo", fill_req.ExchangeNo);
	getChar(fill, "CommodityType", &fill_req.CommodityType);
	getString(fill, "CommodityNo", fill_req.CommodityNo);
	getString(fill, "ContractNo", fill_req.ContractNo);
	getString(fill, "StrikePrice", fill_req.StrikePrice);
	getChar(fill, "CallOrPutFlag", &fill_req.CallOrPutFlag);
	getChar(fill, "MatchSide", &fill_req.MatchSide);
	getChar(fill, "PositionEffect", &fill_req.PositionEffect);
	getChar(fill, "HedgeFlag", &fill_req.HedgeFlag);
	getDouble(fill, "MatchPrice", &fill_req.MatchPrice);
	getUnsignedInt(fill, "MatchQty", &fill_req.MatchQty);
	getString(fill, "OrderSystemNo", fill_req.OrderSystemNo);
	getString(fill, "UpperMatchNo", fill_req.UpperMatchNo);
	getString(fill, "MatchDateTime", fill_req.MatchDateTime);
	getString(fill, "UpperMatchDateTime", fill_req.UpperMatchDateTime);
	getString(fill, "UpperNo", fill_req.UpperNo);
	getChar(fill, "IsAddOne", &fill_req.IsAddOne);
	getString(fill, "FeeCurrencyGroup", fill_req.FeeCurrencyGroup);
	getString(fill, "FeeCurrency", fill_req.FeeCurrency);
	getDouble(fill, "FeeValue", &fill_req.FeeValue);
	getChar(fill, "IsManualFee", &fill_req.IsManualFee);
	getDouble(fill, "ClosePositionPrice", &fill_req.ClosePositionPrice);
	int i = this->api->FillLocalInput(&session, &fill_req);
	return i;
};

int TdApi::fillLocalRemove(const dict &fill)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPIFillLocalRemoveReq fill_req = {};
	getChar(fill, "ServerFlag", &fill_req.ServerFlag);
	getString(fill, "MatchNo", fill_req.MatchNo);
	int i = this->api->FillLocalRemove(&session, &fill_req);
	return i;
};

int TdApi::qrySpotLock(const dict &qryReq)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPISpotLockQryReq qryReq_req = {};
	getString(qryReq, "AccountNo", qryReq_req.AccountNo);
	int i = this->api->QrySpotLock(&session, &qryReq_req);
	return i;
};

int TdApi::submitUserLoginInfo(const dict &qryReq)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPISubmitUserLoginInfo qryReq_req = {};
	getString(qryReq, "UserNo", qryReq_req.UserNo);
	getString(qryReq, "GatherInfo", qryReq_req.GatherInfo);
	getString(qryReq, "ClientLoginIP", qryReq_req.ClientLoginIP);
	getUnsignedInt(qryReq, "ClientLoginPort", &qryReq_req.ClientLoginPort);
	getString(qryReq, "ClientLoginDateTime", qryReq_req.ClientLoginDateTime);
	getString(qryReq, "ClientAppID", qryReq_req.ClientAppID);
	getUnsignedInt(qryReq, "AuthKeyVersion", &qryReq_req.AuthKeyVersion);
	getChar(qryReq, "AbnormalNo", &qryReq_req.AbnormalNo);
	int i = this->api->SubmitUserLoginInfo(&session, &qryReq_req);
	return i;
};

int TdApi::insertSpecialOrder(const string &clientorderno, const dict &order)
{
	ITapTrade::TAPIUINT32 session;
	char clientorderno_buf[51] = {};
	strncpy(clientorderno_buf, clientorderno.c_str(), 51 - 1);
	clientorderno_buf[51 - 1] = '\0';
	ITapTrade::TapAPISpecialOrderInsertReq order_req = {};
	getString(order, "AccountNo", order_req.AccountNo);
	getChar(order, "SpecialOrderType", &order_req.SpecialOrderType);
	getChar(order, "OrderSource", &order_req.OrderSource);
	getString(order, "CombineNo", order_req.CombineNo);
	getUnsignedInt(order, "OrderQty", &order_req.OrderQty);
	getString(order, "ExchangeNo", order_req.ExchangeNo);
	getChar(order, "CommodityType", &order_req.CommodityType);
	getString(order, "CommodityNo", order_req.CommodityNo);
	getString(order, "ContractNo", order_req.ContractNo);
	getString(order, "StrikePrice", order_req.StrikePrice);
	getChar(order, "CallOrPutFlag", &order_req.CallOrPutFlag);
	getChar(order, "OrderSide1", &order_req.OrderSide1);
	getChar(order, "HedgeFlag1", &order_req.HedgeFlag1);
	getString(order, "ContractNo2", order_req.ContractNo2);
	getString(order, "StrikePrice2", order_req.StrikePrice2);
	getChar(order, "CallOrPutFlag2", &order_req.CallOrPutFlag2);
	int i = this->api->InsertSpecialOrder(&session, &clientorderno_buf, &order_req);
	return i;
};

int TdApi::qrySpecialOrder(const dict &qryReq)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPISpecialOrderQryReq qryReq_req = {};
	getString(qryReq, "AccountNo", qryReq_req.AccountNo);
	getString(qryReq, "OrderNo", qryReq_req.OrderNo);
	int i = this->api->QrySpecialOrder(&session, &qryReq_req);
	return i;
};

int TdApi::qryCombinePosition(const dict &qryReq)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPICombinePositionQryReq qryReq_req = {};
	getString(qryReq, "AccountNo", qryReq_req.AccountNo);
	int i = this->api->QryCombinePosition(&session, &qryReq_req);
	return i;
};

int TdApi::qryUserTrustDevice(const dict &qryReq)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPIUserTrustDeviceQryReq qryReq_req = {};
	int i = this->api->QryUserTrustDevice(&session, &qryReq_req);
	return i;
};

int TdApi::addUserTrustDevice(const dict &qryReq)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPIUserTrustDeviceAddReq qryReq_req = {};
	int i = this->api->AddUserTrustDevice(&session, &qryReq_req);
	return i;
};

int TdApi::delUserTrustDevice(const dict &qryReq)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPIUserTrustDeviceDelReq qryReq_req = {};
	getString(qryReq, "LicenseNo", qryReq_req.LicenseNo);
	getString(qryReq, "Mac", qryReq_req.Mac);
	int i = this->api->DelUserTrustDevice(&session, &qryReq_req);
	return i;
};

int TdApi::selfPasswordInfoOperate(const dict &qryReq)
{
	ITapTrade::TapAPISelfPasswordInfoOperateReq qryReq_req = {};
	getString(qryReq, "UserNo", qryReq_req.UserNo);
	getChar(qryReq, "OpreateType", &qryReq_req.OpreateType);
	int i = this->api->SelfPasswordInfoOperate(&qryReq_req);
	return i;
};

int TdApi::verificateIdentityInfo(const dict &qryReq)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPIVerifyIdentityReq qryReq_req = {};
	getChar(qryReq, "CertificateType", &qryReq_req.CertificateType);
	getString(qryReq, "CertificateNo", qryReq_req.CertificateNo);
	getString(qryReq, "EMail", qryReq_req.EMail);
	getString(qryReq, "PhoneNo", qryReq_req.PhoneNo);
	int i = this->api->VerificateIdentityInfo(&session, &qryReq_req);
	return i;
};

int TdApi::resetPassword(const dict &qryReq)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPIResetPasswordReq qryReq_req = {};
	getString(qryReq, "NewPassword", qryReq_req.NewPassword);
	int i = this->api->ResetPassword(&session, &qryReq_req);
	return i;
};

int TdApi::qryExchangeStateInfo(const dict &qryReq)
{
	ITapTrade::TAPIUINT32 session;
	ITapTrade::TapAPIExchangeStateInfoQryReq qryReq_req = {};
	int i = this->api->QryExchangeStateInfo(&session, &qryReq_req);
	return i;
};

int TdApi::createITapTradeAPI(const dict &req)
                    {
                    ITapTrade::TAPIINT32 iResult = 0;
                    ITapTrade::TapAPIApplicationInfo appInfo;
                    memset(&appInfo, 0, sizeof(appInfo));
                    	getString(req, "AuthCode", appInfo.AuthCode);
	getString(req, "KeyOperationLogPath", appInfo.KeyOperationLogPath);
	getChar(req, "LogLevel", &appInfo.LogLevel);
	getString(req, "APPID", appInfo.APPID);
	getInt(req, "ReConnectCount", &appInfo.ReConnectCount);
	getInt(req, "ReConnectSeconds", &appInfo.ReConnectSeconds);

	this->api = CreateITapTradeAPI(&appInfo, iResult);
                    	if (this->api)
                    	{
                    		this->api->SetAPINotify(this);
                    	}
                    	return iResult;
                    };
                    string TdApi::getITapTradeAPIVersion()
                    {
                    const char *v = GetITapTradeAPIVersion();
                    return std::string(v ? v : "");
                    };
                    string TdApi::getITapErrorDescribe(int errorCode)
                    {
                    const char *desc = GetITapErrorDescribe(errorCode);
                    return std::string(desc ? desc : "");
                    };
                    void TdApi::init()
            {
            this->active = true;
            this->task_thread = thread(&TdApi::processTask, this);
            };

///-------------------------------------------------------------------------------------
///pybind11封装
///-------------------------------------------------------------------------------------

class PyTdApi : public TdApi
{
public:
    using TdApi::TdApi;

void onConnect(const string &HostAddress) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onConnect, HostAddress);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspLogin(int errorCode, const dict &loginRspInfo) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspLogin, errorCode, loginRspInfo);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnContactInfo(int errorCode, char isLast, const string &ContactInfo) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnContactInfo, errorCode, isLast, ContactInfo);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspRequestVertificateCode(unsigned int sessionID, int errorCode, const dict &rsp) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspRequestVertificateCode, sessionID, errorCode, rsp);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onExpriationDate(const string &date, int days) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onExpriationDate, date, days);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onAPIReady(int errorCode) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onAPIReady, errorCode);
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
		PYBIND11_OVERLOAD(void, TdApi, onDisconnect, reasonCode);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspChangePassword(unsigned int sessionID, int errorCode) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspChangePassword, sessionID, errorCode);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspAuthPassword(unsigned int sessionID, int errorCode) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspAuthPassword, sessionID, errorCode);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryTradingDate(unsigned int sessionID, int errorCode, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryTradingDate, sessionID, errorCode, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSetReservedInfo(unsigned int sessionID, int errorCode, const string &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspSetReservedInfo, sessionID, errorCode, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryAccount(unsigned int sessionID, unsigned int errorCode, char isLast, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryAccount, sessionID, errorCode, isLast, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryFund(unsigned int sessionID, int errorCode, char isLast, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryFund, sessionID, errorCode, isLast, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnFund(const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnFund, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryExchange(unsigned int sessionID, int errorCode, char isLast, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryExchange, sessionID, errorCode, isLast, info);
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
		PYBIND11_OVERLOAD(void, TdApi, onRspQryCommodity, sessionID, errorCode, isLast, info);
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
		PYBIND11_OVERLOAD(void, TdApi, onRspQryContract, sessionID, errorCode, isLast, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnContract(const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnContract, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspOrderAction(unsigned int sessionID, int errorCode, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspOrderAction, sessionID, errorCode, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnOrder(const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnOrder, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryOrder(unsigned int sessionID, int errorCode, char isLast, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryOrder, sessionID, errorCode, isLast, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryOrderProcess(unsigned int sessionID, int errorCode, char isLast, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryOrderProcess, sessionID, errorCode, isLast, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryFill(unsigned int sessionID, int errorCode, char isLast, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryFill, sessionID, errorCode, isLast, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnFill(const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnFill, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryPosition(unsigned int sessionID, int errorCode, char isLast, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryPosition, sessionID, errorCode, isLast, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnPosition(const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnPosition, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryPositionSummary(unsigned int sessionID, int errorCode, char isLast, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryPositionSummary, sessionID, errorCode, isLast, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnPositionSummary(const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnPositionSummary, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnPositionProfit(const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnPositionProfit, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryCurrency(unsigned int sessionID, int errorCode, char isLast, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryCurrency, sessionID, errorCode, isLast, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryTradeMessage(unsigned int sessionID, int errorCode, char isLast, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryTradeMessage, sessionID, errorCode, isLast, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnTradeMessage(const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnTradeMessage, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryHisOrder(unsigned int sessionID, int errorCode, char isLast, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryHisOrder, sessionID, errorCode, isLast, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryHisOrderProcess(unsigned int sessionID, int errorCode, char isLast, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryHisOrderProcess, sessionID, errorCode, isLast, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryHisMatch(unsigned int sessionID, int errorCode, char isLast, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryHisMatch, sessionID, errorCode, isLast, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryHisPosition(unsigned int sessionID, int errorCode, char isLast, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryHisPosition, sessionID, errorCode, isLast, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryHisDelivery(unsigned int sessionID, int errorCode, char isLast, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryHisDelivery, sessionID, errorCode, isLast, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryHisFund(unsigned int sessionID, int errorCode, char isLast, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryHisFund, sessionID, errorCode, isLast, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryAccountCashAdjust(unsigned int sessionID, int errorCode, char isLast, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryAccountCashAdjust, sessionID, errorCode, isLast, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryBill(unsigned int sessionID, int errorCode, char isLast, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryBill, sessionID, errorCode, isLast, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryAccountFeeRent(unsigned int sessionID, int errorCode, char isLast, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryAccountFeeRent, sessionID, errorCode, isLast, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryAccountMarginRent(unsigned int sessionID, int errorCode, char isLast, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryAccountMarginRent, sessionID, errorCode, isLast, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspHKMarketOrderInsert(unsigned int sessionID, int errorCode, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspHKMarketOrderInsert, sessionID, errorCode, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspHKMarketOrderDelete(unsigned int sessionID, int errorCode, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspHKMarketOrderDelete, sessionID, errorCode, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onHKMarketQuoteNotice(const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onHKMarketQuoteNotice, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspOrderLocalRemove(unsigned int sessionID, int errorCode, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspOrderLocalRemove, sessionID, errorCode, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspOrderLocalInput(unsigned int sessionID, int errorCode, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspOrderLocalInput, sessionID, errorCode, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspOrderLocalModify(unsigned int sessionID, int errorCode, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspOrderLocalModify, sessionID, errorCode, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspOrderLocalTransfer(unsigned int sessionID, int errorCode, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspOrderLocalTransfer, sessionID, errorCode, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspFillLocalInput(unsigned int sessionID, int errorCode, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspFillLocalInput, sessionID, errorCode, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspFillLocalRemove(unsigned int sessionID, int errorCode, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspFillLocalRemove, sessionID, errorCode, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQrySpotLock(unsigned int sessionID, int errorCode, char isLast, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQrySpotLock, sessionID, errorCode, isLast, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnSpotLock(const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnSpotLock, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSubmitUserLoginInfo(unsigned int sessionID, int errorCode, char isLast, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspSubmitUserLoginInfo, sessionID, errorCode, isLast, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSpecialOrderAction(unsigned int sessionID, int errorCode, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspSpecialOrderAction, sessionID, errorCode, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnSpecialOrder(const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnSpecialOrder, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQrySpecialOrder(unsigned int sessionID, int errorCode, char isLast, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQrySpecialOrder, sessionID, errorCode, isLast, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryCombinePosition(unsigned int sessionID, int errorCode, char isLast, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryCombinePosition, sessionID, errorCode, isLast, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnCombinePosition(const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnCombinePosition, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryUserTrustDevice(unsigned int sessionID, int errorCode, char isLast, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryUserTrustDevice, sessionID, errorCode, isLast, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspAddUserTrustDevice(unsigned int sessionID, int errorCode, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspAddUserTrustDevice, sessionID, errorCode, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspDelUserTrustDevice(unsigned int sessionID, int errorCode, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspDelUserTrustDevice, sessionID, errorCode, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnAddUserTrustDevice(const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnAddUserTrustDevice, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnDelUserTrustDevice(const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnDelUserTrustDevice, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryIPOInfo(unsigned int sessionID, int errorCode, char isLast, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryIPOInfo, sessionID, errorCode, isLast, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryIPOStockQty(unsigned int sessionID, int errorCode, char isLast, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryIPOStockQty, sessionID, errorCode, isLast, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryAccountIPO(unsigned int sessionID, int errorCode, char isLast, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryAccountIPO, sessionID, errorCode, isLast, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspAddAccountIPO(unsigned int sessionID, int errorCode, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspAddAccountIPO, sessionID, errorCode, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspCancelAccountIPO(unsigned int sessionID, int errorCode, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspCancelAccountIPO, sessionID, errorCode, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnAddAccountIPO(const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnAddAccountIPO, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnCancelAccountIPO(const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnCancelAccountIPO, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSelfPasswordInfoOperate(int errorCode) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspSelfPasswordInfoOperate, errorCode);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspVerificateIdentityInfo(unsigned int sessionID, int errorCode) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspVerificateIdentityInfo, sessionID, errorCode);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSetVertificateCode(unsigned int sessionID, int errorCode) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspSetVertificateCode, sessionID, errorCode);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspResetPassword(unsigned int sessionID, int errorCode) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspResetPassword, sessionID, errorCode);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryExchangeStateInfo(unsigned int sessionID, int errorCode, char isLast, const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryExchangeStateInfo, sessionID, errorCode, isLast, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnExchangeStateInfo(const dict &info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnExchangeStateInfo, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};
};

PYBIND11_MODULE(taptd, m)
{
// TODO: FreeITapTradeAPI has parameters, manual binding recommended
	// m.def("freeITapTradeAPI", &FreeITapTradeAPI);
    class_<TdApi, PyTdApi> taptd(m, "TdApi", module_local());
    taptd
        .def(init<>())
.def("setAPINotify", &TdApi::setAPINotify)
	.def("setHostAddress", &TdApi::setHostAddress)
	.def("login", &TdApi::login)
	.def("requestVertificateCode", &TdApi::requestVertificateCode)
	.def("setVertificateCode", &TdApi::setVertificateCode)
	.def("disconnect", &TdApi::disconnect)
	.def("changePassword", &TdApi::changePassword)
	.def("authPassword", &TdApi::authPassword)
	.def("haveCertainRight", &TdApi::haveCertainRight)
	.def("qryTradingDate", &TdApi::qryTradingDate)
	.def("setReservedInfo", &TdApi::setReservedInfo)
	.def("qryAccount", &TdApi::qryAccount)
	.def("qryFund", &TdApi::qryFund)
	.def("qryExchange", &TdApi::qryExchange)
	.def("qryCommodity", &TdApi::qryCommodity)
	.def("qryContract", &TdApi::qryContract)
	.def("insertOrder", &TdApi::insertOrder)
	.def("cancelOrder", &TdApi::cancelOrder)
	.def("amendOrder", &TdApi::amendOrder)
	.def("activateOrder", &TdApi::activateOrder)
	.def("qryOrder", &TdApi::qryOrder)
	.def("qryOrderProcess", &TdApi::qryOrderProcess)
	.def("qryFill", &TdApi::qryFill)
	.def("qryPosition", &TdApi::qryPosition)
	.def("qryPositionSummary", &TdApi::qryPositionSummary)
	.def("qryCurrency", &TdApi::qryCurrency)
	.def("qryAccountCashAdjust", &TdApi::qryAccountCashAdjust)
	.def("qryTradeMessage", &TdApi::qryTradeMessage)
	.def("qryBill", &TdApi::qryBill)
	.def("qryHisOrder", &TdApi::qryHisOrder)
	.def("qryHisOrderProcess", &TdApi::qryHisOrderProcess)
	.def("qryHisMatch", &TdApi::qryHisMatch)
	.def("qryHisPosition", &TdApi::qryHisPosition)
	.def("qryHisDelivery", &TdApi::qryHisDelivery)
	.def("qryHisFund", &TdApi::qryHisFund)
	.def("qryAccountFeeRent", &TdApi::qryAccountFeeRent)
	.def("qryAccountMarginRent", &TdApi::qryAccountMarginRent)
	.def("insertHKMarketOrder", &TdApi::insertHKMarketOrder)
	.def("cancelHKMarketOrder", &TdApi::cancelHKMarketOrder)
	.def("orderLocalRemove", &TdApi::orderLocalRemove)
	.def("orderLocalInput", &TdApi::orderLocalInput)
	.def("orderLocalModify", &TdApi::orderLocalModify)
	.def("orderLocalTransfer", &TdApi::orderLocalTransfer)
	.def("fillLocalInput", &TdApi::fillLocalInput)
	.def("fillLocalRemove", &TdApi::fillLocalRemove)
	.def("qrySpotLock", &TdApi::qrySpotLock)
	.def("submitUserLoginInfo", &TdApi::submitUserLoginInfo)
	.def("insertSpecialOrder", &TdApi::insertSpecialOrder)
	.def("qrySpecialOrder", &TdApi::qrySpecialOrder)
	.def("qryCombinePosition", &TdApi::qryCombinePosition)
	.def("qryUserTrustDevice", &TdApi::qryUserTrustDevice)
	.def("addUserTrustDevice", &TdApi::addUserTrustDevice)
	.def("delUserTrustDevice", &TdApi::delUserTrustDevice)
	.def("selfPasswordInfoOperate", &TdApi::selfPasswordInfoOperate)
	.def("verificateIdentityInfo", &TdApi::verificateIdentityInfo)
	.def("resetPassword", &TdApi::resetPassword)
	.def("qryExchangeStateInfo", &TdApi::qryExchangeStateInfo)

	.def("onConnect", &TdApi::onConnect)
	.def("onRspLogin", &TdApi::onRspLogin)
	.def("onRtnContactInfo", &TdApi::onRtnContactInfo)
	.def("onRspRequestVertificateCode", &TdApi::onRspRequestVertificateCode)
	.def("onExpriationDate", &TdApi::onExpriationDate)
	.def("onAPIReady", &TdApi::onAPIReady)
	.def("onDisconnect", &TdApi::onDisconnect)
	.def("onRspChangePassword", &TdApi::onRspChangePassword)
	.def("onRspAuthPassword", &TdApi::onRspAuthPassword)
	.def("onRspQryTradingDate", &TdApi::onRspQryTradingDate)
	.def("onRspSetReservedInfo", &TdApi::onRspSetReservedInfo)
	.def("onRspQryAccount", &TdApi::onRspQryAccount)
	.def("onRspQryFund", &TdApi::onRspQryFund)
	.def("onRtnFund", &TdApi::onRtnFund)
	.def("onRspQryExchange", &TdApi::onRspQryExchange)
	.def("onRspQryCommodity", &TdApi::onRspQryCommodity)
	.def("onRspQryContract", &TdApi::onRspQryContract)
	.def("onRtnContract", &TdApi::onRtnContract)
	.def("onRspOrderAction", &TdApi::onRspOrderAction)
	.def("onRtnOrder", &TdApi::onRtnOrder)
	.def("onRspQryOrder", &TdApi::onRspQryOrder)
	.def("onRspQryOrderProcess", &TdApi::onRspQryOrderProcess)
	.def("onRspQryFill", &TdApi::onRspQryFill)
	.def("onRtnFill", &TdApi::onRtnFill)
	.def("onRspQryPosition", &TdApi::onRspQryPosition)
	.def("onRtnPosition", &TdApi::onRtnPosition)
	.def("onRspQryPositionSummary", &TdApi::onRspQryPositionSummary)
	.def("onRtnPositionSummary", &TdApi::onRtnPositionSummary)
	.def("onRtnPositionProfit", &TdApi::onRtnPositionProfit)
	.def("onRspQryCurrency", &TdApi::onRspQryCurrency)
	.def("onRspQryTradeMessage", &TdApi::onRspQryTradeMessage)
	.def("onRtnTradeMessage", &TdApi::onRtnTradeMessage)
	.def("onRspQryHisOrder", &TdApi::onRspQryHisOrder)
	.def("onRspQryHisOrderProcess", &TdApi::onRspQryHisOrderProcess)
	.def("onRspQryHisMatch", &TdApi::onRspQryHisMatch)
	.def("onRspQryHisPosition", &TdApi::onRspQryHisPosition)
	.def("onRspQryHisDelivery", &TdApi::onRspQryHisDelivery)
	.def("onRspQryHisFund", &TdApi::onRspQryHisFund)
	.def("onRspQryAccountCashAdjust", &TdApi::onRspQryAccountCashAdjust)
	.def("onRspQryBill", &TdApi::onRspQryBill)
	.def("onRspQryAccountFeeRent", &TdApi::onRspQryAccountFeeRent)
	.def("onRspQryAccountMarginRent", &TdApi::onRspQryAccountMarginRent)
	.def("onRspHKMarketOrderInsert", &TdApi::onRspHKMarketOrderInsert)
	.def("onRspHKMarketOrderDelete", &TdApi::onRspHKMarketOrderDelete)
	.def("onHKMarketQuoteNotice", &TdApi::onHKMarketQuoteNotice)
	.def("onRspOrderLocalRemove", &TdApi::onRspOrderLocalRemove)
	.def("onRspOrderLocalInput", &TdApi::onRspOrderLocalInput)
	.def("onRspOrderLocalModify", &TdApi::onRspOrderLocalModify)
	.def("onRspOrderLocalTransfer", &TdApi::onRspOrderLocalTransfer)
	.def("onRspFillLocalInput", &TdApi::onRspFillLocalInput)
	.def("onRspFillLocalRemove", &TdApi::onRspFillLocalRemove)
	.def("onRspQrySpotLock", &TdApi::onRspQrySpotLock)
	.def("onRtnSpotLock", &TdApi::onRtnSpotLock)
	.def("onRspSubmitUserLoginInfo", &TdApi::onRspSubmitUserLoginInfo)
	.def("onRspSpecialOrderAction", &TdApi::onRspSpecialOrderAction)
	.def("onRtnSpecialOrder", &TdApi::onRtnSpecialOrder)
	.def("onRspQrySpecialOrder", &TdApi::onRspQrySpecialOrder)
	.def("onRspQryCombinePosition", &TdApi::onRspQryCombinePosition)
	.def("onRtnCombinePosition", &TdApi::onRtnCombinePosition)
	.def("onRspQryUserTrustDevice", &TdApi::onRspQryUserTrustDevice)
	.def("onRspAddUserTrustDevice", &TdApi::onRspAddUserTrustDevice)
	.def("onRspDelUserTrustDevice", &TdApi::onRspDelUserTrustDevice)
	.def("onRtnAddUserTrustDevice", &TdApi::onRtnAddUserTrustDevice)
	.def("onRtnDelUserTrustDevice", &TdApi::onRtnDelUserTrustDevice)
	.def("onRspQryIPOInfo", &TdApi::onRspQryIPOInfo)
	.def("onRspQryIPOStockQty", &TdApi::onRspQryIPOStockQty)
	.def("onRspQryAccountIPO", &TdApi::onRspQryAccountIPO)
	.def("onRspAddAccountIPO", &TdApi::onRspAddAccountIPO)
	.def("onRspCancelAccountIPO", &TdApi::onRspCancelAccountIPO)
	.def("onRtnAddAccountIPO", &TdApi::onRtnAddAccountIPO)
	.def("onRtnCancelAccountIPO", &TdApi::onRtnCancelAccountIPO)
	.def("onRspSelfPasswordInfoOperate", &TdApi::onRspSelfPasswordInfoOperate)
	.def("onRspVerificateIdentityInfo", &TdApi::onRspVerificateIdentityInfo)
	.def("onRspSetVertificateCode", &TdApi::onRspSetVertificateCode)
	.def("onRspResetPassword", &TdApi::onRspResetPassword)
	.def("onRspQryExchangeStateInfo", &TdApi::onRspQryExchangeStateInfo)
	.def("onRtnExchangeStateInfo", &TdApi::onRtnExchangeStateInfo)

	.def("createITapTradeAPI", &TdApi::createITapTradeAPI)
	.def("getITapTradeAPIVersion", &TdApi::getITapTradeAPIVersion)
	.def("getITapErrorDescribe", &TdApi::getITapErrorDescribe)
	.def("init", &TdApi::init)
;
}