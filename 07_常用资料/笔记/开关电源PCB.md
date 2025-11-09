# BUCK开关电源PCB

<img src="C:\Users\45276\Documents\Tencent Files\452760553\nt_qq\nt_data\Pic\2024-01\Ori\635a068a9abf81a24a8ee537ed88b5a7.jpeg" alt="635a068a9abf81a24a8ee537ed88b5a7" style="zoom:200%;" />

- SW脚到电感的面积不要太大（有多余）
- 电感两边的填充时，不要离的太近

### 电容取值：

| 频率范围(Hz) | 电容取值                               |
| ------------ | -------------------------------------- |
| DC~100K      | 10uF以上的钽电容或铝电解               |
| 100K~10M     | 100nF的MLCC                            |
| 10M~100M     | 10nF的MLCC                             |
| 100M以上     | 1nF的MLCC，并且PCBGND与电源GND的铝电解 |

**误差，耐压，温度系数，ESR，纹波系数**