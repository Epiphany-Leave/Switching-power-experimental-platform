# Switching Power Experimental Platform

[简体中文](README.md)

A learning and experimental repository for switching power converters, with hardware designs, STM32F334 firmware, a Qt serial desktop application, and MATLAB/Simulink models and calculation references.

The hardware covers an STM32F334 controller board, bidirectional DC-DC conversion, and three-phase conversion circuits. The simulation library extends to other power electronics and control topics; a model does not necessarily have matching hardware or firmware in this repository.

## Repository guide

| Directory / file | Contents |
| --- | --- |
| [01_Hardware](01_Hardware/) | JLCEDA Professional `.epro` hardware project and schematic archive |
| [02_Sofaware](02_Sofaware/) | Keil projects including BUCK, Inv, and TPHINV for STM32F334 |
| [03_QT上位机](03_QT上位机/) | Qt serial application source and `通讯协议.xlsx` communication protocol |
| [04_仿真](04_仿真/README.md) | Simulink models organized by topology and application, dependencies, and historical versions |
| [05_计算书](05_计算书/) | Circuit design and parameter calculation references |
| [06_常用工具](06_常用工具/) | Supporting tools |
| [07_常用资料](07_常用资料/) | Learning references |
| Root `BOM*.xlsx` files | Board bills of materials |

The original spelling `02_Sofaware` is retained. Directory and project names locate files; they do not establish that every named function is complete or verified.

## Getting started

```bash
git clone --branch master https://github.com/Epiphany-Leave/Switching-power-experimental-platform.git
cd Switching-power-experimental-platform
```

Choose the relevant entry point:

1. **Hardware**: open the `.epro` file in [01_Hardware](01_Hardware/) with JLCEDA Professional, and review the schematics and BOM alongside it.
2. **Firmware**: open one of these projects in Keil µVision and configure the compiler, STM32 device pack, and programmer for your environment:
   - [BUCK](02_Sofaware/BUCK/project/Project.uvprojx)
   - [Inv](02_Sofaware/Inv/project/Project.uvprojx)
   - [TPHINV](02_Sofaware/TPHINV/project/Project.uvprojx)
3. **Desktop application**: open [Graduated.pro](03_QT上位机/QT/Graduated/Graduated.pro) in Qt Creator with Widgets and SerialPort support. Check serial data against the [communication protocol](03_QT上位机/通讯协议.xlsx).
4. **Simulation**: read the [model guide and dependencies](04_仿真/README.md), choose a model, and configure MATLAB/Simulink accordingly.

## Simulation coverage and environment

Categories cover DC-DC, AC-DC, DC-AC, AC-DC-AC, UPS, grid control, motor drives, power quality and loads, control and signal processing, modeling and calculations, and grid-connected AC/DC interfaces. Historical versions are kept separately.

- Original model save versions span **R2016a–R2024b**; `dpwm` and `PMSM_FOC` were saved with R2024b. Select a compatible release for the individual model.
- Some models use Specialized Power Systems (`powerlib`) components; some also require SDtoolbox or S-Functions. See the [simulation guide](04_仿真/README.md) for details.
- This repository does not provide a verified build or run procedure covering every project. Check parameters and dependencies before running models, building firmware, or connecting hardware.

## Hardware notes

In the original bidirectional DC-DC and three-phase designs, auxiliary supply direction is selected by fitting one direction-selection resistor and removing the other. AC-DC operation of the three-phase board also involves a three-phase rectifier bridge; follow the schematics for assembly details.

## Contributions and license

Issues and pull requests documenting dependencies, operating conditions, and corrections are welcome. For model changes, include the MATLAB release, required toolboxes, and a description of the change.

The existing repository license is [LICENSE](LICENSE) (GNU GPL v3). Retain copyright and license notices supplied with individual files.
