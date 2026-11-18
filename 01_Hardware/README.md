# 硬件工程 / Hardware Projects

[中文首页](../README.md) · [English overview](../README.en.md)

使用嘉立创 EDA 专业版导入 `.epro` 或 `.epro2`。这些工程包包含原理图和 PCB 数据。如遇 `.epro2` 导入问题，请核对编辑器版本，C2000 工程的归档记录为 3.2.91。 [官方导入指南](https://prodocs.lceda.cn/cn/import-export/import-lceda-pro/index.html)

Import the archives into EasyEDA Pro to view schematics and PCB layouts. The C2000 archive records editor version 3.2.91.

| 工程 / Project | 内容 / Contents |
| --- | --- |
| [开关电源实验平台](ProProject_开关电源实验平台_2024-07-17.epro) · [原理图压缩包](开关电源实验平台原理图.zip) | 原平台的 STM32F334 控制板、双向 DC-DC 和三相变换电路 / Original STM32F334 platform, bidirectional DC-DC and three-phase conversion |
| [DSP C2000](DSP_C2000.epro2) | 含 F280 系列器件的 C2000 工程，归档含 4 个板卡记录 / C2000 design with F280-series devices and four board records |
| [IPT60R028G7 半桥模块](IPT60R028G7半桥模块.epro) | IPT60R028G7 MOSFET 半桥板 / MOSFET half-bridge board |
| [XDS110 高速隔离版](XDS110_高速隔离版.epro) | XDS110 调试器的隔离设计，器件库含 ISO7731 和 ISO7741 / Isolated XDS110 debug-probe design |
| [差分采样](差分采样.epro) | 差分交流电压、电流采样、电压采样三个子板 / Differential AC voltage, current sensing and voltage sensing |
| [辅助电源](辅助电源.epro) | SY8401、平面变压器氮化镓电源和 LM5164 子板 / SY8401, planar-transformer GaN supply and LM5164 boards |

## 装配与核对 / Assembly notes

原平台的双向 DC-DC 和三相板通过辅助电源方向选择电阻区分方向，选装一侧时需去掉另一侧。三相板用于 AC-DC 时还涉及三相整流桥。板卡装配以原理图和对应 BOM 为准。

On the original bidirectional DC-DC and three-phase boards, fit the auxiliary-supply direction resistor for the intended direction and remove the other. AC-DC operation of the three-phase board also involves a three-phase rectifier bridge. Use the schematic and matching BOM for assembly.

半桥工程里有一条电容库记录的显示名称与制造商料号字段不一致。打板或采购前应按实际原理图位号核对数值及 BOM。

One capacitor entry in the half-bridge library has inconsistent display-name and manufacturer-part fields. Check the schematic reference, value, and BOM before ordering.

## 后续可补充 / Optional additions

原理图 PDF 可供没有安装 EDA 的读者浏览。如已有样机，附上板卡版本、正反面照片和注明工况的测试结果，会更方便复现。

Schematic PDFs help readers without an EDA installation. For built boards, include the revision, front and back photos, and test results with operating conditions.
