# 开关电源

#### 介绍
开关电源基本拓扑的软硬件及simulink仿真
-----持续更新ing

#### 软件架构
软件架构说明


#### 导入教程

*  硬件PCB直接导入嘉立创专业版即可
*  软件采用Keil编写（主控使用STM32F334）

#### 使用说明

1. >Hardware
>>* 控制板
>>>采用STM32F334，含有HRTIM。
>>* 双向DCDC
>>>正向BUCK，反向BOOST。注意辅助电源方向选择电阻，焊接哪个电阻（另一个电阻去掉），即选择哪个方向
>>* 双向三相电
>>>正向三相DCAC，反向三相ACDC。方向电阻同DCDC，注意选用ACDC时辅助电源多一个三相整流桥。采取相电压，可当单相使用。
2.  >Sofeware
>>* DCDC
>>>1. BUCK
>>>2. BOOST
>>* DCAC
>>>单相
>>* ACDC
>>>单相

#### 参与贡献

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request


#### 特技

1.  使用 Readme\_XXX.md 来支持不同的语言，例如 Readme\_en.md, Readme\_zh.md
2.  Gitee 官方博客 [blog.gitee.com](https://blog.gitee.com)
3.  你可以 [https://gitee.com/explore](https://gitee.com/explore) 这个地址来了解 Gitee 上的优秀开源项目
4.  [GVP](https://gitee.com/gvp) 全称是 Gitee 最有价值开源项目，是综合评定出的优秀开源项目
5.  Gitee 官方提供的使用手册 [https://gitee.com/help](https://gitee.com/help)
6.  Gitee 封面人物是一档用来展示 Gitee 会员风采的栏目 [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)
