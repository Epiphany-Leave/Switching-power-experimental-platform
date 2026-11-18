# Buck 开关电源 PCB

- 电感尽量靠近 SW 引脚，缩小 SW 节点铜皮面积。
- 电感两端是不同的网络，铺铜时保留所需间距。

典型布局见 [TI《Reduced Size, Double Sided Layout for High-Current DC/DC Converters》](https://www.ti.com/lit/an/slva963/slva963.pdf)。

## 去耦电容取值

下表是原笔记中的参考值。选型时也要看电容的误差、耐压、温度特性、ESR 和允许纹波电流。

| 频率范围 | 参考取值 |
| --- | --- |
| DC–100 kHz | 10 µF 以上的钽电容或铝电解电容 |
| 100 kHz–10 MHz | 100 nF MLCC |
| 10–100 MHz | 10 nF MLCC |
| 100 MHz 以上 | 1 nF MLCC |
