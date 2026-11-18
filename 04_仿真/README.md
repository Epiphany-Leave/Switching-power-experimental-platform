# 仿真导航 / Simulation Guide

[中文首页](../README.md) · [English overview](../README.en.md)

共 **71 个模型（70 SLX + 1 MDL）**，另含参数脚本、分析脚本和 PSIM 原理图。

**71 models (70 SLX + 1 MDL)**, plus parameter and analysis scripts and a PSIM schematic.

## 分类原则 / Classification

完整应用优先；通用功率级按实际电源、负载、有效连接及控制目标分类；纯算法单列。CHB/NPC/DPWM 等名称不能决定功率方向；内部高频交流不改变 LLC/DAB 整体 DC-DC 类别。两个静态方向不确定的并网接口单列，不强行判断整流或逆变。

Complete applications take priority. Generic converters are classified by their sources, loads, active connections and control objectives; standalone algorithms are separate. Topology names alone do not determine power direction. Internal high-frequency AC does not turn an isolated DC-DC stage into an inverter system. Two interfaces with unverified power direction have a separate category.

| 目录 / Folder | 当前模型 / Models | 内容 / Scope |
| --- | ---: | --- |
| [01_DC-DC](01_DC-DC) | 14 | Buck、交错 Boost、飞跨电容 Buck-Boost、LLC、谐振双有源桥与超级电容 / DC-DC power stages |
| [02_AC-DC](02_AC-DC) | 33 | PFC、PWM/CSR、Vienna/NPC、CHB、MMC及带隔离输出的整流 / Rectification and PFC |
| [03_DC-AC](03_DC-AC) | 9 | 单相、三相、多桥臂逆变与谐振驱动 / Inverter experiments |
| [04_AC-DC-AC](04_AC-DC-AC) | 1 | 完整交直交变换链 / Complete AC-DC-AC chain |
| [05_UPS](05_UPS) | 2 | 不间断电源系统 / UPS systems |
| [06_电网控制](06_%E7%94%B5%E7%BD%91%E6%8E%A7%E5%88%B6) | 4 | VSG 与交流下垂控制系统 / VSG and AC droop systems |
| [07_电机驱动](07_%E7%94%B5%E6%9C%BA%E9%A9%B1%E5%8A%A8) | 2 | PMSM 磁场定向控制与单相异步电机 / PMSM field-oriented control and single-phase induction motors |
| [08_电能质量与负载](08_%E7%94%B5%E8%83%BD%E8%B4%A8%E9%87%8F%E4%B8%8E%E8%B4%9F%E8%BD%BD) | 2 | 有源滤波与交流电子负载 / APF and AC electronic load |
| [09_控制与信号处理](09_%E6%8E%A7%E5%88%B6%E4%B8%8E%E4%BF%A1%E5%8F%B7%E5%A4%84%E7%90%86) | 2 | 独立 DPWM 与非线性 S-Function 实验 / Standalone control and signal processing |
| [10_建模与计算](10_%E5%BB%BA%E6%A8%A1%E4%B8%8E%E8%AE%A1%E7%AE%97) | — | 三个 MATLAB Live Script / Three MATLAB Live Scripts |
| [11_并网交直流接口](11_%E5%B9%B6%E7%BD%91%E4%BA%A4%E7%9B%B4%E6%B5%81%E6%8E%A5%E5%8F%A3) | 2 | CSI 与 TNPC 并网接口；功率方向待核验 / Grid-connected interfaces; power direction unverified |

## 打开前 / Before opening

- 从模型所在文件夹打开，按需加载参数脚本。最高保存版本为 R2024b。
- 多数功率模型需要 Specialized Power Systems（SPS）。该库从 R2026a 起移除，使用新版时需先迁移模型。[MathWorks 指南](https://www.mathworks.com/help/simscape-electrical/ug/upgrade-sps-models-to-use-simscape-blocks.html)
- 部分分析脚本需要 Control System Toolbox，PSIM 原理图用 PSIM 打开。
- `SFun_BS.slx` 是不完整实验，控制器文件和初始化需补全。

Open models from their folders and load parameter scripts as needed. The latest saved release is R2024b. Most power models use Specialized Power Systems, which was removed in R2026a. Migrate these models to use them in newer releases. Some scripts need Control System Toolbox. Open the PSIM schematic with PSIM. `SFun_BS.slx` still needs its controller files and initialization.

## 模型清单 / Model index

保存版本为模型文件最后保存时的 MATLAB release。

The release is the MATLAB version used to save the model.

### 01_DC-DC

| 模型 / Model | 保存版本 / Release | 说明 / Description |
| --- | --- | --- |
| [buck.slx](01_DC-DC/Buck/buck.slx) | R2021a | Buck 变换器 / Buck converter |
| [dcdc.slx](01_DC-DC/Buck/dcdc.slx) | R2023b | DC-DC 变换器 / DC-DC converter |
| [double_DCDC.slx](01_DC-DC/Buck/double_DCDC.slx) | R2021a | 双 DC-DC 变换器 / Dual DC-DC converter |
| [MPC_BUCK.slx](01_DC-DC/Buck_%E7%94%B5%E6%B5%81%E6%8E%A7%E5%88%B6/MPC_BUCK.slx) | R2023b | Buck 预测控制 / Model-predictive Buck control |
| [parallelbuck.slx](01_DC-DC/Buck_%E7%94%B5%E6%B5%81%E6%8E%A7%E5%88%B6/parallelbuck.slx) | R2023b | 并联 Buck / Parallel Buck converters |
| [LLC_FREQ.slx](01_DC-DC/LLC/LLC_FREQ.slx) | R2022b | LLC 频率控制 / LLC frequency control |
| [LLC_FREQ_2016.slx](01_DC-DC/LLC/LLC_FREQ_2016.slx) | R2021a | LLC 频率控制模型 / LLC frequency-control model |
| [PSM.slx](01_DC-DC/LLC/PSM/psim%E4%BB%BF%E7%9C%9F/PSM.slx) | R2023a | LLC 移相调制 / LLC phase-shift modulation |
| [PSM_2016.slx](01_DC-DC/LLC/PSM/simulink/PSM_2016.slx) | R2016a | LLC 移相调制模型 / LLC phase-shift model |
| [singal_three.slx](01_DC-DC/%E4%B8%89%E7%9B%B8%E8%80%A6%E5%90%88%E9%9A%94%E7%A6%BB/singal_three.slx) | R2023b | 三相耦合隔离 DC-DC / Three-phase coupled isolated DC-DC |
| [Dual3LevelBoost.slx](01_DC-DC/%E4%BA%A4%E9%94%99%E4%B8%89%E7%94%B5%E5%B9%B3Boost/Dual3LevelBoost.slx) | R2023b | 交错三电平 Boost / Interleaved three-level boost |
| [SRCDAB.slx](01_DC-DC/%E8%B0%90%E6%8C%AF%E5%8F%8C%E6%9C%89%E6%BA%90%E6%A1%A5/SRCDAB.slx) | R2023b | 串联谐振双有源桥 / Series-resonant dual active bridge |
| [chaodianRM.slx](01_DC-DC/%E8%B6%85%E7%BA%A7%E7%94%B5%E5%AE%B9/chaodianRM.slx) | R2021b | 超级电容系统 / Supercapacitor system |
| [FCbuck_boost.slx](01_DC-DC/%E9%A3%9E%E8%B7%A8%E7%94%B5%E5%AE%B9Buck-Boost/FCbuck_boost.slx) | R2023b | 飞跨电容三电平反相 Buck-Boost / Flying-capacitor three-level inverting buck-boost |

### 02_AC-DC

| 模型 / Model | 保存版本 / Release | 说明 / Description |
| --- | --- | --- |
| [MMCRect21Level.slx](02_AC-DC/MMC/MMCRect21Level.slx) | R2023b | 21 电平 MMC 整流器 / 21-level MMC rectifier |
| [MMC_Rectifier_NLM_2018.mdl](02_AC-DC/MMC/MMC_Rectifier_NLM_2018.mdl) | R2023b | MMC 最近电平调制整流器 / MMC rectifier with nearest-level modulation |
| [AFBPFC.slx](02_AC-DC/PFC/AFBPFC.slx) | R2023b | AFB PFC 仿真 / AFB PFC model |
| [DSFBPFC.slx](02_AC-DC/PFC/DSFBPFC.slx) | R2023b | DSFB PFC 仿真 / DSFB PFC model |
| [PFC.slx](02_AC-DC/PFC/PFC.slx) | R2021a | 功率因数校正 / Power factor correction |
| [QPR.slx](02_AC-DC/PFC/QPR.slx) | R2021a | 全桥整流与 QPR 控制 / Full-bridge rectifier with QPR control |
| [pfc1.slx](02_AC-DC/PFC/pfc1.slx) | R2023b | PFC 仿真 / PFC model |
| [pfc2023b.slx](02_AC-DC/PFC/pfc2023b.slx) | R2023b | PFC 仿真 / PFC model |
| [DualPWMRECT.slx](02_AC-DC/PWM%E6%95%B4%E6%B5%81/DualPWMRECT.slx) | R2021b | 双 PWM 整流 / Dual PWM rectifier |
| [PQRECT.slx](02_AC-DC/PWM%E6%95%B4%E6%B5%81/PQRECT.slx) | R2021b | PWM 整流与 PQ 控制 / PWM rectifier with PQ control |
| [PWMRECT1ph.slx](02_AC-DC/PWM%E6%95%B4%E6%B5%81/PWMRECT1ph.slx) | R2021b | 单相 PWM 整流 / Single-phase PWM rectifier |
| [PWMRECT30V.slx](02_AC-DC/PWM%E6%95%B4%E6%B5%81/PWMRECT30V.slx) | R2021b | PWM 整流 / PWM rectifier |
| [ThreePhase_Rectifier.slx](02_AC-DC/PWM%E6%95%B4%E6%B5%81/ThreePhase_Rectifier.slx) | R2021b | 三相整流 / Three-phase rectifier |
| [ANPCVienna_DPWMA.slx](02_AC-DC/Vienna%E4%B8%8ENPC/ANPCVienna_DPWMA.slx) | R2023b | ANPC Vienna 整流与 DPWM-A / ANPC Vienna rectifier with DPWM-A |
| [DualViennaRECT.slx](02_AC-DC/Vienna%E4%B8%8ENPC/DualViennaRECT.slx) | R2021b | 双 Vienna 整流 / Dual Vienna rectifier |
| [FCNPC1PH.slx](02_AC-DC/Vienna%E4%B8%8ENPC/FCNPC1PH.slx) | R2023b | 单相飞跨电容 NPC 整流 / Single-phase flying-capacitor NPC rectifier |
| [FCNPC1PHREC.slx](02_AC-DC/Vienna%E4%B8%8ENPC/FCNPC1PHREC.slx) | R2023b | 单相飞跨电容 NPC 整流 / Single-phase flying-capacitor NPC rectifier |
| [FCNPC3PH.slx](02_AC-DC/Vienna%E4%B8%8ENPC/FCNPC3PH.slx) | R2023b | 三相飞跨电容 NPC 整流 / Three-phase flying-capacitor NPC rectifier |
| [INPCVienna_DPWMA.slx](02_AC-DC/Vienna%E4%B8%8ENPC/INPCVienna_DPWMA.slx) | R2023b | INPC Vienna 整流与 DPWM-A / INPC Vienna rectifier with DPWM-A |
| [PQVienna.slx](02_AC-DC/Vienna%E4%B8%8ENPC/PQVienna.slx) | R2023b | Vienna 整流与 PQ 控制 / Vienna rectifier with PQ control |
| [SVienna.slx](02_AC-DC/Vienna%E4%B8%8ENPC/SVienna.slx) | R2021b | Vienna 整流 / Vienna rectifier |
| [Vienna1ph.slx](02_AC-DC/Vienna%E4%B8%8ENPC/Vienna1ph.slx) | R2021b | 单相 Vienna 整流 / Single-phase Vienna rectifier |
| [Vienna_DPWMA.slx](02_AC-DC/Vienna%E4%B8%8ENPC/Vienna_DPWMA.slx) | R2023b | Vienna 整流与 DPWM-A / Vienna rectifier with DPWM-A |
| [ACDC.slx](02_AC-DC/%E6%99%B6%E9%97%B8%E7%AE%A1%E6%95%B4%E6%B5%81/ACDC.slx) | R2021a | 晶闸管整流 / Thyristor rectifier |
| [CSR.slx](02_AC-DC/%E7%94%B5%E6%B5%81%E6%BA%90%E6%95%B4%E6%B5%81/CSR.slx) | R2023b | 电流源整流 / Current-source rectifier |
| [CSR1.slx](02_AC-DC/%E7%94%B5%E6%B5%81%E6%BA%90%E6%95%B4%E6%B5%81/CSR1.slx) | R2021b | 电流源整流 / Current-source rectifier |
| [CSR2.0.slx](02_AC-DC/%E7%94%B5%E6%B5%81%E6%BA%90%E6%95%B4%E6%B5%81/CSR2.0.slx) | R2023b | 电流源整流 / Current-source rectifier |
| [CHB.slx](02_AC-DC/%E7%BA%A7%E8%81%94%E6%95%B4%E6%B5%81%E4%B8%8E%E9%9A%94%E7%A6%BB%E8%BE%93%E5%87%BA/CHB.slx) | R2023b | 级联 H 桥整流 / Cascaded H-bridge rectifier |
| [CHBwithLLC.slx](02_AC-DC/%E7%BA%A7%E8%81%94%E6%95%B4%E6%B5%81%E4%B8%8E%E9%9A%94%E7%A6%BB%E8%BE%93%E5%87%BA/CHBwithLLC.slx) | R2023b | 级联 H 桥整流与 LLC 隔离级 / CHB rectifier with LLC isolation |
| [DPWMA17levelRECT.slx](02_AC-DC/%E7%BA%A7%E8%81%94%E6%95%B4%E6%B5%81%E4%B8%8E%E9%9A%94%E7%A6%BB%E8%BE%93%E5%87%BA/DPWMA17levelRECT.slx) | R2021b | 17 电平整流与双 PI 控制 / 17-level rectifier with dual PI control |
| [DPWMA17levelRECT_DigitalPR.slx](02_AC-DC/%E7%BA%A7%E8%81%94%E6%95%B4%E6%B5%81%E4%B8%8E%E9%9A%94%E7%A6%BB%E8%BE%93%E5%87%BA/DPWMA17levelRECT_DigitalPR.slx) | R2023b | 17 电平整流与数字 PR 控制 / 17-level rectifier with digital PR control |
| [rec4.slx](02_AC-DC/%E7%BA%A7%E8%81%94%E6%95%B4%E6%B5%81%E4%B8%8E%E9%9A%94%E7%A6%BB%E8%BE%93%E5%87%BA/rec4.slx) | R2021b | 整流与隔离输出 / Rectifier with isolated output |
| [REC1.slx](02_AC-DC/PWM%E6%95%B4%E6%B5%81/REC1.slx) | R2023b | 单相 PWM 整流及 PFC、PR 控制 / Single-phase PWM rectifier with PFC and PR control |

### 03_DC-AC

| 模型 / Model | 保存版本 / Release | 说明 / Description |
| --- | --- | --- |
| [DPWMAx2025A.slx](03_DC-AC/%E4%B8%89%E7%9B%B8%E4%B8%8E%E5%A4%9A%E6%A1%A5%E8%87%82/DPWMAx2025A.slx) | R2023b | 双三桥臂逆变与 DPWM / Dual three-leg inverter with DPWM |
| [DTNPC.slx](03_DC-AC/%E4%B8%89%E7%9B%B8%E4%B8%8E%E5%A4%9A%E6%A1%A5%E8%87%82/DTNPC.slx) | R2023b | DTNPC 逆变 / DTNPC inverter |
| [FH3P4LINVT.slx](03_DC-AC/%E4%B8%89%E7%9B%B8%E4%B8%8E%E5%A4%9A%E6%A1%A5%E8%87%82/FH3P4LINVT.slx) | R2023b | 三相四桥臂逆变 / Three-phase four-leg inverter |
| [PH2INV.slx](03_DC-AC/%E4%B8%89%E7%9B%B8%E4%B8%8E%E5%A4%9A%E6%A1%A5%E8%87%82/PH2INV.slx) | R2021a | 多桥臂逆变 / Multi-leg inverter |
| [TNPC3P4L.slx](03_DC-AC/%E4%B8%89%E7%9B%B8%E4%B8%8E%E5%A4%9A%E6%A1%A5%E8%87%82/TNPC3P4L.slx) | R2023b | 三相四桥臂 T-NPC 逆变 / Three-phase four-leg T-NPC inverter |
| [Heric.slx](03_DC-AC/%E5%8D%95%E7%9B%B8%E9%80%86%E5%8F%98/Heric.slx) | R2023b | 单相 HERIC 逆变 / Single-phase HERIC inverter |
| [Vienna_Inv1ph.slx](03_DC-AC/%E5%8D%95%E7%9B%B8%E9%80%86%E5%8F%98/Vienna_Inv1ph.slx) | R2023b | 单相 Vienna 逆变 / Single-phase Vienna inverter |
| [invslx.slx](03_DC-AC/%E5%8D%95%E7%9B%B8%E9%80%86%E5%8F%98/invslx.slx) | R2021a | 单相逆变实验 / Single-phase inverter experiment |
| [NLM3LFCNPC.slx](03_DC-AC/%E8%B0%90%E6%8C%AF%E9%A9%B1%E5%8A%A8/NLM3LFCNPC.slx) | R2023b | 三电平 FCNPC LC 谐振驱动 / Three-level FCNPC LC resonant drive |

### 04_AC-DC-AC

| 模型 / Model | 保存版本 / Release | 说明 / Description |
| --- | --- | --- |
| [ACDCACsummarycircuit.slx](04_AC-DC-AC/ACDCACsummarycircuit.slx) | R2023b | 完整交直交变换链 / Complete AC-DC-AC conversion chain |

### 05_UPS

| 模型 / Model | 保存版本 / Release | 说明 / Description |
| --- | --- | --- |
| [UPS.slx](05_UPS/UPS.slx) | R2023b | UPS 系统 / UPS system |
| [UPS2.slx](05_UPS/UPS2.slx) | R2023b | UPS 系统 / UPS system |

### 06_电网控制

| 模型 / Model | 保存版本 / Release | 说明 / Description |
| --- | --- | --- |
| [Droop_nomslx.slx](06_%E7%94%B5%E7%BD%91%E6%8E%A7%E5%88%B6/Droop/Droop_nomslx.slx) | R2021a | 交流下垂控制 / AC droop control |
| [Droopslx.slx](06_%E7%94%B5%E7%BD%91%E6%8E%A7%E5%88%B6/Droop/Droopslx.slx) | R2021a | 交流下垂控制 / AC droop control |
| [AC_VSG.slx](06_%E7%94%B5%E7%BD%91%E6%8E%A7%E5%88%B6/VSG/AC_VSG.slx) | R2021b | 并联逆变器虚拟同步发电机 / Parallel-inverter virtual synchronous generator |
| [vsg.slx](06_%E7%94%B5%E7%BD%91%E6%8E%A7%E5%88%B6/VSG/vsg.slx) | R2023b | 虚拟同步发电机 / Virtual synchronous generator |

### 07_电机驱动

| 模型 / Model | 保存版本 / Release | 说明 / Description |
| --- | --- | --- |
| [PMSM_FOC.slx](07_%E7%94%B5%E6%9C%BA%E9%A9%B1%E5%8A%A8/PMSM/PMSM_FOC.slx) | R2024b | 永磁同步电机磁场定向控制 / PMSM field-oriented control |
| [INVT.slx (induction motor)](07_%E7%94%B5%E6%9C%BA%E9%A9%B1%E5%8A%A8/%E5%BC%82%E6%AD%A5%E7%94%B5%E6%9C%BA/INVT.slx) | R2023b | 单相异步电机和两相三桥臂 DPWM / Single-phase induction motor and two-phase three-leg DPWM |

### 08_电能质量与负载

| 模型 / Model | 保存版本 / Release | 说明 / Description |
| --- | --- | --- |
| [APF2025B.slx](08_%E7%94%B5%E8%83%BD%E8%B4%A8%E9%87%8F%E4%B8%8E%E8%B4%9F%E8%BD%BD/APF/APF2025B.slx) | R2023b | 有源电力滤波器 / Active power filter |
| [Ac_load.slx](08_%E7%94%B5%E8%83%BD%E8%B4%A8%E9%87%8F%E4%B8%8E%E8%B4%9F%E8%BD%BD/%E4%BA%A4%E6%B5%81%E7%94%B5%E5%AD%90%E8%B4%9F%E8%BD%BD/Ac_load.slx) | R2023b | 交流电子负载 / AC electronic load |

### 09_控制与信号处理

| 模型 / Model | 保存版本 / Release | 说明 / Description |
| --- | --- | --- |
| [dpwm.slx](09_%E6%8E%A7%E5%88%B6%E4%B8%8E%E4%BF%A1%E5%8F%B7%E5%A4%84%E7%90%86/DPWM/dpwm.slx) | R2024b | 独立 DPWM 调制 / Standalone DPWM modulation |
| [SFun_BS.slx](09_%E6%8E%A7%E5%88%B6%E4%B8%8E%E4%BF%A1%E5%8F%B7%E5%A4%84%E7%90%86/SFunction/SFun_BS.slx) | R2021a | 不完整的非线性 S-Function 实验 / Incomplete nonlinear S-Function experiment |

### 11_并网交直流接口

| 模型 / Model | 保存版本 / Release | 说明 / Description |
| --- | --- | --- |
| [CSI.slx](11_%E5%B9%B6%E7%BD%91%E4%BA%A4%E7%9B%B4%E6%B5%81%E6%8E%A5%E5%8F%A3/CSI.slx) | R2023b | 电流型并网接口，功率方向待核验 / Current-source grid interface; power direction unverified |
| [TNPC3P3W1.slx](11_%E5%B9%B6%E7%BD%91%E4%BA%A4%E7%9B%B4%E6%B5%81%E6%8E%A5%E5%8F%A3/TNPC3P3W1.slx) | R2023b | T-NPC 并网接口，功率方向待核验 / T-NPC grid interface; power direction unverified |

## 分类参考 / References

- [MathWorks: Power electronic converter selection](https://www.mathworks.com/help/simscape-electrical/ug/choose-power-electronic-converter-block.html)
- [TI: ANPC power stage for both inverters and PFCs](https://www.ti.com/tool/TIDA-010210)
- [Plexim: Converter and application examples](https://www.plexim.com/support/examples)
- [MathWorks: PWM reference generator, including DPWM](https://www.mathworks.com/help/mcb/ref/pwmreferencegenerator.html)
