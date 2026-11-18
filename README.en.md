# Switching Power Experimental Platform

[简体中文](README.md) · **English**

A platform for learning and experimenting with switching power converters. It includes EasyEDA hardware designs, STM32F334 firmware, TI C2000 projects and examples, a Qt serial application, and MATLAB/Simulink models.

The original platform contains bidirectional DC-DC and three-phase converter circuits. The hardware collection also includes C2000, half-bridge, isolated debug, sensing, and auxiliary supply projects. The simulation library covers rectifiers, inverters, UPS, grid control, motor drives, and more.

## Repository guide

| Directory / File | Contents |
| --- | --- |
| [01_Hardware](01_Hardware/README.md) | EasyEDA Pro projects, schematic PDFs, and board photos |
| [02_Software](02_Software/README.md) | STM32 projects for Keil and TI C2000 projects and examples for CCS |
| [03_QT上位机](03_QT上位机/) | Qt serial application and communication protocol |
| [04_仿真](04_仿真/README.md) | Simulink models by topology and application, with dependency notes |
| [05_计算书](05_计算书/) | Circuit design and calculation references |
| [06_常用工具](06_常用工具/) | Power supply design tools |
| [07_常用资料](07_常用资料/README.md) | References on loop compensation, inverters, magnetics, and transfer functions |

## Getting started

```bash
git clone https://github.com/Epiphany-Leave/Switching-power-experimental-platform.git
cd Switching-power-experimental-platform
```

1. View the schematic PDFs online, or import the relevant `.epro` or `.epro2` into EasyEDA Pro to inspect the schematic and PCB. [Hardware projects](01_Hardware/README.md)
2. Choose Keil or TI CCS for your controller. Open the project and check its toolchain, device, and dependencies. [Firmware and examples](02_Software/README.md)
3. Open the desktop project in Qt Creator with Qt Widgets and SerialPort. Use the protocol to set up the serial connection. [Qt project](03_QT上位机/QT/Graduated/Graduated.pro) · [Communication protocol](03_QT上位机/通讯协议.xlsx)
4. Use the MATLAB release and toolboxes required by the model. Saved releases span R2016a–R2024b. Some models also need Specialized Power Systems or external components. [Simulation guide](04_仿真/README.md)

## Acknowledgments

Thanks to [Lao Zhang](https://space.bilibili.com/52867486) and everyone in the group for generously sharing their work as open source.

## Contributions and license

Issues and pull requests with board notes, test results, dependency information, and corrections are welcome. For simulation changes, include the MATLAB release and required toolboxes.

See the repository's [GNU GPL v3 license](LICENSE). Third-party code and references retain their original copyright and license notices.
