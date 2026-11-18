# TI C2000 工程与例程 / TI C2000 Projects and Examples

[固件导航 / Firmware guide](../README.md)

| 目录 / Directory | 内容 / Contents |
| --- | --- |
| [F280049_PRJ](F280049_PRJ/) | TMS320F280049C CCS 工程，含 RAM 和 FLASH 配置。主程序演示定时器、ADC、ePWM 和 SFO 校准，另有 HRPWM、SCI、Trip Zone 例程。 / CCS project with RAM and FLASH profiles, timer, ADC, ePWM and SFO calibration, plus peripheral routines. |
| [cla_lp_f28004x](cla_lp_f28004x/) | LAUNCHXL-F280049C 的 CLA 低通 FIR 实验。由 PWM 触发 ADC 采样，再由 CLA 执行滤波。 / CLA low-pass FIR lab with PWM-triggered ADC sampling. |
| [C2000外设初始化例程](C2000外设初始化例程/) | CAN、SCI/UART、CMPSS、DAC、HRPWM、定时器和 Trip Zone 代码片段。 / Peripheral initialization snippets. |
| [MINMAX法DPWMA](MINMAX法DPWMA/) | Min/Max 法 DPWMA 调制源码、使用笔记与 C2837xD 发波参考。 / Min/max DPWMA source, usage notes, and a C2837xD PWM reference. |

## 导入与依赖 / Import and dependencies

在 CCS 中使用 **Import CCS Projects** 选择上述两个工程目录。项目内保留了工程描述文件、链接脚本和调试器目标配置。构建前核对目标芯片、编译器版本和本机 SDK。

Use **Import CCS Projects** for the two CCS project folders. The project descriptors, linker scripts, and debugger targets are included. Match the target and tools before building.

- `F280049_PRJ` 原工程使用 TI C2000 编译器 **22.6.2.LTS**，由 `LIB/` 提供 HRPWM 所需的 SFO V8 库。 / The original project uses compiler **22.6.2.LTS** and the SFO V8 library in `LIB/`.
- `cla_lp_f28004x` 原工程使用编译器 **22.6.1.LTS**、**C2000Ware 5.03.00.00** 和 **SysConfig 1.21.0**。工程链接 SDK 中的 `driverlib/f28004x/driverlib/ccs/Debug/driverlib.lib`。在 CCS 注册 C2000Ware 后检查链接是否解析。 / Register the matching C2000Ware product in CCS and check that the linked SDK library resolves. [C2000Ware](https://www.ti.com/tool/C2000WARE) · [LaunchPad](https://www.ti.com/tool/LAUNCHXL-F280049C)
- 外设初始化与 DPWMA 是供移植的片段。CAN、UART 和 HRPWM 示例还引用原工程头文件，如 `H_CAN_Deal.h`、`H_UART.h`、`H_CRC.h`、`H_Uart_Drv.h` 和 `hrpwm.h`，需结合目标工程补齐。 / Integrate the snippets into a target project and provide the missing application headers.

## 构建验证 / Build verification

两个工程均已在 CCS 12.8.1 中导入。`F280049_PRJ` 使用本机编译器 22.6.1.LTS 构建 RAM 和 FLASH 配置，均生成 `.out`。`cla_lp_f28004x` 已导入，构建在发现本机缺少 C2000Ware 5.03.00.00 后停止。

Both projects imported into CCS 12.8.1. The installed compiler, 22.6.1.LTS, produced a `.out` for both RAM and FLASH in `F280049_PRJ`. The CLA build stopped at the C2000Ware 5.03.00.00 dependency check.

## 第三方许可 / Third-party licenses

TI 示例、设备支持代码和 DriverLib 保留各文件的版权与许可。随工程分发的 SFO V8 二进制库受 TI 的许可约束，许可与使用限制随接口头文件提供。 [SFO V8 license notice](F280049_PRJ/LIB/SFO_V8.h)

TI examples, device support code, and DriverLib retain their original notices. The SFO V8 binary is governed by TI's terms supplied in its interface header. [SFO V8 license notice](F280049_PRJ/LIB/SFO_V8.h)
