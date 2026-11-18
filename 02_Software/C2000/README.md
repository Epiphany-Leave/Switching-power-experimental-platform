# C2000 工程与例程 / C2000 Projects and Examples

[固件导航 / Firmware guide](../README.md)

| 目录 / Directory | 内容 / Contents |
| --- | --- |
| [F280049_PRJ](F280049_PRJ/) | F280049C 工程，含 ADC、ePWM、SFO 和 RAM/FLASH 配置 / F280049C project with ADC, ePWM, SFO and RAM/FLASH configurations |
| [cla_lp_f28004x](cla_lp_f28004x/) | F280049C CLA 低通 FIR 实验 / F280049C CLA low-pass FIR lab |
| [XC-F280049C_Peripheral_Examples](XC-F280049C_Peripheral_Examples/) | LED、按键、SCI、RS485、CAN、I2C、SPI 和 FSI 例程 / LED, key, SCI, RS485, CAN, I2C, SPI and FSI examples |
| [C2000外设初始化例程](C2000外设初始化例程/) | 外设初始化代码片段 / Peripheral initialization snippets |
| [MINMAX法DPWMA](MINMAX法DPWMA/) | Min/Max DPWMA 源码与使用笔记 / Min/max DPWMA source and notes |

在 CCS 中导入工程目录，并核对目标芯片和 SDK。`F280049_PRJ` 配置编译器 22.6.2.LTS，SFO V8 库位于 `LIB/`（[许可说明](F280049_PRJ/LIB/SFO_V8.h)）。`cla_lp_f28004x` 使用编译器 22.6.1.LTS、C2000Ware 5.03.00.00 和 SysConfig 1.21.0；外设例程使用 C2000Ware 5.02.00.00，部分需要 SysConfig 1.19.0。代码片段需要目标工程及相应应用头文件。

Import project folders in CCS and check the target and SDK. `F280049_PRJ` specifies compiler 22.6.2.LTS and includes SFO V8 in `LIB/` ([license](F280049_PRJ/LIB/SFO_V8.h)). `cla_lp_f28004x` uses compiler 22.6.1.LTS, C2000Ware 5.03.00.00 and SysConfig 1.21.0. The peripheral examples use C2000Ware 5.02.00.00; some require SysConfig 1.19.0. Snippets require a target project and their application headers.
