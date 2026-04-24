对比 C++ API 头文件与 Python `.pyi` 封装，**所有核心的接口方法和回调均已封装，未缺失**。  
但两个全局释放函数在封装中未暴露，通常因为 Python 自动管理对象生命周期而不需要手动调用。若将它们视为“丢失”，则具体情况如下：

---

### 行情模块（`TapQuoteAPI.h` vs `tapmd.pyi`）
- **`ITapQuoteAPI` 全部 8 个方法**：`SetAPINotify`、`SetHostAddress`、`Login`、`Disconnect`、`QryCommodity`、`QryContract`、`SubscribeQuote`、`UnSubscribeQuote` → `MdApi` 中均有对应。
- **`ITapQuoteAPINotify` 全部 8 个回调**：`OnRspLogin`、`OnAPIReady`、`OnDisconnect`、`OnRspQryCommodity`、`OnRspQryContract`、`OnRspSubscribeQuote`、`OnRspUnSubscribeQuote`、`OnRtnQuote` → `MdApi` 中均有对应。
- **全局导出函数 5 个**：`CreateTapQuoteAPI`、`GetTapQuoteAPIVersion`、`SetTapQuoteAPIDataPath`、`SetTapQuoteAPILogLevel` 已封装；**❌ 缺少 `FreeTapQuoteAPI`**。

➡️ **行情丢失 1 个函数**：`FreeTapQuoteAPI`。

---

### 交易模块（`iTapTradeAPI.h` vs `taptd.pyi`）
- **`ITapTradeAPI` 全部 50+ 方法**：`Login`、`InsertOrder`、`QryFund`、`QryPosition` 等均已在 `TdApi` 中实现（包括 `ActivateOrder`、所有 `QryHis*`、`OrderLocal*`、`FillLocal*`、`QryExchangeStateInfo` 等）。  
  ✅ 无缺失。
- **`ITapTradeAPINotify` 全部 60+ 回调**：`OnRspLogin`、`OnRtnOrder`、`OnRtnFill`、`OnRtnPosition` 等均在 `TdApi` 中定义。  
  ✅ 无缺失。
- **全局导出函数 4 个**：`CreateITapTradeAPI`、`GetITapTradeAPIVersion`、`GetITapErrorDescribe` 已封装；**❌ 缺少 `FreeITapTradeAPI`**。

➡️ **交易丢失 1 个函数**：`FreeITapTradeAPI`。

---

### 结论
- **功能接口 & 回调**：**零丢失**，封装非常完整。
- **全局辅助函数**：仅丢失 **`FreeTapQuoteAPI`** 和 **`FreeITapTradeAPI`** 两个手动释放函数（这在 Python 封装中很常见，因为 `__del__` 或 GC 会自动处理资源释放）。
- **总计丢失函数数**：**2 个**（且均为非业务必要的资源释放函数）。