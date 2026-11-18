# STM32 工程 / STM32 Projects

[固件导航 / Firmware guide](../README.md)

| 工程 / Project | 目标器件 / Target | Keil 工程 / Keil project |
| --- | --- | --- |
| [降压变换器 / Buck converter](Buck_Converter/) | STM32F334R8Tx | [Buck_Converter.uvprojx](Buck_Converter/project/Buck_Converter.uvprojx) |
| [单相逆变器 / Single-phase inverter](Single_Phase_Inverter/) | STM32F334R6 | [Single_Phase_Inverter.uvprojx](Single_Phase_Inverter/project/Single_Phase_Inverter.uvprojx) |
| [三相逆变器 / Three-phase inverter](Three_Phase_Inverter/) | STM32F334R6 | [Three_Phase_Inverter.uvprojx](Three_Phase_Inverter/project/Three_Phase_Inverter.uvprojx) |
| 降压板诊断 / Buck board diagnostics | STM32F334R6 | [Buck_Board_Diagnostics.uvprojx](Buck_Converter/Board_Diagnostics/project/Buck_Board_Diagnostics.uvprojx) |
| 单相逆变器 PWM 模板 / Single-phase inverter PWM template | STM32F334R6 | [Single_Phase_PWM_Template.uvprojx](Single_Phase_Inverter/PWM_Control_Template/project/Single_Phase_PWM_Template.uvprojx) |
| 三相逆变器 PWM 模板 / Three-phase inverter PWM template | STM32F334R6 | [Three_Phase_PWM_Template.uvprojx](Three_Phase_Inverter/PWM_Control_Template/project/Three_Phase_PWM_Template.uvprojx) |

两份 PWM 模板需补齐生成的控制代码，三相工程下的模板还需要 `private_inv.h`。Both PWM templates require generated controller code. The template under the three-phase inverter also needs `private_inv.h`.

使用 Keil µVision 打开工程；工程配置使用 STM32F3 器件包 2.2.2。下载前核对目标芯片、调试器与板卡。

Open the projects in Keil µVision with the STM32F3 device pack 2.2.2. Check the target, debugger and board before programming.
