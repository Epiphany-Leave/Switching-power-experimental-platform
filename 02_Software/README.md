# 固件与例程 / Firmware and Examples

[中文首页](../README.md) · [English overview](../README.en.md)

| 平台 / Platform | 工程入口 / Entry points | 开发工具 / Toolchain |
| --- | --- | --- |
| STM32F334 | [BUCK](STM32/BUCK/project/Project.uvprojx) · [Inv](STM32/Inv/project/Project.uvprojx) · [TPHINV](STM32/TPHINV/project/Project.uvprojx) | Keil µVision、STM32F3 器件包 / STM32F3 device pack |
| TI C2000 | [C2000 工程与代码片段](C2000/README.md) · [XC-F280049C 通用外设例程](C2000/XC-F280049C_Peripheral_Examples/) | TI CCS、C2000 编译器。按工程配置安装 C2000Ware 与 SysConfig。 / TI CCS and C2000 compiler. Install C2000Ware and SysConfig as required by the project. |

原 STM32 目录迁至 `STM32/`。使用 Keil 打开相应的 `project/Project.uvprojx`，再核对目标芯片、调试器和板卡版本。BUCK 工程选择 STM32F334R8Tx，Inv 和 TPHINV 选择 STM32F334R6。

The STM32 projects now live under `STM32/`. Open the corresponding `project/Project.uvprojx` in Keil and check the target, debugger, and board revision. BUCK targets STM32F334R8Tx. Inv and TPHINV target STM32F334R6.
