#include "../../../tap.h"
#include "pybind11/pybind11.h"
#include "iTapTradeAPI.h"

using namespace pybind11;

using namespace ITapTrade;

// 常量定义（若有）
#define ONCONNECT 0
#define ONRSPLOGIN 1
#define ONRTNCONTACTINFO 2
#define ONRSPREQUESTVERTIFICATECODE 3
#define ONEXPRIATIONDATE 4
#define ONAPIREADY 5
#define ONDISCONNECT 6
#define ONRSPCHANGEPASSWORD 7
#define ONRSPAUTHPASSWORD 8
#define ONRSPQRYTRADINGDATE 9
#define ONRSPSETRESERVEDINFO 10
#define ONRSPQRYACCOUNT 11
#define ONRSPQRYFUND 12
#define ONRTNFUND 13
#define ONRSPQRYEXCHANGE 14
#define ONRSPQRYCOMMODITY 15
#define ONRSPQRYCONTRACT 16
#define ONRTNCONTRACT 17
#define ONRSPORDERACTION 18
#define ONRTNORDER 19
#define ONRSPQRYORDER 20
#define ONRSPQRYORDERPROCESS 21
#define ONRSPQRYFILL 22
#define ONRTNFILL 23
#define ONRSPQRYPOSITION 24
#define ONRTNPOSITION 25
#define ONRSPQRYPOSITIONSUMMARY 26
#define ONRTNPOSITIONSUMMARY 27
#define ONRTNPOSITIONPROFIT 28
#define ONRSPQRYCURRENCY 29
#define ONRSPQRYTRADEMESSAGE 30
#define ONRTNTRADEMESSAGE 31
#define ONRSPQRYHISORDER 32
#define ONRSPQRYHISORDERPROCESS 33
#define ONRSPQRYHISMATCH 34
#define ONRSPQRYHISPOSITION 35
#define ONRSPQRYHISDELIVERY 36
#define ONRSPQRYHISFUND 37
#define ONRSPQRYACCOUNTCASHADJUST 38
#define ONRSPQRYBILL 39
#define ONRSPQRYACCOUNTFEERENT 40
#define ONRSPQRYACCOUNTMARGINRENT 41
#define ONRSPHKMARKETORDERINSERT 42
#define ONRSPHKMARKETORDERDELETE 43
#define ONHKMARKETQUOTENOTICE 44
#define ONRSPORDERLOCALREMOVE 45
#define ONRSPORDERLOCALINPUT 46
#define ONRSPORDERLOCALMODIFY 47
#define ONRSPORDERLOCALTRANSFER 48
#define ONRSPFILLLOCALINPUT 49
#define ONRSPFILLLOCALREMOVE 50
#define ONRSPQRYSPOTLOCK 51
#define ONRTNSPOTLOCK 52
#define ONRSPSUBMITUSERLOGININFO 53
#define ONRSPSPECIALORDERACTION 54
#define ONRTNSPECIALORDER 55
#define ONRSPQRYSPECIALORDER 56
#define ONRSPQRYCOMBINEPOSITION 57
#define ONRTNCOMBINEPOSITION 58
#define ONRSPQRYUSERTRUSTDEVICE 59
#define ONRSPADDUSERTRUSTDEVICE 60
#define ONRSPDELUSERTRUSTDEVICE 61
#define ONRTNADDUSERTRUSTDEVICE 62
#define ONRTNDELUSERTRUSTDEVICE 63
#define ONRSPQRYIPOINFO 64
#define ONRSPQRYIPOSTOCKQTY 65
#define ONRSPQRYACCOUNTIPO 66
#define ONRSPADDACCOUNTIPO 67
#define ONRSPCANCELACCOUNTIPO 68
#define ONRTNADDACCOUNTIPO 69
#define ONRTNCANCELACCOUNTIPO 70
#define ONRSPSELFPASSWORDINFOOPERATE 71
#define ONRSPVERIFICATEIDENTITYINFO 72
#define ONRSPSETVERTIFICATECODE 73
#define ONRSPRESETPASSWORD 74
#define ONRSPQRYEXCHANGESTATEINFO 75
#define ONRTNEXCHANGESTATEINFO 76

///-------------------------------------------------------------------------------------
///C++ SPI的回调函数的继承实现
///-------------------------------------------------------------------------------------

class TdApi : public ITapTrade::ITapTradeAPINotify
{
private:
    ITapTrade::ITapTradeAPI* api;
    thread task_thread;
    TaskQueue task_queue;
    bool active = false;

public:
    TdApi() {}
    virtual ~TdApi()
    {
        if (this->active)
            this->exit();
    }

    void exit()
    {
        this->active = false;
        this->task_queue.close();
        if (this->task_thread.joinable())
            this->task_thread.join();
    }

    // 从基类继承的回调函数
    virtual void OnConnect(const ITapTrade::TAPISTR_40 HostAddress);
    virtual void OnRspLogin(ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPITradeLoginRspInfo *loginRspInfo);
    virtual void OnRtnContactInfo(ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TAPISTR_40 ContactInfo);
    virtual void OnRspRequestVertificateCode(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const TapAPIRequestVertificateCodeRsp *rsp);
    virtual void OnExpriationDate(ITapTrade::TAPIDATE date, int days);
    virtual void OnAPIReady(ITapTrade::TAPIINT32 errorCode);
    virtual void OnDisconnect(ITapTrade::TAPIINT32 reasonCode);
    virtual void OnRspChangePassword(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode);
    virtual void OnRspAuthPassword(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode);
    virtual void OnRspQryTradingDate(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPITradingCalendarQryRsp *info);
    virtual void OnRspSetReservedInfo(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TAPISTR_50 info);
    virtual void OnRspQryAccount(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIUINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountInfo *info);
    virtual void OnRspQryFund(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIFundData *info);
    virtual void OnRtnFund(const ITapTrade::TapAPIFundData *info);
    virtual void OnRspQryExchange(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIExchangeInfo *info);
    virtual void OnRspQryCommodity(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPICommodityInfo *info);
    virtual void OnRspQryContract(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPITradeContractInfo *info);
    virtual void OnRtnContract(const ITapTrade::TapAPITradeContractInfo *info);
    virtual void OnRspOrderAction(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderActionRsp *info);
    virtual void OnRtnOrder(const ITapTrade::TapAPIOrderInfoNotice *info);
    virtual void OnRspQryOrder(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIOrderInfo *info);
    virtual void OnRspQryOrderProcess(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIOrderInfo *info);
    virtual void OnRspQryFill(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIFillInfo *info);
    virtual void OnRtnFill(const ITapTrade::TapAPIFillInfo *info);
    virtual void OnRspQryPosition(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIPositionInfo *info);
    virtual void OnRtnPosition(const ITapTrade::TapAPIPositionInfo *info);
    virtual void OnRspQryPositionSummary(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIPositionSummary *info);
    virtual void OnRtnPositionSummary(const TapAPIPositionSummary *info);
    virtual void OnRtnPositionProfit(const ITapTrade::TapAPIPositionProfitNotice *info);
    virtual void OnRspQryCurrency(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPICurrencyInfo *info);
    virtual void OnRspQryTradeMessage(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPITradeMessage *info);
    virtual void OnRtnTradeMessage(const ITapTrade::TapAPITradeMessage *info);
    virtual void OnRspQryHisOrder(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisOrderQryRsp *info);
    virtual void OnRspQryHisOrderProcess(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisOrderProcessQryRsp *info);
    virtual void OnRspQryHisMatch(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisMatchQryRsp *info);
    virtual void OnRspQryHisPosition(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisPositionQryRsp *info);
    virtual void OnRspQryHisDelivery(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisDeliveryQryRsp *info);
    virtual void OnRspQryHisFund(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisFundQryRsp* info);
    virtual void OnRspQryAccountCashAdjust(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountCashAdjustQryRsp *info);
    virtual void OnRspQryBill(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIBillQryRsp *info);
    virtual void OnRspQryAccountFeeRent(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountFeeRentQryRsp *info);
    virtual void OnRspQryAccountMarginRent(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountMarginRentQryRsp *info);
    virtual void OnRspHKMarketOrderInsert(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderMarketInsertRsp *info);
    virtual void OnRspHKMarketOrderDelete(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderMarketDeleteRsp *info);
    virtual void OnHKMarketQuoteNotice(const ITapTrade::TapAPIOrderQuoteMarketNotice *info);
    virtual void OnRspOrderLocalRemove(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderLocalRemoveRsp *info);
    virtual void OnRspOrderLocalInput(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderLocalInputRsp *info);
    virtual void OnRspOrderLocalModify(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderLocalModifyRsp *info);
    virtual void OnRspOrderLocalTransfer(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderLocalTransferRsp *info);
    virtual void OnRspFillLocalInput(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIFillLocalInputRsp *info);
    virtual void OnRspFillLocalRemove(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIFillLocalRemoveRsp *info);
    virtual void OnRspQrySpotLock(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPISpotLockDataRsp *info);
    virtual void OnRtnSpotLock(const ITapTrade::TapAPISpotLockDataRsp *info);
    virtual void OnRspSubmitUserLoginInfo(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPISubmitUserLoginRspInfo * info);
    virtual void OnRspSpecialOrderAction(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPISpecialOrderInfo *info);
    virtual void OnRtnSpecialOrder(const ITapTrade::TapAPISpecialOrderInfo *info);
    virtual void OnRspQrySpecialOrder(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPISpecialOrderInfo *info);
    virtual void OnRspQryCombinePosition(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const  ITapTrade::TapAPICombinePositionInfo *info);
    virtual void OnRtnCombinePosition(const ITapTrade::TapAPICombinePositionInfo *info);
    virtual void OnRspQryUserTrustDevice(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const  ITapTrade::TapAPIUserTrustDeviceQryRsp *info);
    virtual void OnRspAddUserTrustDevice(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIUserTrustDeviceAddRsp *info);
    virtual void OnRspDelUserTrustDevice(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIUserTrustDeviceDelRsp *info);
    virtual void OnRtnAddUserTrustDevice(const ITapTrade::TapAPIUserTrustDeviceAddRsp *info);
    virtual void OnRtnDelUserTrustDevice(const ITapTrade::TapAPIUserTrustDeviceDelRsp *info);
    virtual void OnRspQryIPOInfo(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIIPOInfoQryRsp *info);
    virtual void OnRspQryIPOStockQty(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAvailableApplyQryRsp *info);
    virtual void OnRspQryAccountIPO(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountIPOQryRsp *info);
    virtual void OnRspAddAccountIPO(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIAccountIPOAddRsp *info);
    virtual void OnRspCancelAccountIPO(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIAccountIPOCancelRsp *info);
    virtual void OnRtnAddAccountIPO(const ITapTrade::TapAPIAccountIPOAddNotice *info);
    virtual void OnRtnCancelAccountIPO(const ITapTrade::TapAPIAccountIPOCancelNotice *info);
    virtual void OnRspSelfPasswordInfoOperate(ITapTrade::TAPIINT32 errorCode);
    virtual void OnRspVerificateIdentityInfo(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode);
    virtual void OnRspSetVertificateCode(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode);
    virtual void OnRspResetPassword(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode);
    virtual void OnRspQryExchangeStateInfo(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIExchangeStateInfoQryRsp* info);
    virtual void OnRtnExchangeStateInfo(const ITapTrade::TapAPIExchangeStateInfoAddNotice* info);

    // 工作线程
    void processTask();

void processConnect(Task *task);

void processRspLogin(Task *task);

void processRtnContactInfo(Task *task);

void processRspRequestVertificateCode(Task *task);

void processExpriationDate(Task *task);

void processAPIReady(Task *task);

void processDisconnect(Task *task);

void processRspChangePassword(Task *task);

void processRspAuthPassword(Task *task);

void processRspQryTradingDate(Task *task);

void processRspSetReservedInfo(Task *task);

void processRspQryAccount(Task *task);

void processRspQryFund(Task *task);

void processRtnFund(Task *task);

void processRspQryExchange(Task *task);

void processRspQryCommodity(Task *task);

void processRspQryContract(Task *task);

void processRtnContract(Task *task);

void processRspOrderAction(Task *task);

void processRtnOrder(Task *task);

void processRspQryOrder(Task *task);

void processRspQryOrderProcess(Task *task);

void processRspQryFill(Task *task);

void processRtnFill(Task *task);

void processRspQryPosition(Task *task);

void processRtnPosition(Task *task);

void processRspQryPositionSummary(Task *task);

void processRtnPositionSummary(Task *task);

void processRtnPositionProfit(Task *task);

void processRspQryCurrency(Task *task);

void processRspQryTradeMessage(Task *task);

void processRtnTradeMessage(Task *task);

void processRspQryHisOrder(Task *task);

void processRspQryHisOrderProcess(Task *task);

void processRspQryHisMatch(Task *task);

void processRspQryHisPosition(Task *task);

void processRspQryHisDelivery(Task *task);

void processRspQryHisFund(Task *task);

void processRspQryAccountCashAdjust(Task *task);

void processRspQryBill(Task *task);

void processRspQryAccountFeeRent(Task *task);

void processRspQryAccountMarginRent(Task *task);

void processRspHKMarketOrderInsert(Task *task);

void processRspHKMarketOrderDelete(Task *task);

void processHKMarketQuoteNotice(Task *task);

void processRspOrderLocalRemove(Task *task);

void processRspOrderLocalInput(Task *task);

void processRspOrderLocalModify(Task *task);

void processRspOrderLocalTransfer(Task *task);

void processRspFillLocalInput(Task *task);

void processRspFillLocalRemove(Task *task);

void processRspQrySpotLock(Task *task);

void processRtnSpotLock(Task *task);

void processRspSubmitUserLoginInfo(Task *task);

void processRspSpecialOrderAction(Task *task);

void processRtnSpecialOrder(Task *task);

void processRspQrySpecialOrder(Task *task);

void processRspQryCombinePosition(Task *task);

void processRtnCombinePosition(Task *task);

void processRspQryUserTrustDevice(Task *task);

void processRspAddUserTrustDevice(Task *task);

void processRspDelUserTrustDevice(Task *task);

void processRtnAddUserTrustDevice(Task *task);

void processRtnDelUserTrustDevice(Task *task);

void processRspQryIPOInfo(Task *task);

void processRspQryIPOStockQty(Task *task);

void processRspQryAccountIPO(Task *task);

void processRspAddAccountIPO(Task *task);

void processRspCancelAccountIPO(Task *task);

void processRtnAddAccountIPO(Task *task);

void processRtnCancelAccountIPO(Task *task);

void processRspSelfPasswordInfoOperate(Task *task);

void processRspVerificateIdentityInfo(Task *task);

void processRspSetVertificateCode(Task *task);

void processRspResetPassword(Task *task);

void processRspQryExchangeStateInfo(Task *task);

void processRtnExchangeStateInfo(Task *task);

    // Python 可重写的回调接口
virtual void onConnect(const string &HostAddress) {};

virtual void onRspLogin(int errorCode, const dict &loginRspInfo) {};

virtual void onRtnContactInfo(int errorCode, char isLast, const string &ContactInfo) {};

virtual void onRspRequestVertificateCode(unsigned int sessionID, int errorCode, const dict &rsp) {};

virtual void onExpriationDate(const string &date, int days) {};

virtual void onAPIReady(int errorCode) {};

virtual void onDisconnect(int reasonCode) {};

virtual void onRspChangePassword(unsigned int sessionID, int errorCode) {};

virtual void onRspAuthPassword(unsigned int sessionID, int errorCode) {};

virtual void onRspQryTradingDate(unsigned int sessionID, int errorCode, const dict &info) {};

virtual void onRspSetReservedInfo(unsigned int sessionID, int errorCode, const string &info) {};

virtual void onRspQryAccount(unsigned int sessionID, unsigned int errorCode, char isLast, const dict &info) {};

virtual void onRspQryFund(unsigned int sessionID, int errorCode, char isLast, const dict &info) {};

virtual void onRtnFund(const dict &info) {};

virtual void onRspQryExchange(unsigned int sessionID, int errorCode, char isLast, const dict &info) {};

virtual void onRspQryCommodity(unsigned int sessionID, int errorCode, char isLast, const dict &info) {};

virtual void onRspQryContract(unsigned int sessionID, int errorCode, char isLast, const dict &info) {};

virtual void onRtnContract(const dict &info) {};

virtual void onRspOrderAction(unsigned int sessionID, int errorCode, const dict &info) {};

virtual void onRtnOrder(const dict &info) {};

virtual void onRspQryOrder(unsigned int sessionID, int errorCode, char isLast, const dict &info) {};

virtual void onRspQryOrderProcess(unsigned int sessionID, int errorCode, char isLast, const dict &info) {};

virtual void onRspQryFill(unsigned int sessionID, int errorCode, char isLast, const dict &info) {};

virtual void onRtnFill(const dict &info) {};

virtual void onRspQryPosition(unsigned int sessionID, int errorCode, char isLast, const dict &info) {};

virtual void onRtnPosition(const dict &info) {};

virtual void onRspQryPositionSummary(unsigned int sessionID, int errorCode, char isLast, const dict &info) {};

virtual void onRtnPositionSummary(const dict &info) {};

virtual void onRtnPositionProfit(const dict &info) {};

virtual void onRspQryCurrency(unsigned int sessionID, int errorCode, char isLast, const dict &info) {};

virtual void onRspQryTradeMessage(unsigned int sessionID, int errorCode, char isLast, const dict &info) {};

virtual void onRtnTradeMessage(const dict &info) {};

virtual void onRspQryHisOrder(unsigned int sessionID, int errorCode, char isLast, const dict &info) {};

virtual void onRspQryHisOrderProcess(unsigned int sessionID, int errorCode, char isLast, const dict &info) {};

virtual void onRspQryHisMatch(unsigned int sessionID, int errorCode, char isLast, const dict &info) {};

virtual void onRspQryHisPosition(unsigned int sessionID, int errorCode, char isLast, const dict &info) {};

virtual void onRspQryHisDelivery(unsigned int sessionID, int errorCode, char isLast, const dict &info) {};

virtual void onRspQryHisFund(unsigned int sessionID, int errorCode, char isLast, const dict &info) {};

virtual void onRspQryAccountCashAdjust(unsigned int sessionID, int errorCode, char isLast, const dict &info) {};

virtual void onRspQryBill(unsigned int sessionID, int errorCode, char isLast, const dict &info) {};

virtual void onRspQryAccountFeeRent(unsigned int sessionID, int errorCode, char isLast, const dict &info) {};

virtual void onRspQryAccountMarginRent(unsigned int sessionID, int errorCode, char isLast, const dict &info) {};

virtual void onRspHKMarketOrderInsert(unsigned int sessionID, int errorCode, const dict &info) {};

virtual void onRspHKMarketOrderDelete(unsigned int sessionID, int errorCode, const dict &info) {};

virtual void onHKMarketQuoteNotice(const dict &info) {};

virtual void onRspOrderLocalRemove(unsigned int sessionID, int errorCode, const dict &info) {};

virtual void onRspOrderLocalInput(unsigned int sessionID, int errorCode, const dict &info) {};

virtual void onRspOrderLocalModify(unsigned int sessionID, int errorCode, const dict &info) {};

virtual void onRspOrderLocalTransfer(unsigned int sessionID, int errorCode, const dict &info) {};

virtual void onRspFillLocalInput(unsigned int sessionID, int errorCode, const dict &info) {};

virtual void onRspFillLocalRemove(unsigned int sessionID, int errorCode, const dict &info) {};

virtual void onRspQrySpotLock(unsigned int sessionID, int errorCode, char isLast, const dict &info) {};

virtual void onRtnSpotLock(const dict &info) {};

virtual void onRspSubmitUserLoginInfo(unsigned int sessionID, int errorCode, char isLast, const dict &info) {};

virtual void onRspSpecialOrderAction(unsigned int sessionID, int errorCode, const dict &info) {};

virtual void onRtnSpecialOrder(const dict &info) {};

virtual void onRspQrySpecialOrder(unsigned int sessionID, int errorCode, char isLast, const dict &info) {};

virtual void onRspQryCombinePosition(unsigned int sessionID, int errorCode, char isLast, const dict &info) {};

virtual void onRtnCombinePosition(const dict &info) {};

virtual void onRspQryUserTrustDevice(unsigned int sessionID, int errorCode, char isLast, const dict &info) {};

virtual void onRspAddUserTrustDevice(unsigned int sessionID, int errorCode, const dict &info) {};

virtual void onRspDelUserTrustDevice(unsigned int sessionID, int errorCode, const dict &info) {};

virtual void onRtnAddUserTrustDevice(const dict &info) {};

virtual void onRtnDelUserTrustDevice(const dict &info) {};

virtual void onRspQryIPOInfo(unsigned int sessionID, int errorCode, char isLast, const dict &info) {};

virtual void onRspQryIPOStockQty(unsigned int sessionID, int errorCode, char isLast, const dict &info) {};

virtual void onRspQryAccountIPO(unsigned int sessionID, int errorCode, char isLast, const dict &info) {};

virtual void onRspAddAccountIPO(unsigned int sessionID, int errorCode, const dict &info) {};

virtual void onRspCancelAccountIPO(unsigned int sessionID, int errorCode, const dict &info) {};

virtual void onRtnAddAccountIPO(const dict &info) {};

virtual void onRtnCancelAccountIPO(const dict &info) {};

virtual void onRspSelfPasswordInfoOperate(int errorCode) {};

virtual void onRspVerificateIdentityInfo(unsigned int sessionID, int errorCode) {};

virtual void onRspSetVertificateCode(unsigned int sessionID, int errorCode) {};

virtual void onRspResetPassword(unsigned int sessionID, int errorCode) {};

virtual void onRspQryExchangeStateInfo(unsigned int sessionID, int errorCode, char isLast, const dict &info) {};

virtual void onRtnExchangeStateInfo(const dict &info) {};

    // 主动函数
int setAPINotify();

int setHostAddress(const string &IP, unsigned short port, bool bSSL);

int login(const dict &loginAuth);

int requestVertificateCode(const string &ContactInfo);

int setVertificateCode(const dict &req);

int disconnect();

int changePassword(const dict &req);

int authPassword(const dict &req);

int haveCertainRight(int rightID);

int qryTradingDate();

int setReservedInfo(const string &info);

int qryAccount(const dict &qryReq);

int qryFund(const dict &qryReq);

int qryExchange();

int qryCommodity();

int qryContract(const dict &qryReq);

int insertOrder(const string &ClientOrderNo, const dict &order);

int cancelOrder(const dict &order);

int amendOrder(const dict &order);

int activateOrder(const dict &order);

int qryOrder(const dict &qryReq);

int qryOrderProcess(const dict &qryReq);

int qryFill(const dict &qryReq);

int qryPosition(const dict &qryReq);

int qryPositionSummary(const dict &qryReq);

int qryCurrency();

int qryAccountCashAdjust(const dict &qryReq);

int qryTradeMessage(const dict &qryReq);

int qryBill(const dict &qryReq);

int qryHisOrder(const dict &qryReq);

int qryHisOrderProcess(const dict &qryReq);

int qryHisMatch(const dict &qryReq);

int qryHisPosition(const dict &qryReq);

int qryHisDelivery(const dict &qryReq);

int qryHisFund(const dict &qryReq);

int qryAccountFeeRent(const dict &qryReq);

int qryAccountMarginRent(const dict &qryReq);

int insertHKMarketOrder(const string &ClientBuyOrderNo, const string &ClientSellOrderNo, const dict &order);

int cancelHKMarketOrder(const dict &order);

int orderLocalRemove(const dict &order);

int orderLocalInput(const dict &order);

int orderLocalModify(const dict &order);

int orderLocalTransfer(const dict &order);

int fillLocalInput(const dict &fill);

int fillLocalRemove(const dict &fill);

int qrySpotLock(const dict &qryReq);

int submitUserLoginInfo(const dict &qryReq);

int insertSpecialOrder(const string &clientorderno, const dict &order);

int qrySpecialOrder(const dict &qryReq);

int qryCombinePosition(const dict &qryReq);

int qryUserTrustDevice(const dict &qryReq);

int addUserTrustDevice(const dict &qryReq);

int delUserTrustDevice(const dict &qryReq);

int selfPasswordInfoOperate(const dict &qryReq);

int verificateIdentityInfo(const dict &qryReq);

int resetPassword(const dict &qryReq);

int qryExchangeStateInfo(const dict &qryReq);

int createITapTradeAPI(const dict &req);

string getITapTradeAPIVersion();

string getITapErrorDescribe(int errorCode);

    void init();
};