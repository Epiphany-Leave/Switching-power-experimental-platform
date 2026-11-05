# 仿真导航 / Simulation Guide

[中文首页](../README.md) · [English overview](../README.en.md)

共 **71 个当前模型（70 SLX + 1 MDL）**，另保留参数/分析脚本、PSIM 文件与 7 个历史/自动保存版本。模型二进制内容未修改。

**71 current models (70 SLX + 1 MDL)**, plus scripts, a PSIM schematic and 7 historical/autosave files. Model contents are preserved byte for byte.

## 分类原则 / Classification

完整应用优先；通用功率级按实际电源、负载、有效连接及控制目标分类；纯算法单列。CHB/NPC/DPWM 等名称不能决定功率方向；内部高频交流不改变 LLC/DAB 整体 DC-DC 类别。两个静态方向不确定的并网接口单列，不强行判断整流或逆变。

Complete applications take priority. Generic converters are classified by their sources, loads, active connections and control objectives; standalone algorithms are separate. Topology names alone do not determine power direction. Internal high-frequency AC does not turn an isolated DC-DC stage into an inverter system. Two interfaces with unverified power direction have a separate category.

| 目录 / Folder | 当前模型 / Models | 内容 / Scope |
| --- | ---: | --- |
| [01_DC-DC](01_DC-DC) | 14 | Buck、交错 Boost、LLC、谐振双有源桥、超级电容及耦合隔离 / DC-DC power stages |
| [02_AC-DC](02_AC-DC) | 32 | PFC、PWM/CSR、Vienna/NPC、CHB、MMC及带隔离输出的整流 / Rectification and PFC |
| [03_DC-AC](03_DC-AC) | 10 | 单相、三相、多桥臂与含 SOGI-PLL 的逆变实验 / Inverter experiments |
| [04_AC-DC-AC](04_AC-DC-AC) | 1 | 完整交直交变换链 / Complete AC-DC-AC chain |
| [05_UPS](05_UPS) | 2 | 不间断电源系统 / UPS systems |
| [06_电网控制](06_%E7%94%B5%E7%BD%91%E6%8E%A7%E5%88%B6) | 4 | VSG 与交流下垂控制系统 / VSG and AC droop systems |
| [07_电机驱动](07_%E7%94%B5%E6%9C%BA%E9%A9%B1%E5%8A%A8) | 1 | PMSM 磁场定向控制 / PMSM field-oriented control |
| [08_电能质量与负载](08_%E7%94%B5%E8%83%BD%E8%B4%A8%E9%87%8F%E4%B8%8E%E8%B4%9F%E8%BD%BD) | 2 | 有源滤波与交流电子负载 / APF and AC electronic load |
| [09_控制与信号处理](09_%E6%8E%A7%E5%88%B6%E4%B8%8E%E4%BF%A1%E5%8F%B7%E5%A4%84%E7%90%86) | 3 | 独立 DPWM、Sigma-Delta ADC、非线性 S-Function 实验 / Standalone control and signal processing |
| [10_建模与计算](10_%E5%BB%BA%E6%A8%A1%E4%B8%8E%E8%AE%A1%E7%AE%97) | — | 三个 MATLAB Live Script / Three MATLAB Live Scripts |
| [11_并网交直流接口](11_%E5%B9%B6%E7%BD%91%E4%BA%A4%E7%9B%B4%E6%B5%81%E6%8E%A5%E5%8F%A3) | 2 | CSI 与 TNPC 并网接口；功率方向待核验 / Grid-connected interfaces; power direction unverified |
| [90_历史版本](90_%E5%8E%86%E5%8F%B2%E7%89%88%E6%9C%AC) | — | 六个旧版本模型与一个自动保存文件 / Six model backups and one autosave |

## 打开前 / Before opening

- 从下方进入模型所在文件夹，将该文件夹设为 MATLAB 当前目录；按模型需要加载同目录参数脚本。不要把全部子文件夹同时加入搜索路径，部分历史版本或不同实验具有同名模型。
- 保存版本来自文件元数据，分布在 R2016a–R2024b，不代表已经验证兼容性。`dpwm.slx` 与 `PMSM_FOC.slx` 保存于 R2024b；较低版本 MATLAB 可能无法直接打开。
- 多数功率模型使用 Specialized Power Systems 的 `powerlib` / `sps_*` 库，需具有对应组件的 MATLAB/Simulink 环境。计算脚本使用的 `tf`、`bode` 等还需要 Control System Toolbox；PSIM 文件需要相应软件。
- `SD_ADC.slx` 引用了外部 `SDtoolbox/Power Spectral Density`，本仓库不含该工具箱。
- `SFunction/SFun_BS.slx` 是原始未完成实验：需要变量 `pa` 和 `ctrl`/`plant`。原仓库脚本 `parameters.m`、`plant.m`、`crtl.m` 已一起保留，但 `ctrl.m` 缺失，`crtl.m` 主函数名却为 `plant`，参考输入和初始化也有不一致。它们仅作为原始资料保留，未修复或宣称可直接运行。
- `SOGI_PLLslx.slx` 属于完整逆变实验，自带初始化参数；上述 S-Function 脚本不是它的依赖。其交流源为 100 Hz、PLL 基频为 50 Hz，具体实验设定需进一步核验。

Open a model from its own folder and load the required local parameter scripts. Avoid adding every folder to the MATLAB path: some models share names. Saved releases are metadata, not compatibility guarantees. Most power models require the matching Specialized Power Systems libraries; analysis scripts may require Control System Toolbox, and the PSIM schematic needs PSIM. `SD_ADC.slx` requires the external SDtoolbox. The original S-Function experiment has missing/mismatched controller files and incomplete inputs; retained scripts do not make it runnable. The SOGI-PLL inverter has its own initialization and a 100 Hz AC-source / 50 Hz PLL setting that needs review.

本次完成静态结构、文件完整性与路径检查，未运行模型或验证控制性能。缓存、加速编译文件和生成代码仅在本地 `99_本地生成文件` 保留，不随仓库发布。历史源文件保存在 `90_历史版本`，不冒充当前模型。

Static structure, integrity and paths were checked; simulations and control performance were not validated. Generated caches and build products remain in the local archive only. Historical source files are kept separately.

## 模型清单 / Model index

保存版本是最后写入文件的 MATLAB release。原路径仅用于追溯，点击模型名进入新位置。

The release shown is the saved-file release. Original paths provide provenance; links point to the reorganized files.

### 01_DC-DC

| 模型 / Model | 保存版本 / Release | 原路径与说明 / Origin and notes |
| --- | --- | --- |
| [buck.slx](01_DC-DC/Buck/buck.slx) | R2021a | `SD_ADC/buck.slx` |
| [dcdc.slx](01_DC-DC/Buck/dcdc.slx) | R2023b | `dcdc.slx` |
| [double_DCDC.slx](01_DC-DC/Buck/double_DCDC.slx) | R2021a | `SD_ADC/double_DCDC.slx` |
| [MPC_BUCK.slx](01_DC-DC/Buck_%E7%94%B5%E6%B5%81%E6%8E%A7%E5%88%B6/MPC_BUCK.slx) | R2023b | `currentsource/MPC_BUCK.slx` |
| [parallelbuck.slx](01_DC-DC/Buck_%E7%94%B5%E6%B5%81%E6%8E%A7%E5%88%B6/parallelbuck.slx) | R2023b | `currentsource/parallelbuck.slx` |
| [LLC_FREQ.slx](01_DC-DC/LLC/LLC_FREQ.slx) | R2022b | `LLC/LLC_FREQ.slx` |
| [LLC_FREQ_2016.slx](01_DC-DC/LLC/LLC_FREQ_2016.slx) | R2021a | `LLC/LLC_FREQ_2016.slx` |
| [PSM.slx](01_DC-DC/LLC/PSM/psim%E4%BB%BF%E7%9C%9F/PSM.slx) | R2023a | `LLC/PSM/psim仿真/PSM.slx` |
| [PSM_2016.slx](01_DC-DC/LLC/PSM/simulink/PSM_2016.slx) | R2016a | `LLC/PSM/simulink/PSM_2016.slx` |
| [singal_three.slx](01_DC-DC/%E4%B8%89%E7%9B%B8%E8%80%A6%E5%90%88%E9%9A%94%E7%A6%BB/singal_three.slx) | R2023b | `VSG/singal_three.slx`；原在 VSG；实际 DC→逆变→耦合→整流→DC / DC-DC, originally in VSG |
| [Dual3LevelBoost.slx](01_DC-DC/%E4%BA%A4%E9%94%99%E4%B8%89%E7%94%B5%E5%B9%B3Boost/Dual3LevelBoost.slx) | R2023b | `ThreeP/Dual3LevelBoost.slx` |
| [Dual3LevelBoost2.slx](01_DC-DC/%E4%BA%A4%E9%94%99%E4%B8%89%E7%94%B5%E5%B9%B3Boost/Dual3LevelBoost2.slx) | R2023b | `ThreeP/Dual3LevelBoost2.slx`；与 Dual3LevelBoost 内容完全相同；保留原文件 / Byte-identical variant retained |
| [SRCDAB.slx](01_DC-DC/%E8%B0%90%E6%8C%AF%E5%8F%8C%E6%9C%89%E6%BA%90%E6%A1%A5/SRCDAB.slx) | R2023b | `SRCDAB.slx` |
| [chaodianRM.slx](01_DC-DC/%E8%B6%85%E7%BA%A7%E7%94%B5%E5%AE%B9/chaodianRM.slx) | R2021b | `chaodian/chaodianRM.slx` |

### 02_AC-DC

| 模型 / Model | 保存版本 / Release | 原路径与说明 / Origin and notes |
| --- | --- | --- |
| [MMCRect21Level.slx](02_AC-DC/MMC/MMCRect21Level.slx) | R2023b | `MMCRect21Level.slx` |
| [MMC_Rectifier_NLM_2018.mdl](02_AC-DC/MMC/MMC_Rectifier_NLM_2018.mdl) | R2023b | `MMC_Rectifier_NLM_2018.mdl` |
| [AFBPFC.slx](02_AC-DC/PFC/AFBPFC.slx) | R2023b | `AFBPFC.slx` |
| [DSFBPFC.slx](02_AC-DC/PFC/DSFBPFC.slx) | R2023b | `DSFBPFC.slx` |
| [PFC.slx](02_AC-DC/PFC/PFC.slx) | R2021a | `PFC/PFC.slx` |
| [QPR.slx](02_AC-DC/PFC/QPR.slx) | R2021a | `PFC/QPR.slx`；带全桥整流功率级，非纯 QPR / Full-bridge rectifier, not a standalone controller |
| [pfc1.slx](02_AC-DC/PFC/pfc1.slx) | R2023b | `PFC/pfc1.slx` |
| [pfc2023b.slx](02_AC-DC/PFC/pfc2023b.slx) | R2023b | `pfc2023b.slx` |
| [DualPWMRECT.slx](02_AC-DC/PWM%E6%95%B4%E6%B5%81/DualPWMRECT.slx) | R2021b | `PWMReact/DualPWMRECT.slx` |
| [PQRECT.slx](02_AC-DC/PWM%E6%95%B4%E6%B5%81/PQRECT.slx) | R2021b | `PWMReact/PQRECT.slx` |
| [PWMRECT1ph.slx](02_AC-DC/PWM%E6%95%B4%E6%B5%81/PWMRECT1ph.slx) | R2023b | `PWMReact/PWMRECT1ph.slx` |
| [PWMRECT30V.slx](02_AC-DC/PWM%E6%95%B4%E6%B5%81/PWMRECT30V.slx) | R2021b | `PWMRECT30V.slx` |
| [ThreePhase_Rectifier.slx](02_AC-DC/PWM%E6%95%B4%E6%B5%81/ThreePhase_Rectifier.slx) | R2023b | `ThreeP/ThreePhase_Rectifier.slx` |
| [ANPCVienna_DPWMA.slx](02_AC-DC/Vienna%E4%B8%8ENPC/ANPCVienna_DPWMA.slx) | R2023b | `ANPCVienna_DPWMA.slx`；按交流源、直流负载和外环归整流 / Classified by source, load and control loop |
| [DualViennaRECT.slx](02_AC-DC/Vienna%E4%B8%8ENPC/DualViennaRECT.slx) | R2021b | `ThreeP/DualViennaRECT.slx` |
| [FCNPC1PH.slx](02_AC-DC/Vienna%E4%B8%8ENPC/FCNPC1PH.slx) | R2023b | `FCNPC1PH.slx`；交流源、直流负载与母线电压环 / AC supply, DC load and bus control |
| [FCNPC1PHREC.slx](02_AC-DC/Vienna%E4%B8%8ENPC/FCNPC1PHREC.slx) | R2023b | `FCNPC1PHREC.slx` |
| [FCNPC3PH.slx](02_AC-DC/Vienna%E4%B8%8ENPC/FCNPC3PH.slx) | R2023b | `FCNPC3PH.slx`；交流输入、直流负载 / AC input and DC load |
| [INPCVienna_DPWMA.slx](02_AC-DC/Vienna%E4%B8%8ENPC/INPCVienna_DPWMA.slx) | R2023b | `INPCVienna_DPWMA.slx` |
| [PQVienna.slx](02_AC-DC/Vienna%E4%B8%8ENPC/PQVienna.slx) | R2023b | `PQVienna.slx` |
| [SVienna.slx](02_AC-DC/Vienna%E4%B8%8ENPC/SVienna.slx) | R2021b | `SVienna.slx` |
| [TNPC3P4L.slx](02_AC-DC/Vienna%E4%B8%8ENPC/TNPC3P4L.slx) | R2023b | `ThreeP/TNPC3P4L.slx`；交流输入与直流负载；与根目录同名文件不同 / AC input and DC load; distinct namesake |
| [Vienna1ph.slx](02_AC-DC/Vienna%E4%B8%8ENPC/Vienna1ph.slx) | R2023b | `PWMReact/Vienna1ph.slx` |
| [Vienna_DPWMA.slx](02_AC-DC/Vienna%E4%B8%8ENPC/Vienna_DPWMA.slx) | R2023b | `ThreeP/Vienna_DPWMA.slx`；含直流源支路；按母线 PI 外环归整流实验 / DC-side source branch; DC-bus PI control |
| [ACDC.slx](02_AC-DC/%E6%99%B6%E9%97%B8%E7%AE%A1%E6%95%B4%E6%B5%81/ACDC.slx) | R2021a | `ACDC.slx` |
| [CSR.slx](02_AC-DC/%E7%94%B5%E6%B5%81%E6%BA%90%E6%95%B4%E6%B5%81/CSR.slx) | R2023b | `CSR.slx` |
| [CSR1.slx](02_AC-DC/%E7%94%B5%E6%B5%81%E6%BA%90%E6%95%B4%E6%B5%81/CSR1.slx) | R2021b | `chaodian/CSR1.slx` |
| [CSR2.0.slx](02_AC-DC/%E7%94%B5%E6%B5%81%E6%BA%90%E6%95%B4%E6%B5%81/CSR2.0.slx) | R2023b | `CSR2.0.slx` |
| [CHB.slx](02_AC-DC/%E7%BA%A7%E8%81%94%E6%95%B4%E6%B5%81%E4%B8%8E%E9%9A%94%E7%A6%BB%E8%BE%93%E5%87%BA/CHB.slx) | R2023b | `CHB.slx`；交流源与直流电压外环 / AC supply and DC-bus voltage loop |
| [CHBwithLLC.slx](02_AC-DC/%E7%BA%A7%E8%81%94%E6%95%B4%E6%B5%81%E4%B8%8E%E9%9A%94%E7%A6%BB%E8%BE%93%E5%87%BA/CHBwithLLC.slx) | R2023b | `CHBwithLLC.slx`；CHB 整流后接隔离级 / CHB rectifier with isolated output stage |
| [DPWMA17levelRECT.slx](02_AC-DC/%E7%BA%A7%E8%81%94%E6%95%B4%E6%B5%81%E4%B8%8E%E9%9A%94%E7%A6%BB%E8%BE%93%E5%87%BA/DPWMA17levelRECT.slx) | R2021b | `DPWM/DPWMA17levelRECT.slx`；包含整流功率级，非独立 DPWM / Includes rectifier power stage |
| [rec4.slx](02_AC-DC/%E7%BA%A7%E8%81%94%E6%95%B4%E6%B5%81%E4%B8%8E%E9%9A%94%E7%A6%BB%E8%BE%93%E5%87%BA/rec4.slx) | R2021b | `rec4.slx`；交流输入、隔离级与直流输出 / AC input, isolated stages, DC output |

### 03_DC-AC

| 模型 / Model | 保存版本 / Release | 原路径与说明 / Origin and notes |
| --- | --- | --- |
| [SOGI_PLLslx.slx](03_DC-AC/SOGI_PLL/SOGI_PLLslx.slx) | R2021a | `GitHub:04_仿真/SOGI_PLL/SOGI_PLLslx.slx`；原仓库保留；带功率级的逆变实验 / Existing repository inverter experiment |
| [DPWMAx2025A.slx](03_DC-AC/%E4%B8%89%E7%9B%B8%E4%B8%8E%E5%A4%9A%E6%A1%A5%E8%87%82/DPWMAx2025A.slx) | R2023b | `DPWMAx2025A.slx`；直流源与双三桥臂，非独立调制算法 / DC supply and dual three-leg bridges |
| [DTNPC.slx](03_DC-AC/%E4%B8%89%E7%9B%B8%E4%B8%8E%E5%A4%9A%E6%A1%A5%E8%87%82/DTNPC.slx) | R2023b | `ThreeP/DTNPC.slx` |
| [FH3P4LINVT.slx](03_DC-AC/%E4%B8%89%E7%9B%B8%E4%B8%8E%E5%A4%9A%E6%A1%A5%E8%87%82/FH3P4LINVT.slx) | R2023b | `FH3P4LINVT.slx` |
| [PH2INV.slx](03_DC-AC/%E4%B8%89%E7%9B%B8%E4%B8%8E%E5%A4%9A%E6%A1%A5%E8%87%82/PH2INV.slx) | R2021a | `PH2INV.slx` |
| [TNPC3P4L.slx](03_DC-AC/%E4%B8%89%E7%9B%B8%E4%B8%8E%E5%A4%9A%E6%A1%A5%E8%87%82/TNPC3P4L.slx) | R2023b | `TNPC3P4L.slx`；直流输入与三相交流负载 / DC input, three-phase AC load |
| [Heric.slx](03_DC-AC/%E5%8D%95%E7%9B%B8%E9%80%86%E5%8F%98/Heric.slx) | R2023b | `Heric.slx` |
| [INVT.slx](03_DC-AC/%E5%8D%95%E7%9B%B8%E9%80%86%E5%8F%98/INVT.slx) | R2023b | `INVT.slx` |
| [Vienna_Inv1ph.slx](03_DC-AC/%E5%8D%95%E7%9B%B8%E9%80%86%E5%8F%98/Vienna_Inv1ph.slx) | R2023b | `PWMReact/Vienna_Inv1ph.slx` |
| [invslx.slx](03_DC-AC/%E5%8D%95%E7%9B%B8%E9%80%86%E5%8F%98/invslx.slx) | R2021a | `SD_ADC/invslx.slx` |

### 04_AC-DC-AC

| 模型 / Model | 保存版本 / Release | 原路径与说明 / Origin and notes |
| --- | --- | --- |
| [ACDCACsummarycircuit.slx](04_AC-DC-AC/ACDCACsummarycircuit.slx) | R2023b | `ACDCAC/ACDCACsummarycircuit.slx` |

### 05_UPS

| 模型 / Model | 保存版本 / Release | 原路径与说明 / Origin and notes |
| --- | --- | --- |
| [UPS.slx](05_UPS/UPS.slx) | R2023b | `UPS/UPS.slx` |
| [UPS2.slx](05_UPS/UPS2.slx) | R2023b | `UPS2.slx` |

### 06_电网控制

| 模型 / Model | 保存版本 / Release | 原路径与说明 / Origin and notes |
| --- | --- | --- |
| [Droop_nomslx.slx](06_%E7%94%B5%E7%BD%91%E6%8E%A7%E5%88%B6/Droop/Droop_nomslx.slx) | R2021a | `Droop/Droop_nomslx.slx` |
| [Droopslx.slx](06_%E7%94%B5%E7%BD%91%E6%8E%A7%E5%88%B6/Droop/Droopslx.slx) | R2021a | `Droop/Droopslx.slx` |
| [AC_VSG.slx](06_%E7%94%B5%E7%BD%91%E6%8E%A7%E5%88%B6/VSG/AC_VSG.slx) | R2023b | `VSG/AC_VSG.slx` |
| [vsg.slx](06_%E7%94%B5%E7%BD%91%E6%8E%A7%E5%88%B6/VSG/vsg.slx) | R2023b | `VSG/vsg.slx` |

### 07_电机驱动

| 模型 / Model | 保存版本 / Release | 原路径与说明 / Origin and notes |
| --- | --- | --- |
| [PMSM_FOC.slx](07_%E7%94%B5%E6%9C%BA%E9%A9%B1%E5%8A%A8/PMSM/PMSM_FOC.slx) | R2024b | `PMSM/PMSM_FOC.slx` |

### 08_电能质量与负载

| 模型 / Model | 保存版本 / Release | 原路径与说明 / Origin and notes |
| --- | --- | --- |
| [APF2025B.slx](08_%E7%94%B5%E8%83%BD%E8%B4%A8%E9%87%8F%E4%B8%8E%E8%B4%9F%E8%BD%BD/APF/APF2025B.slx) | R2023b | `APF2025B.slx` |
| [Ac_load.slx](08_%E7%94%B5%E8%83%BD%E8%B4%A8%E9%87%8F%E4%B8%8E%E8%B4%9F%E8%BD%BD/%E4%BA%A4%E6%B5%81%E7%94%B5%E5%AD%90%E8%B4%9F%E8%BD%BD/Ac_load.slx) | R2023b | `Ac_load.slx` |

### 09_控制与信号处理

| 模型 / Model | 保存版本 / Release | 原路径与说明 / Origin and notes |
| --- | --- | --- |
| [dpwm.slx](09_%E6%8E%A7%E5%88%B6%E4%B8%8E%E4%BF%A1%E5%8F%B7%E5%A4%84%E7%90%86/DPWM/dpwm.slx) | R2024b | `dpwm.slx` |
| [SFun_BS.slx](09_%E6%8E%A7%E5%88%B6%E4%B8%8E%E4%BF%A1%E5%8F%B7%E5%A4%84%E7%90%86/SFunction/SFun_BS.slx) | R2021a | `SFun_BS.slx`；原始实验不完整；参见依赖说明 / Incomplete original experiment; see dependencies |
| [SD_ADC.slx](09_%E6%8E%A7%E5%88%B6%E4%B8%8E%E4%BF%A1%E5%8F%B7%E5%A4%84%E7%90%86/SigmaDelta_ADC/SD_ADC.slx) | R2021a | `SD_ADC/SD_ADC.slx`；引用外部 SDtoolbox / Requires external SDtoolbox |

### 11_并网交直流接口

| 模型 / Model | 保存版本 / Release | 原路径与说明 / Origin and notes |
| --- | --- | --- |
| [CSI.slx](11_%E5%B9%B6%E7%BD%91%E4%BA%A4%E7%9B%B4%E6%B5%81%E6%8E%A5%E5%8F%A3/CSI.slx) | R2023b | `CSI.slx`；双电源接口；电流型结构，功率方向未运行核验 / Current-source grid interface; direction unverified |
| [TNPC3P3W1.slx](11_%E5%B9%B6%E7%BD%91%E4%BA%A4%E7%9B%B4%E6%B5%81%E6%8E%A5%E5%8F%A3/TNPC3P3W1.slx) | R2023b | `TNPC3P3W1.slx`；直流源与交流受控源接口；功率方向待核验 / DC/AC source interface; direction unverified |

## 分类参考 / References

- [MathWorks: Power electronic converter selection](https://www.mathworks.com/help/simscape-electrical/ug/choose-power-electronic-converter-block.html)
- [TI: ANPC power stage for both inverters and PFCs](https://www.ti.com/tool/TIDA-010210)
- [Plexim: Converter and application examples](https://www.plexim.com/support/examples)
- [MathWorks: PWM reference generator, including DPWM](https://www.mathworks.com/help/mcb/ref/pwmreferencegenerator.html)
