# 开关电源实验平台

**简体中文** · [English](README.en.md)

一个用于学习和实验的开关电源平台，包含嘉立创 EDA 硬件工程、STM32F334 固件、TI C2000 工程与例程、Qt 串口上位机，以及 MATLAB/Simulink 仿真。

原平台包含双向 DC-DC 和三相变换电路。新增硬件涵盖 C2000、半桥、隔离调试器、采样与辅助电源。仿真库还覆盖整流、逆变、UPS、电网控制和电机驱动等主题。

## 目录导航

| 目录 / 文件 | 内容 |
| --- | --- |
| [01_Hardware](01_Hardware/README.md) | 嘉立创 EDA 专业版工程、原理图与板卡说明 |
| [02_Software](02_Software/README.md) | 分为 STM32 Keil 工程和 TI C2000 CCS 工程与例程 |
| [03_QT上位机](03_QT上位机/) | Qt 串口上位机和通信协议 |
| [04_仿真](04_仿真/README.md) | 按拓扑和应用分类的 Simulink 模型、依赖与历史版本 |
| [05_计算书](05_计算书/) | 电路设计与参数计算资料 |
| [06_常用工具](06_常用工具/) | 电源设计辅助工具 |
| [07_常用资料](07_常用资料/README.md) | 环路补偿、逆变、磁性元件、传递函数等参考资料 |
| 根目录 `BOM*.xlsx` | 原平台板卡物料清单 |

## 快速开始

```bash
git clone https://github.com/Epiphany-Leave/Switching-power-experimental-platform.git
cd Switching-power-experimental-platform
```

1. 在嘉立创 EDA 专业版导入对应的 `.epro` 或 `.epro2`，结合原理图与 BOM 查看设计。 [硬件工程](01_Hardware/README.md)
2. 根据控制器选择 Keil 或 TI CCS，打开对应工程并核对开发工具、器件与依赖。 [固件与例程](02_Software/README.md)
3. 用 Qt Creator 打开上位机工程，配置 Qt Widgets 和 SerialPort，再对照协议连接串口。 [Qt 工程](03_QT上位机/QT/Graduated/Graduated.pro) · [通信协议](03_QT上位机/通讯协议.xlsx)
4. 按对应版本和工具箱打开仿真。模型保存版本跨 R2016a–R2024b，部分还需要 Specialized Power Systems 或外部组件。 [仿真导航](04_仿真/README.md)

## 感谢

感谢[老张](https://space.bilibili.com/52867486)以及群友们的无私开源。

## 贡献与许可

欢迎通过 Issue 或 Pull Request 补充板卡说明、实测记录、工程依赖和修正。涉及模型时，请注明 MATLAB 版本和所需工具箱。

仓库许可见 [GNU GPL v3](LICENSE)。第三方代码与资料保留各自的版权及许可说明。
