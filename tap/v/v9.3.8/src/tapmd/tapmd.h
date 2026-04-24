#include "../../../tap.h"
#include "pybind11/pybind11.h"
#include "TapQuoteAPI.h"

using namespace pybind11;


// 常量定义（若有）
#define ONRSPLOGIN 0
#define ONAPIREADY 1
#define ONDISCONNECT 2
#define ONRSPQRYCOMMODITY 3
#define ONRSPQRYCONTRACT 4
#define ONRSPSUBSCRIBEQUOTE 5
#define ONRSPUNSUBSCRIBEQUOTE 6
#define ONRTNQUOTE 7

///-------------------------------------------------------------------------------------
///C++ SPI的回调函数的继承实现
///-------------------------------------------------------------------------------------

class MdApi : public ITapQuoteAPINotify
{
private:
    ITapQuoteAPI* api;
    thread task_thread;
    TaskQueue task_queue;
    bool active = false;

public:
    MdApi() {}
    virtual ~MdApi()
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
    virtual void OnRspLogin(TAPIINT32 errorCode, const TapAPIQuotLoginRspInfo *info);
    virtual void OnAPIReady();
    virtual void OnDisconnect(TAPIINT32 reasonCode);
    virtual void OnRspQryCommodity(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteCommodityInfo *info);
    virtual void OnRspQryContract(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteContractInfo *info);
    virtual void OnRspSubscribeQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteWhole *info);
    virtual void OnRspUnSubscribeQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIContract *info);
    virtual void OnRtnQuote(const TapAPIQuoteWhole *info);

    // 工作线程
    void processTask();

void processRspLogin(Task *task);

void processAPIReady(Task *task);

void processDisconnect(Task *task);

void processRspQryCommodity(Task *task);

void processRspQryContract(Task *task);

void processRspSubscribeQuote(Task *task);

void processRspUnSubscribeQuote(Task *task);

void processRtnQuote(Task *task);

    // Python 可重写的回调接口
virtual void onRspLogin(int errorCode, const dict &info) {};

virtual void onAPIReady() {};

virtual void onDisconnect(int reasonCode) {};

virtual void onRspQryCommodity(unsigned int sessionID, int errorCode, char isLast, const dict &info) {};

virtual void onRspQryContract(unsigned int sessionID, int errorCode, char isLast, const dict &info) {};

virtual void onRspSubscribeQuote(unsigned int sessionID, int errorCode, char isLast, const dict &info) {};

virtual void onRspUnSubscribeQuote(unsigned int sessionID, int errorCode, char isLast, const dict &info) {};

virtual void onRtnQuote(const dict &info) {};

    // 主动函数
int setAPINotify();

int setHostAddress(const string &IP, unsigned short port);

int login(const dict &loginAuth);

int disconnect();

int qryCommodity();

int qryContract(const dict &qryReq);

int subscribeQuote(const dict &contract);

int unSubscribeQuote(const dict &contract);

int createTapQuoteAPI(const dict &req);

string getTapQuoteAPIVersion();

int setTapQuoteAPIDataPath(const string &path);

int setTapQuoteAPILogLevel(int level);

    void init();
};