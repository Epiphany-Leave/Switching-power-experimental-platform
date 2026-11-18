/*
 * CAN.c
 *
 *  Created on: 2025年3月5日
 *      Author: 
 */
#include "H_CAN.h"
#include "H_CAN_Deal.h"

#define CAN_ADD 0x80//模块地址
#define BROADCAST 0xFF//广播地址
#define MONITOR_ADD  0xA0//上位机地址

#define Protocol 1
#define SystemType 0x02
#define DestinationAddress 0xEF
#define SourceAddress 0xF0
#define SerialNumberLowPart 0x00

long CAN_Data0_L;
long CAN_Data0_H;
long CAN_Data1_L;
long CAN_Data1_H;
long CAN_Data2_L;
long CAN_Data2_H;
long CAN_ID0;
long CAN_ID1;
long CAN_ID2;
__interrupt void CAN_ISR(void);



/*==============================================================================
函数名称：Can_Init(void)
函数功能：CAN初始化
输入参数：
输出参数：
返 回 值：
其它说明：
==============================================================================*/
void Can_Init(uint32_t clockFreq, uint32_t bitRate,
              uint16_t bitTime){
    uint16_t brp;
    uint16_t tPhase;
    uint16_t phaseSeg2;
    uint16_t tSync = 1U;
    uint16_t tProp = 2U;
    uint16_t tSeg1;
    uint16_t tSeg2;
    uint16_t sjw;
    uint16_t prescaler;
    uint32_t prescalerExtension;

    uint32_t bitReg;

    uint16_t i = 0;

//    EALLOW;
//    GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;    // Enable pull-up for GPIO28 (SCIRXDA)
//    GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;    // Enable pull-up for GPIO29 (SCITXDA)
//    GpioCtrlRegs.GPAQSEL1.bit.GPIO12 = 3;  // Asynch input GPIO28 (SCIRXDA)
//    GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 13;   // Configure GPIO28 for SCIRXDA operation
//    GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 13;   // Configure GPIO29 for SCITXDA operation
//
//    EDIS;
    EALLOW;
    GPIO_SetupPinMux(12, GPIO_MUX_CPU1, 13);  // GPIO28 = SCIRXDA
    GPIO_SetupPinMux(13, GPIO_MUX_CPU1, 13);  // GPIO29 = SCITXDA

    // 配置输入限定（可选）
    GPIO_SetupPinOptions(12, GPIO_INPUT, GPIO_ASYNC); // 异步输入
    GPIO_SetupPinOptions(13, GPIO_OUTPUT, GPIO_PUSHPULL); // 推挽输出
    EDIS;


//    GPIO_SetupPinMux(13, GPIO_MUX_CPU1, 13);
//    GPIO_SetupPinMux(12, GPIO_MUX_CPU1, 13);
    CanaRegs.CAN_CTL.bit.Init = 0x01;   //can模块忽略总线活动
    CanaRegs.CAN_CTL.bit.PMD = 0x0101;  //关闭奇偶校验
    CanaRegs.CAN_RAM_INIT.all = 0x1A;//启动CAN邮箱内存初始化
    while(!((CanaRegs.CAN_RAM_INIT.all & 0x03F) == 0x025)){}
    // 强制模块重置状态
    CanaRegs.CAN_CTL.bit.SWR = 0x01;

//    SysCtl_delay(1U);
    DELAY_US(1);
    // 允许对配置寄存器进行写入操作
    CanaRegs.CAN_CTL.bit.CCE = 0x01;

    //
    // Calculate bit timing values
    //
    brp = (uint16_t)(clockFreq / (bitRate * bitTime));
    tPhase = bitTime - (tSync + tProp);
    if((tPhase / 2U) <= 8U)
    {
        phaseSeg2 = tPhase / 2U;
    }
    else
    {
        phaseSeg2 = 8U;
    }
    tSeg1 = ((tPhase - phaseSeg2) + tProp) - 1U;
    tSeg2 = phaseSeg2 - 1U;
    if(phaseSeg2 > 4U)
    {
        sjw = 3U;
    }
    else
    {
        sjw = tSeg2;
    }
    prescalerExtension = ((brp - 1U) / 64U);
    prescaler = ((brp - 1U) % 64U);


    // 要设置位定时寄存器，控制器必须先置于初始化模式（如果尚未处于该模式，则需先将其切换至该模式），并且还需启用配置更改位。初始化位的状态应予以保存，以便在结束时能够恢复
    CanaRegs.CAN_CTL.bit.CCE = 0x01;
    CanaRegs.CAN_CTL.bit.Init = 0x01;


    bitReg = prescaler&0x3F;
    bitReg |= (sjw<<6)&0xC0;
    bitReg |= (tSeg1<<8)&0x0F00;
    bitReg |= (tSeg2<<12)&0x07000;
    bitReg |= (prescalerExtension<<16)&0x0F0000;
    //CanaRegs.CAN_BTR.all = bitReg;

    CanaRegs.CAN_BTR.bit.BRP = 39;
    CanaRegs.CAN_BTR.bit.BRPE = 0;
    CanaRegs.CAN_BTR.bit.TSEG1 = 15;
    CanaRegs.CAN_BTR.bit.TSEG2 = 2;
    CanaRegs.CAN_BTR.bit.SJW = 1;

//    CanaRegs.CAN_CTL.bit.CCE = 0x00;
    // 启用CAN外围设备的中断功能。
    CanaRegs.CAN_CTL.bit.EIE = 0x00;
    CanaRegs.CAN_CTL.bit.IE0 = 0x01;//
    CanaRegs.CAN_CTL.bit.IE1 = 0x00;//
    CanaRegs.CAN_CTL.bit.SIE = 0x01;
    CanaRegs.CAN_CTL.bit.DAR = 1;


    CanaRegs.CAN_GLB_INT_EN.bit.GLBINT0_EN = 0x01; // CANINTO的中断使能//
    CanaRegs.CAN_GLB_INT_EN.bit.GLBINT1_EN = 0x00; // CANINTO的中断失能//
    // 禁用带有外部环回功能的CAN测试模式
    CanaRegs.CAN_CTL.bit.Test = 0;
    CanaRegs.CAN_TEST.bit.SILENT = 0;
    CanaRegs.CAN_TEST.bit.LBACK = 0;
    CanaRegs.CAN_TEST.bit.EXL = 0;
    // 初始化用于发送 CAN 消息的发送消息对象。
    // 等待忙状态位清零


    for(i=1;i<=32;i++){
        while(CanaRegs.CAN_IF1CMD.bit.Busy == 1){}
//        CanaRegs.CAN_IF1ARB.all = 0xE0000080;
        CanaRegs.CAN_IF1MCTL.all = 0x00000088;
        CanaRegs.CAN_IF1CMD.all = 0x00900000|i;
    }


    // 将消息方向设置为“发送”
    while(CanaRegs.CAN_IF1CMD.bit.Busy == 1){}
    /*
     * 邮箱 1 发送邮箱
     * ID = 0x80
     * leng = 8
     * 禁用中断
     *
    */
    CanaRegs.CAN_IF1MSK.all = 0;
//    CanaRegs.CAN_IF1MSK.bit.MDir = 0;
//    CanaRegs.CAN_IF1MSK.bit.MXtd = 0;
    CanaRegs.CAN_IF1ARB.all = 0xE0000080;
//    CanaRegs.CAN_IF1ARB.bit.Dir = 1;
//    CanaRegs.CAN_IF1ARB.bit.Xtd = 1;
//    CanaRegs.CAN_IF1ARB.bit.MsgVal = 1;
//    CanaRegs.CAN_IF1ARB.bit.ID = 0x80;
    CanaRegs.CAN_IF1MCTL.all = 0x00000088;
//    CanaRegs.CAN_IF1MCTL.bit.DLC = 8;
//    CanaRegs.CAN_IF1MCTL.bit.EoB = 1;
//    CanaRegs.CAN_IF1MCTL.bit.TxIE = 0;
//    CanaRegs.CAN_IF1MCTL.bit.RxIE = 0;
    CanaRegs.CAN_IF1CMD.all = 0x00F00001;
//    CanaRegs.CAN_IF1CMD.bit.Control = 1;
//    CanaRegs.CAN_IF1CMD.bit.Arb = 1;
//    CanaRegs.CAN_IF1CMD.bit.Mask = 1;
//    CanaRegs.CAN_IF1CMD.bit.DIR = 1;
//    CanaRegs.CAN_IF1CMD.bit.MSG_NUM = 1;

    // 将消息方向设置为“接受”
    while(CanaRegs.CAN_IF1CMD.bit.Busy == 1){}
    /*
     * 邮箱 2
     * ID = 0x8803C00 邮箱2为接收
     * leng = 8
     * 启用中断
     *
    */
//    CanaRegs.CAN_IF1MSK.all = 0xC0003FFF;
    CanaRegs.CAN_IF1MSK.all = 0xC0000000;
    CanaRegs.CAN_IF1ARB.all = 0xC8803C00;
    CanaRegs.CAN_IF1MCTL.all = 0x00001488;
    CanaRegs.CAN_IF1CMD.all = 0x00F00002;     //

    // 启动 CAN 模块操作
    CanaRegs.CAN_CTL.bit.Init = 0;
    CanaRegs.CAN_CTL.bit.CCE = 0;

    EALLOW;
    PieVectTable.CANA0_INT = &CAN_ISR;
    PieCtrlRegs.PIEIER9.bit.INTx5 = 1; // 映射到PIE组9中断5
    IER |= M_INT9;
    EDIS;

}


uint32_t status;
/*==============================================================================
函数名称：CAN_ISR(void)
函数功能：CAN接收中断
输入参数：
输出参数：
返 回 值：
其它说明：
==============================================================================*/
__interrupt void CAN_ISR(void)
{
    long MessageType = 0;
    unsigned long ID_L=0,ID_H=0,CommandType=0;

    int i=0;


    status = CanaRegs.CAN_INT.all&0x0FFFF;
    if(status == 0x02){
        // 将消息数据 A、数据 B 以及控制值设置为在根据请求从消息对象读取数据时需要读取的值
        CanaRegs.CAN_IF1CMD.all = 0x00338002;
        // 等待忙状态位清零
        for(i=0;i<10;i++){
            if(CanaRegs.CAN_IF1CMD.bit.Busy != 1){
                break;
            }
        }
        // 等待忙状态位清零
        for(i=0;i<10;i++){
            if(CanaRegs.CAN_IF1CMD.bit.Busy != 1){
                break;
            }
        }
        if(CanaRegs.CAN_IF1MCTL.bit.NewDat == 0){
            return;
        }

        CAN_Data1_H = CanaRegs.CAN_IF1DATA.all;
        CAN_Data1_L = CanaRegs.CAN_IF1DATB.all;
        CAN_ID1     = CanaRegs.CAN_IF1ARB.all & 0x1FFFFFFF;

        receive_message.rx_efid    = CAN_ID1;
        receive_message.rx_dlen    = 8;
        receive_message.rx_data[3] = CAN_Data1_H >> 24 & 0xFF;
        receive_message.rx_data[2] = CAN_Data1_H >> 16 & 0xFF;
        receive_message.rx_data[1] = CAN_Data1_H >> 8 & 0xFF;
        receive_message.rx_data[0] = CAN_Data1_H & 0xFF;
        receive_message.rx_data[7] = CAN_Data1_L >> 24 & 0xFF;
        receive_message.rx_data[6] = CAN_Data1_L >> 16 & 0xFF;
        receive_message.rx_data[5] = CAN_Data1_L >> 8 & 0xFF;
        receive_message.rx_data[4] = CAN_Data1_L & 0xFF;

        ID_H = 0;
        ID_H |= receive_message.rx_data[0];
        ID_H = ID_H<<8;
        ID_H |= receive_message.rx_data[1];
        ID_H = ID_H<<8;
        ID_H |= receive_message.rx_data[2];
        ID_H = ID_H<<8;
        ID_H |= receive_message.rx_data[3];

        ID_L = 0;
        ID_L |= receive_message.rx_data[4];
        ID_L = ID_L<<8;
        ID_L |= receive_message.rx_data[5];
        ID_L = ID_L<<8;
        ID_L |= receive_message.rx_data[6];
        ID_L = ID_L<<8;
        ID_L |= receive_message.rx_data[7];

        ID_H = ID_H & 0x0FFFF;

        CommandType = 0;
        CommandType |= receive_message.rx_data[2];
        CommandType = CommandType<<8;
        CommandType |= receive_message.rx_data[3];
        MessageType = receive_message.rx_data[0] & 0x0F;
        if(MessageType == 0 ||
           MessageType == 2 ||
           MessageType == 3 ||
           MessageType == 9 ||
           MessageType == 10){
            Flag_CAN |= 0x01;
        }else{
            Flag_CAN &= 0xFE;
        }
        // 现在清除新的数据标志
//        CanaRegs.CAN_IF2CMD.all = 0x40002;
        CanaRegs.CAN_IF1CMD.all = 0x080002;
    }
    if(CanaRegs.CAN_INT.all == 0x8000){
        status = CanaRegs.CAN_ES.all;
    }


    CanaRegs.CAN_GLB_INT_CLR.bit.INT0_FLG_CLR = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}

/*==============================================================================
函数名称：CanRecord(void)
函数功能：CAN发送
输入参数：
输出参数：
返 回 值：
其它说明：
==============================================================================*/
void CanRecord(void)
{
    unsigned long MailBoxID = 0;
    unsigned long data[8]={0};

    uint32_t msgCtrl = 0U;
    uint16_t TxStatus = 0;
    int i = 0;

    MailBoxID = transmit_message.tx_efid;
    data[0] = transmit_message.tx_data[0];
    data[1] = transmit_message.tx_data[1];
    data[2] = transmit_message.tx_data[2];
    data[3] = transmit_message.tx_data[3];
    data[4] = transmit_message.tx_data[4];
    data[5] = transmit_message.tx_data[5];
    data[6] = transmit_message.tx_data[6];
    data[7] = transmit_message.tx_data[7];


    // 将 IF 命令设置为读取消息对象控制值//
    // 设置从消息对象获取数据的请求。
    // 将消息对象传输至 IF 寄存器。
    CanaRegs.CAN_IF1CMD.all = 0x00100001;
    // 等待忙状态位清零
    for(i=0;i<10;i++){
        if(CanaRegs.CAN_IF1CMD.bit.Busy != 1){
            break;
        }
    }
    msgCtrl = CanaRegs.CAN_IF1MCTL.all;
    TxStatus = msgCtrl &0x100;
    //表明该邮箱没有在发送进程中，可以进行数据发送。
    if(TxStatus == 0){
        // 等待忙状态位清零
        for(i=0;i<10;i++){
            if(CanaRegs.CAN_IF1CMD.bit.Busy != 1){
                CanaRegs.CAN_IF1MSK.all = 0;
                CanaRegs.CAN_IF1ARB.all = 0xE0000000|MailBoxID;
                CanaRegs.CAN_IF1MCTL.all = 0x00000088;
                CanaRegs.CAN_IF1CMD.all = 0x00F00001;
                break;
            }
        }
        CanaRegs.CAN_IF1DATA.all = (data[3]<<24) | (data[2]<<16) | (data[1]<<8) | data[0];
        CanaRegs.CAN_IF1DATB.all = (data[7]<<24) | (data[6]<<16) | (data[5]<<8) | data[4];
        // 将消息对象传输至由ID指定的指定消息对象中
        CanaRegs.CAN_IF1CMD.all = 0x00870001;
        for(i=0;i<10;i++){
            if(CanaRegs.CAN_IF1CMD.bit.Busy != 1){
                CanaRegs.CAN_IF1CMD.all = 0x00800001;
                break;
            }
        }
    }
}

