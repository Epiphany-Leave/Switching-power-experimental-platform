# 开关电源实验平台

[English](README.en.md)

面向开关电源学习与实验的资料仓库，包含硬件设计、STM32F334 固件、Qt 串口上位机，以及 MATLAB/Simulink 仿真与计算资料。

硬件围绕 STM32F334 控制板、双向 DC-DC 和三相变换电路展开。仿真库包含更多电力电子与控制主题，是扩展学习参考，不表示每个模型都有对应硬件或固件。

## 目录导航

| 目录 / 文件 | 内容 |
| --- | --- |
| [01_Hardware](01_Hardware/) | 嘉立创专业版 `.epro` 硬件工程与原理图压缩包 |
| [02_Sofaware](02_Sofaware/) | BUCK、Inv、TPHINV 等 Keil 工程，主控 STM32F334 |
| [03_QT上位机](03_QT上位机/) | Qt 串口上位机源码与 `通讯协议.xlsx` |
| [04_仿真](04_仿真/README.md) | 按拓扑和应用分类的 Simulink 模型、运行依赖与历史版本导航 |
| [05_计算书](05_计算书/) | 电路设计与参数计算资料 |
| [06_常用工具](06_常用工具/) | 辅助工具 |
| [07_常用资料](07_常用资料/) | 学习参考资料 |
| 根目录 `BOM*.xlsx` | 各板卡物料清单 |

`02_Sofaware` 保留原目录拼写；目录名和工程名用于定位文件，不代表相应功能已完整实现或验证。

## 快速开始

```bash
git clone --branch master https://github.com/Epiphany-Leave/Switching-power-experimental-platform.git
cd Switching-power-experimental-platform
```

按需要选择入口：

1. **硬件**：使用嘉立创专业版打开 [硬件目录](01_Hardware/) 中的 `.epro`，结合原理图与 BOM 查看板卡设计。
2. **固件**：使用 Keil µVision 打开以下工程，按本机环境配置编译器、STM32 器件包与下载器：
   - [BUCK](02_Sofaware/BUCK/project/Project.uvprojx)
   - [Inv](02_Sofaware/Inv/project/Project.uvprojx)
   - [TPHINV](02_Sofaware/TPHINV/project/Project.uvprojx)
3. **上位机**：使用 Qt Creator 打开 [Graduated.pro](03_QT上位机/QT/Graduated/Graduated.pro)，配置含 Widgets、SerialPort 的 Qt 构建环境，并参照 [通讯协议](03_QT上位机/通讯协议.xlsx) 核对串口数据。
4. **仿真**：先阅读 [仿真导航与依赖说明](04_仿真/README.md)，再选择模型并配置 MATLAB/Simulink 环境。

## 仿真范围与环境

仿真按 DC-DC、AC-DC、DC-AC、AC-DC-AC、UPS、电网控制、电机驱动、电能质量与负载、控制与信号处理、建模与计算、并网交直流接口分类，历史版本单独保留。

- 模型原始保存版本跨 **R2016a–R2024b**；`dpwm`、`PMSM_FOC` 使用 R2024b 保存。请按具体模型选择兼容版本。
- 部分模型使用 Specialized Power Systems（`powerlib`）组件；部分还依赖 SDtoolbox 或 S-Function。具体要求见 [仿真说明](04_仿真/README.md)。
- 本仓库未提供全部工程的统一构建或运行验证；打开模型、编译固件与连接硬件前，应核对参数和依赖。

## 硬件使用提示

原设计的双向 DC-DC 与三相板通过辅助电源方向选择电阻区分方向：选装一侧时需去掉另一侧。三相板用于 AC-DC 时还涉及三相整流桥，实际装配请以原理图为准。

## 贡献与许可

欢迎通过 Issue 或 Pull Request 补充依赖、运行条件与修正；涉及模型时请注明 MATLAB 版本、所需工具箱及修改内容。

仓库现有许可见 [LICENSE](LICENSE)（GNU GPL v3）；各文件自带的版权与许可说明请一并保留。
