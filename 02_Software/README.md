# 固件与例程 / Firmware and Examples

[中文首页](../README.md) · [English overview](../README.en.md)

| 平台 / Platform | 工程入口 / Entry points | 开发工具 / Toolchain |
| --- | --- | --- |
| STM32F334 | [BUCK](STM32/BUCK/project/Project.uvprojx) · [Inv](STM32/Inv/project/Project.uvprojx) · [TPHINV](STM32/TPHINV/project/Project.uvprojx) | Keil µVision、STM32F3 器件包 / STM32F3 device pack |
| TI C2000 | [C2000 工程与代码片段](C2000/README.md) | TI Code Composer Studio、C2000 编译器，CLA 工程另外需要 C2000Ware 与 SysConfig / TI CCS, C2000 compiler, plus C2000Ware and SysConfig for the CLA project |

原 STM32 目录迁至 `STM32/`。使用 Keil 打开相应的 `project/Project.uvprojx`，再核对目标芯片、调试器和板卡版本。BUCK 工程选择 STM32F334R8Tx，Inv 和 TPHINV 选择 STM32F334R6。

The STM32 projects now live under `STM32/`. Open the corresponding `project/Project.uvprojx` in Keil and check the target, debugger, and board revision. BUCK targets STM32F334R8Tx. Inv and TPHINV target STM32F334R6.
