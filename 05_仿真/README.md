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
- `Backstepping_SFunction.slx` 使用同目录的 `ctrl.m` 和 `plant.m`。先运行 `parameters.m`，参考输入与初始化仍需核对。

Open models from their folders and load parameter scripts as needed. The latest saved release is R2024b. Most power models use Specialized Power Systems, which was removed in R2026a. Migrate these models to use them in newer releases. Some scripts need Control System Toolbox. Open the PSIM schematic with PSIM. For `Backstepping_SFunction.slx`, run the local `parameters.m` first. Its reference inputs and initialization still need checking.

## 模型清单 / Model index

保存版本为模型文件最后保存时的 MATLAB release。

The release is the MATLAB version used to save the model.

### 01_DC-DC

| 模型 / Model | 保存版本 / Release | 说明 / Description |
| --- | --- | --- |
| [buck.slx](01_DC-DC/Buck%E4%B8%8E%E5%8F%8C%E5%90%91%E5%8D%8A%E6%A1%A5/buck.slx) | R2021a | Buck 变换器 / Buck converter |
| [Buck_Closed_Loop.slx](01_DC-DC/Buck%E4%B8%8E%E5%8F%8C%E5%90%91%E5%8D%8A%E6%A1%A5/Buck_Closed_Loop.slx) | R2023b | 闭环 Buck / Closed-loop buck converter |
| [Bidirectional_Half_Bridge_DCDC.slx](01_DC-DC/Buck%E4%B8%8E%E5%8F%8C%E5%90%91%E5%8D%8A%E6%A1%A5/Bidirectional_Half_Bridge_DCDC.slx) | R2021a | 双向半桥 DC-DC / Bidirectional half-bridge DC-DC |
| [Buck_MPC.slx](01_DC-DC/Buck%E7%94%B5%E6%B5%81%E6%8E%A7%E5%88%B6/Buck_MPC.slx) | R2023b | Buck 预测控制 / Model-predictive Buck control |
| [Buck_Parallel.slx](01_DC-DC/Buck%E7%94%B5%E6%B5%81%E6%8E%A7%E5%88%B6/Buck_Parallel.slx) | R2023b | 并联 Buck / Parallel Buck converters |
| [LLC_Frequency_Control.slx](01_DC-DC/LLC/LLC_Frequency_Control.slx) | R2022b | LLC 频率控制 / LLC frequency control |
| [LLC_Frequency_Control_Legacy.slx](01_DC-DC/LLC/LLC_Frequency_Control_Legacy.slx) | R2021a | LLC 频率控制模型 / LLC frequency-control model |
| [LLC_Phase_Shift.slx](01_DC-DC/LLC/%E7%A7%BB%E7%9B%B8%E8%B0%83%E5%88%B6/LLC_Phase_Shift.slx) | R2023a | LLC 移相调制 / LLC phase-shift modulation |
| [LLC_Phase_Shift_R2016a.slx](01_DC-DC/LLC/%E7%A7%BB%E7%9B%B8%E8%B0%83%E5%88%B6/LLC_Phase_Shift_R2016a.slx) | R2016a | LLC 移相调制模型 / LLC phase-shift model |
| [Three_Phase_Coupled_Isolated_DCDC.slx](01_DC-DC/%E4%B8%89%E7%9B%B8%E8%80%A6%E5%90%88%E9%9A%94%E7%A6%BB/Three_Phase_Coupled_Isolated_DCDC.slx) | R2023b | 三相耦合隔离 DC-DC / Three-phase coupled isolated DC-DC |
| [Interleaved_3_Level_Boost.slx](01_DC-DC/%E4%BA%A4%E9%94%99%E4%B8%89%E7%94%B5%E5%B9%B3Boost/Interleaved_3_Level_Boost.slx) | R2023b | 交错三电平 Boost / Interleaved three-level boost |
| [Series_Resonant_DAB.slx](01_DC-DC/%E8%B0%90%E6%8C%AF%E5%8F%8C%E6%9C%89%E6%BA%90%E6%A1%A5/Series_Resonant_DAB.slx) | R2023b | 串联谐振双有源桥 / Series-resonant dual active bridge |
| [Supercapacitor_DCDC.slx](01_DC-DC/%E8%B6%85%E7%BA%A7%E7%94%B5%E5%AE%B9/Supercapacitor_DCDC.slx) | R2021b | 超级电容系统 / Supercapacitor system |
| [Inverting_Buck_Boost_FC_3_Level.slx](01_DC-DC/%E9%A3%9E%E8%B7%A8%E7%94%B5%E5%AE%B9Buck-Boost/Inverting_Buck_Boost_FC_3_Level.slx) | R2023b | 飞跨电容三电平反相 Buck-Boost / Flying-capacitor three-level inverting buck-boost |

### 02_AC-DC

| 模型 / Model | 保存版本 / Release | 说明 / Description |
| --- | --- | --- |
| [MMC_21_Level_Rectifier.slx](02_AC-DC/MMC/MMC_21_Level_Rectifier.slx) | R2023b | 21 电平 MMC 整流器 / 21-level MMC rectifier |
| [MMC_Rectifier_NLM_2018.mdl](02_AC-DC/MMC/MMC_Rectifier_NLM_2018.mdl) | R2023b | MMC 最近电平调制整流器 / MMC rectifier with nearest-level modulation |
| [PFC_AFB.slx](02_AC-DC/PFC/PFC_AFB.slx) | R2023b | AFB PFC 仿真 / AFB PFC model |
| [PFC_DSFB.slx](02_AC-DC/PFC/PFC_DSFB.slx) | R2023b | DSFB PFC 仿真 / DSFB PFC model |
| [PFC_Full_Bridge_IGBT_PR.slx](02_AC-DC/PFC/PFC_Full_Bridge_IGBT_PR.slx) | R2021a | IGBT 全桥 PFC 与 PR 控制 / IGBT full-bridge PFC with PR control |
| [Full_Bridge_Rectifier_QPR.slx](02_AC-DC/PFC/Full_Bridge_Rectifier_QPR.slx) | R2021a | 全桥整流与 QPR 控制 / Full-bridge rectifier with QPR control |
| [PFC_Full_Bridge_Unipolar_SPWM_PR.slx](02_AC-DC/PFC/PFC_Full_Bridge_Unipolar_SPWM_PR.slx) | R2023b | PFC 仿真 / PFC model |
| [PFC_Unipolar_Double_Frequency_PR.slx](02_AC-DC/PFC/PFC_Unipolar_Double_Frequency_PR.slx) | R2023b | PFC 仿真 / PFC model |
| [Dual_PWM_Rectifier.slx](02_AC-DC/PWM%E6%95%B4%E6%B5%81/Dual_PWM_Rectifier.slx) | R2021b | 双 PWM 整流 / Dual PWM rectifier |
| [PWM_Rectifier_PQ_Control.slx](02_AC-DC/PWM%E6%95%B4%E6%B5%81/PWM_Rectifier_PQ_Control.slx) | R2021b | PWM 整流与 PQ 控制 / PWM rectifier with PQ control |
| [Single_Phase_PWM_Rectifier.slx](02_AC-DC/PWM%E6%95%B4%E6%B5%81/Single_Phase_PWM_Rectifier.slx) | R2021b | 单相 PWM 整流 / Single-phase PWM rectifier |
| [PWM_Rectifier_30V.slx](02_AC-DC/PWM%E6%95%B4%E6%B5%81/PWM_Rectifier_30V.slx) | R2021b | PWM 整流 / PWM rectifier |
| [Three_Phase_Rectifier_PR.slx](02_AC-DC/PWM%E6%95%B4%E6%B5%81/Three_Phase_Rectifier_PR.slx) | R2021b | 三相整流 / Three-phase rectifier |
| [Vienna_ANPC_Rectifier_DPWMA.slx](02_AC-DC/Vienna%E4%B8%8ENPC/Vienna_ANPC_Rectifier_DPWMA.slx) | R2023b | ANPC Vienna 整流与 DPWM-A / ANPC Vienna rectifier with DPWM-A |
| [Dual_Vienna_Rectifier.slx](02_AC-DC/Vienna%E4%B8%8ENPC/Dual_Vienna_Rectifier.slx) | R2021b | 双 Vienna 整流 / Dual Vienna rectifier |
| [Single_Phase_FCNPC_Rectifier.slx](02_AC-DC/Vienna%E4%B8%8ENPC/Single_Phase_FCNPC_Rectifier.slx) | R2023b | 单相飞跨电容 NPC 整流 / Single-phase flying-capacitor NPC rectifier |
| [Single_Phase_Half_3_Level_FCNPC_Rectifier.slx](02_AC-DC/Vienna%E4%B8%8ENPC/Single_Phase_Half_3_Level_FCNPC_Rectifier.slx) | R2023b | 单相飞跨电容 NPC 整流 / Single-phase flying-capacitor NPC rectifier |
| [Three_Phase_FCNPC_Rectifier.slx](02_AC-DC/Vienna%E4%B8%8ENPC/Three_Phase_FCNPC_Rectifier.slx) | R2023b | 三相飞跨电容 NPC 整流 / Three-phase flying-capacitor NPC rectifier |
| [Vienna_INPC_Rectifier_DPWMA.slx](02_AC-DC/Vienna%E4%B8%8ENPC/Vienna_INPC_Rectifier_DPWMA.slx) | R2023b | INPC Vienna 整流与 DPWM-A / INPC Vienna rectifier with DPWM-A |
| [Vienna_Rectifier_PQ_Control.slx](02_AC-DC/Vienna%E4%B8%8ENPC/Vienna_Rectifier_PQ_Control.slx) | R2023b | Vienna 整流与 PQ 控制 / Vienna rectifier with PQ control |
| [Single_Phase_Vienna_Rectifier_DPWM.slx](02_AC-DC/Vienna%E4%B8%8ENPC/Single_Phase_Vienna_Rectifier_DPWM.slx) | R2021b | Vienna 整流 / Vienna rectifier |
| [Single_Phase_Vienna_Rectifier.slx](02_AC-DC/Vienna%E4%B8%8ENPC/Single_Phase_Vienna_Rectifier.slx) | R2021b | 单相 Vienna 整流 / Single-phase Vienna rectifier |
| [Vienna_Rectifier_DPWMA.slx](02_AC-DC/Vienna%E4%B8%8ENPC/Vienna_Rectifier_DPWMA.slx) | R2023b | Vienna 整流与 DPWM-A / Vienna rectifier with DPWM-A |
| [Thyristor_Rectifier.slx](02_AC-DC/%E6%99%B6%E9%97%B8%E7%AE%A1%E6%95%B4%E6%B5%81/Thyristor_Rectifier.slx) | R2021a | 晶闸管整流 / Thyristor rectifier |
| [Current_Source_Rectifier_DPWMA.slx](02_AC-DC/%E7%94%B5%E6%B5%81%E6%BA%90%E6%95%B4%E6%B5%81/Current_Source_Rectifier_DPWMA.slx) | R2023b | 电流源整流 / Current-source rectifier |
| [Current_Source_Rectifier_SVPWM.slx](02_AC-DC/%E7%94%B5%E6%B5%81%E6%BA%90%E6%95%B4%E6%B5%81/Current_Source_Rectifier_SVPWM.slx) | R2021b | 电流源整流 / Current-source rectifier |
| [Current_Source_Rectifier_DPWM.slx](02_AC-DC/%E7%94%B5%E6%B5%81%E6%BA%90%E6%95%B4%E6%B5%81/Current_Source_Rectifier_DPWM.slx) | R2023b | 电流源整流 / Current-source rectifier |
| [CHB_Rectifier.slx](02_AC-DC/%E7%BA%A7%E8%81%94%E6%95%B4%E6%B5%81%E4%B8%8E%E9%9A%94%E7%A6%BB%E8%BE%93%E5%87%BA/CHB_Rectifier.slx) | R2023b | 级联 H 桥整流 / Cascaded H-bridge rectifier |
| [CHB_Rectifier_LLC_Isolation.slx](02_AC-DC/%E7%BA%A7%E8%81%94%E6%95%B4%E6%B5%81%E4%B8%8E%E9%9A%94%E7%A6%BB%E8%BE%93%E5%87%BA/CHB_Rectifier_LLC_Isolation.slx) | R2023b | 级联 H 桥整流与 LLC 隔离级 / CHB rectifier with LLC isolation |
| [DPWMA_17_Level_Rectifier_Dual_PI.slx](02_AC-DC/%E7%BA%A7%E8%81%94%E6%95%B4%E6%B5%81%E4%B8%8E%E9%9A%94%E7%A6%BB%E8%BE%93%E5%87%BA/DPWMA_17_Level_Rectifier_Dual_PI.slx) | R2021b | 17 电平整流与双 PI 控制 / 17-level rectifier with dual PI control |
| [DPWMA_17_Level_Rectifier_Digital_PR.slx](02_AC-DC/%E7%BA%A7%E8%81%94%E6%95%B4%E6%B5%81%E4%B8%8E%E9%9A%94%E7%A6%BB%E8%BE%93%E5%87%BA/DPWMA_17_Level_Rectifier_Digital_PR.slx) | R2023b | 17 电平整流与数字 PR 控制 / 17-level rectifier with digital PR control |
| [Cascaded_Rectifier_Isolated_Output.slx](02_AC-DC/%E7%BA%A7%E8%81%94%E6%95%B4%E6%B5%81%E4%B8%8E%E9%9A%94%E7%A6%BB%E8%BE%93%E5%87%BA/Cascaded_Rectifier_Isolated_Output.slx) | R2021b | 整流与隔离输出 / Rectifier with isolated output |
| [Single_Phase_CHB_Rectifier_Digital_PR.slx](02_AC-DC/PWM%E6%95%B4%E6%B5%81/Single_Phase_CHB_Rectifier_Digital_PR.slx) | R2023b | 单相级联 H 桥整流，数字 PR 控制 / Single-phase cascaded H-bridge rectifier with digital PR control |

### 03_DC-AC

| 模型 / Model | 保存版本 / Release | 说明 / Description |
| --- | --- | --- |
| [Dual_Three_Leg_Inverter_DPWMA.slx](03_DC-AC/%E4%B8%89%E7%9B%B8%E4%B8%8E%E5%A4%9A%E6%A1%A5%E8%87%82/Dual_Three_Leg_Inverter_DPWMA.slx) | R2023b | 双三桥臂逆变与 DPWM / Dual three-leg inverter with DPWM |
| [DTNPC_Inverter.slx](03_DC-AC/%E4%B8%89%E7%9B%B8%E4%B8%8E%E5%A4%9A%E6%A1%A5%E8%87%82/DTNPC_Inverter.slx) | R2023b | DTNPC 逆变 / DTNPC inverter |
| [Three_Phase_Four_Leg_Inverter.slx](03_DC-AC/%E4%B8%89%E7%9B%B8%E4%B8%8E%E5%A4%9A%E6%A1%A5%E8%87%82/Three_Phase_Four_Leg_Inverter.slx) | R2023b | 三相四桥臂逆变 / Three-phase four-leg inverter |
| [Three_Phase_Two_Level_Inverter.slx](03_DC-AC/%E4%B8%89%E7%9B%B8%E4%B8%8E%E5%A4%9A%E6%A1%A5%E8%87%82/Three_Phase_Two_Level_Inverter.slx) | R2021a | 三相两电平逆变 / Three-phase two-level inverter |
| [Three_Phase_Four_Leg_TNPC_Inverter.slx](03_DC-AC/%E4%B8%89%E7%9B%B8%E4%B8%8E%E5%A4%9A%E6%A1%A5%E8%87%82/Three_Phase_Four_Leg_TNPC_Inverter.slx) | R2023b | 三相四桥臂 T-NPC 逆变 / Three-phase four-leg T-NPC inverter |
| [Single_Phase_HERIC_Inverter.slx](03_DC-AC/%E5%8D%95%E7%9B%B8%E9%80%86%E5%8F%98/Single_Phase_HERIC_Inverter.slx) | R2023b | 单相 HERIC 逆变 / Single-phase HERIC inverter |
| [Single_Phase_Vienna_Inverter.slx](03_DC-AC/%E5%8D%95%E7%9B%B8%E9%80%86%E5%8F%98/Single_Phase_Vienna_Inverter.slx) | R2023b | 单相 Vienna 逆变 / Single-phase Vienna inverter |
| [Single_Phase_Inverter.slx](03_DC-AC/%E5%8D%95%E7%9B%B8%E9%80%86%E5%8F%98/Single_Phase_Inverter.slx) | R2021a | 单相逆变实验 / Single-phase inverter experiment |
| [FCNPC_3_Level_Resonant_Drive_NLM.slx](03_DC-AC/%E8%B0%90%E6%8C%AF%E9%A9%B1%E5%8A%A8/FCNPC_3_Level_Resonant_Drive_NLM.slx) | R2023b | 三电平 FCNPC LC 谐振驱动 / Three-level FCNPC LC resonant drive |

### 04_AC-DC-AC

| 模型 / Model | 保存版本 / Release | 说明 / Description |
| --- | --- | --- |
| [Single_Phase_ACDCAC.slx](04_AC-DC-AC/Single_Phase_ACDCAC.slx) | R2023b | 完整交直交变换链 / Complete AC-DC-AC conversion chain |

### 05_UPS

| 模型 / Model | 保存版本 / Release | 说明 / Description |
| --- | --- | --- |
| [UPS_Vienna_TNPC.slx](05_UPS/UPS_Vienna_TNPC.slx) | R2023b | UPS 系统 / UPS system |
| [UPS_CRM_PFC.slx](05_UPS/UPS_CRM_PFC.slx) | R2023b | UPS 系统 / UPS system |

### 06_电网控制

| 模型 / Model | 保存版本 / Release | 说明 / Description |
| --- | --- | --- |
| [Parallel_Inverter_Droop_Nom.slx](06_%E7%94%B5%E7%BD%91%E6%8E%A7%E5%88%B6/Droop/Parallel_Inverter_Droop_Nom.slx) | R2021a | 交流下垂控制 / AC droop control |
| [Parallel_Inverter_Droop.slx](06_%E7%94%B5%E7%BD%91%E6%8E%A7%E5%88%B6/Droop/Parallel_Inverter_Droop.slx) | R2021a | 交流下垂控制 / AC droop control |
| [Parallel_Inverter_VSG.slx](06_%E7%94%B5%E7%BD%91%E6%8E%A7%E5%88%B6/VSG/Parallel_Inverter_VSG.slx) | R2021b | 并联逆变器虚拟同步发电机 / Parallel-inverter virtual synchronous generator |
| [Virtual_Synchronous_Generator.slx](06_%E7%94%B5%E7%BD%91%E6%8E%A7%E5%88%B6/VSG/Virtual_Synchronous_Generator.slx) | R2023b | 虚拟同步发电机 / Virtual synchronous generator |

### 07_电机驱动

| 模型 / Model | 保存版本 / Release | 说明 / Description |
| --- | --- | --- |
| [PMSM_FOC.slx](07_%E7%94%B5%E6%9C%BA%E9%A9%B1%E5%8A%A8/PMSM/PMSM_FOC.slx) | R2024b | 永磁同步电机磁场定向控制 / PMSM field-oriented control |
| [Single_Phase_Induction_Motor_DPWM.slx](07_%E7%94%B5%E6%9C%BA%E9%A9%B1%E5%8A%A8/%E5%BC%82%E6%AD%A5%E7%94%B5%E6%9C%BA/Single_Phase_Induction_Motor_DPWM.slx) | R2023b | 单相异步电机和两相三桥臂 DPWM / Single-phase induction motor and two-phase three-leg DPWM |

### 08_电能质量与负载

| 模型 / Model | 保存版本 / Release | 说明 / Description |
| --- | --- | --- |
| [Active_Power_Filter.slx](08_%E7%94%B5%E8%83%BD%E8%B4%A8%E9%87%8F%E4%B8%8E%E8%B4%9F%E8%BD%BD/APF/Active_Power_Filter.slx) | R2023b | 有源电力滤波器 / Active power filter |
| [AC_Electronic_Load.slx](08_%E7%94%B5%E8%83%BD%E8%B4%A8%E9%87%8F%E4%B8%8E%E8%B4%9F%E8%BD%BD/%E4%BA%A4%E6%B5%81%E7%94%B5%E5%AD%90%E8%B4%9F%E8%BD%BD/AC_Electronic_Load.slx) | R2023b | 交流电子负载 / AC electronic load |

### 09_控制与信号处理

| 模型 / Model | 保存版本 / Release | 说明 / Description |
| --- | --- | --- |
| [DPWM_Modulation_Examples.slx](09_%E6%8E%A7%E5%88%B6%E4%B8%8E%E4%BF%A1%E5%8F%B7%E5%A4%84%E7%90%86/DPWM/DPWM_Modulation_Examples.slx) | R2024b | 独立 DPWM 调制 / Standalone DPWM modulation |
| [Backstepping_SFunction.slx](09_%E6%8E%A7%E5%88%B6%E4%B8%8E%E4%BF%A1%E5%8F%B7%E5%A4%84%E7%90%86/%E5%8F%8D%E6%AD%A5%E6%8E%A7%E5%88%B6S%E5%87%BD%E6%95%B0/Backstepping_SFunction.slx) | R2021a | 不完整的非线性 S-Function 实验 / Incomplete nonlinear S-Function experiment |

### 11_并网交直流接口

| 模型 / Model | 保存版本 / Release | 说明 / Description |
| --- | --- | --- |
| [Current_Source_Grid_Interface.slx](11_%E5%B9%B6%E7%BD%91%E4%BA%A4%E7%9B%B4%E6%B5%81%E6%8E%A5%E5%8F%A3/Current_Source_Grid_Interface.slx) | R2023b | 电流型并网接口，功率方向待核验 / Current-source grid interface; power direction unverified |
| [Three_Phase_TNPC_Grid_Interface.slx](11_%E5%B9%B6%E7%BD%91%E4%BA%A4%E7%9B%B4%E6%B5%81%E6%8E%A5%E5%8F%A3/Three_Phase_TNPC_Grid_Interface.slx) | R2023b | T-NPC 并网接口，功率方向待核验 / T-NPC grid interface; power direction unverified |

## 配套脚本与原理图 / Scripts and Schematic

| 用途 / Use | 文件 / Files |
| --- | --- |
| Buck 控制与电感铜损 / Buck control and inductor DCR loss | [PI 整定](01_DC-DC/Buck电流控制/Interleaved_Buck_PI_Tuning.m) · [铜损对比](01_DC-DC/Buck电流控制/Inductor_DCR_Loss_Comparison.m) · [铜损曲面](01_DC-DC/Buck电流控制/Inductor_DCR_Loss_Surface.m) |
| CRM PFC 磁性元件设计 / CRM PFC magnetics design | [MATLAB 脚本](02_AC-DC/PFC/CRM_PFC_Magnetics_Design.m) |
| 交流负载电流环分析 / AC load current-loop analysis | [MATLAB 脚本](08_电能质量与负载/交流电子负载/AC_Load_Current_Loop_Analysis.m) |
| Buck 等效电路及采样数据建模 / Buck equivalent-circuit and sampled-data models | [等效电路](10_建模与计算/Buck_Equivalent_Circuit_Model.mlx) · [采样数据模型](10_建模与计算/Buck_Sampled_Data_Model_Dragan.mlx) · [同脚本的另一份输出](10_建模与计算/Buck_Sampled_Data_Model_Variant.mlx) |
| LLC 移相调制 / LLC phase-shift modulation | [PSIM 原理图](01_DC-DC/LLC/移相调制/LLC_Phase_Shift.psimsch) |

## 分类参考 / References

- [MathWorks: Power electronic converter selection](https://www.mathworks.com/help/simscape-electrical/ug/choose-power-electronic-converter-block.html)
- [TI: ANPC power stage for both inverters and PFCs](https://www.ti.com/tool/TIDA-010210)
- [Plexim: Converter and application examples](https://www.plexim.com/support/examples)
- [MathWorks: PWM reference generator, including DPWM](https://www.mathworks.com/help/mcb/ref/pwmreferencegenerator.html)
