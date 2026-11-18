/*
 * sci.c
 *
 *  Created on: 2025年12月1日
 *      Author: 45276
 */

#include "sci.h"

#define SCI_SUCCESS        0
#define SCI_ERROR_TIMEOUT -1

__interrupt void SCIA_Rx_IRQn();
void SCIA_GPIO_Init(void)
{
//    EALLOW;
//    GpioCtrlRegs.GPAPUD.bit.GPIO28      = 0;
//    GpioCtrlRegs.GPAPUD.bit.GPIO29      = 0;
//    GpioCtrlRegs.GPAQSEL2.bit.GPIO28    = 3;
//    GpioCtrlRegs.GPAMUX2.bit.GPIO28     = 1;
//    GpioCtrlRegs.GPAMUX2.bit.GPIO29     = 1;
//    EDIS;

    GPIO_SetupPinMux(28, GPIO_MUX_CPU1, 1);
    GPIO_SetupPinOptions(28, GPIO_INPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(29, GPIO_MUX_CPU1, 1);
    GPIO_SetupPinOptions(29, GPIO_OUTPUT, GPIO_ASYNC);
}

/*
 * 计算LSPCLK时钟下的SCI波特率相关说明：
 * SCI波特率寄存器为16位，可表示0~64K范围
 * scibaud = (SCIHBAUD << 8) + SCILBAUD
 * SCI波特率 = LSPCLK / ((BRR + 1) * 8)
 * 其中：
 * scibaud = LSPCLK / （SCI波特率 * 8） - 1
 * 要求0 < BRR < 65536
 * 若scibaud = 0，则SCI波特率 = LSPCLK / 16
 * scibaud的最小值为16时，可获得最大波特率
 */
/*
 * 初始化SCI函数
 * 参数：
 * baud：波特率
 * RXFrameLength：数据包长度（不能超过16位）
 * 返回值：
 * 0：成功
 * -1：失败
 */
void SCIA_Init(Uint32 baud, Uint16 RXFrameLength)
{
    /* 计算波特率高位和低位 */
    Uint16 scibaud,scihbaud,scilbaud;
    scibaud  = (Uint16)(25000000/(8*baud)-1);
    scihbaud = scibaud >> 8;
    scilbaud = scibaud & 0xff;

    /* 限制数据帧的长度为16 */
    RXFrameLength = RXFrameLength > 16 ? 16 : RXFrameLength;
    /* 初始化GPIO */
    SCIA_GPIO_Init();
    /* 使能SCI中断 */
    EALLOW;
    PieVectTable.SCIA_RX_INT = &SCIA_Rx_IRQn;
    /* 使能SCI时钟 */
    CpuSysRegs.PCLKCR7.bit.SCI_A = 1;
    EDIS;

    /* CCR通信控制寄存器相关配置 */
    SciaRegs.SCICCR.bit.STOPBITS    = 0;    // 0-同志为，1为：1-同志为
    SciaRegs.SCICCR.bit.PARITYENA   = 0;    // 0-不是你校验
    SciaRegs.SCICCR.bit.LOOPBKENA   = 0;    // 回环测试模式：0-失能
    SciaRegs.SCICCR.bit.SCICHAR     = 7;    // 字符长度控制位：7h（R/W） = SCICHAR_LENGTH_8

    /* CTL1控制寄存器相关配置 */
    SciaRegs.SCICTL1.bit.RXERRINTENA    = 0;    // SCI接收错误中断使能：0-失能
    SciaRegs.SCICTL1.bit.SWRESET        = 1;    // SCI软件复位：1-复位
                                                // 0h（R/W） = 将 0 写入该位可将 SCI 状态机和操作标志（寄存器 SCICTL2 和 SCIRXST）复位到其初始状态
                                                // 1h（R/W） = 系统复位后，想该位写入 1 ，重启 SCI
    SciaRegs.SCICTL1.bit.TXENA          = 1;    // SCI发送使能：1-使能
    SciaRegs.SCICTL1.bit.RXENA          = 1;    // SCI接收使能：1-使能

    /* HBAUD波特率高位寄存器相关配置 */
    SciaRegs.SCIHBAUD.bit.BAUD = scihbaud;    // 波特率高位：0-16进制
    /* LBAUD波特率低位寄存器相关配置 */
    SciaRegs.SCILBAUD.bit.BAUD = scilbaud;    // 波特率低位：0-16进制

    /* CTL2控制寄存器相关配置 */
    SciaRegs.SCICTL2.bit.RXBKINTENA     = 1;    // 使能RXRDY或BRKDT中断。SCIFFENA=1时，
    SciaRegs.SCICTL2.bit.TXINTENA       = 0;    // 禁用TXRDY中断

    /* FIFO相关配置 */
    // TX
    SciaRegs.SCIFFTX.bit.SCIRST         = 1;    // 写入 0 重置 SCI 发送和接收通道。 SCI FIFO 寄存器配置位将保持不变。1-SCI FIFO
    SciaRegs.SCIFFTX.bit.SCIFFENA       = 1;    // SCI FIFO 使能：1-使能FIFO增强功能
    SciaRegs.SCIFFTX.bit.TXFIFORESET    = 1;    // SCI FIFO 发送重置：1-重置
    SciaRegs.SCIFFTX.bit.TXFFINTCLR     = 1;    // SCI FIFO 发送中断清除：1-清除TXFFINT
    SciaRegs.SCIFFTX.bit.TXFFIENA       = 0;    // SCI FIFO 发送中断使能：0-禁用TX FIFO中断
    SciaRegs.SCIFFTX.bit.TXFFIL         = 16;   // SCI FIFO 发送中断级别：TXFFST<=TXFFIL时，会产生中断信号。TXFFIL不能超过FIFO深度16
    // RX
    SciaRegs.SCIFFRX.bit.RXFFOVRCLR     = 1;    // SCI FIFO 接收溢出清除：1-清除（接收FIFO溢出标志位）
    SciaRegs.SCIFFRX.bit.RXFIFORESET    = 1;    // SCI FIFO 接收重置：1-重置
    SciaRegs.SCIFFRX.bit.RXFFINTCLR     = 1;
    SciaRegs.SCIFFRX.bit.RXFFIENA       = 1;
    SciaRegs.SCIFFRX.bit.RXFFIL         = RXFrameLength;
    // 传输时延配置
    SciaRegs.SCIFFCT.bit.FFTXDLY        = 0;    // FIFO传输延为0
    SciaRegs.SCIPRI.bit.FREESOFT        = 2;    // 0h（R/w）= 挂起时立即停止 1h（R/w）= 挂起时等待一个SCI字符时间 2h（R/w）= 自由运行 3h（R/w）= 挂起时立即停止，并启用自动波特率检测

    /* 中断向量表 x1 y9 */
    IER |= M_INT9;
    PieCtrlRegs.PIEIER9.bit.INTx9   = 1;
    PieCtrlRegs.PIEACK.bit.ACK9     = 1;
}

/* 单字节发送函数 */
int SCIA_SendByte(Uint16 data)
{
    // 发送数据
    SciaRegs.SCITXBUF.all = data & 0xFF; // 确保只发送低8位
    return SCI_SUCCESS;
}

/* 字符串发送函数 */
int SCIA_SendString(const char *msg)
{
    int i = 0;
    int status = SCI_SUCCESS;

    while(msg[i] != '\0')
    {
        status = SCIA_SendByte(msg[i]);
        i++;
        if(status != SCI_SUCCESS)
        {
            return status;
        }
    }
    return SCI_SUCCESS;
}

/*
 * 重置SCI函数
 * 作用：当前通信出现问题时调用此函数重置SCI
*/
void SCIA_Reset(void)
{
    // 保存当前中断状态
    Uint16 tempIER = IER;
    Uint16 tempPIEIER = PieCtrlRegs.PIEIER9.all;

    // 禁用中断
    IER &= ~M_INT9;
    PieCtrlRegs.PIEIER9.bit.INTx1 = 0; // 清除中断标志

    // 软件复位SCI
    SciaRegs.SCICTL1.bit.SWRESET = 0; // 软件复位
    DELAY_US(10);                     // 短暂延时

    // 重置FIFO
    SciaRegs.SCIFFTX.bit.TXFIFORESET = 0;
    SciaRegs.SCIFFRX.bit.RXFIFORESET = 0;
    DELAY_US(10);                     // 短暂延时

    // 重新启用FIFO
    SciaRegs.SCIFFTX.bit.TXFIFORESET = 1;
    SciaRegs.SCIFFRX.bit.RXFIFORESET = 1;

    // 清除所有中断标志位
    SciaRegs.SCIFFTX.bit.TXFFINTCLR  = 1;
    SciaRegs.SCIFFRX.bit.RXFFINTCLR  = 1;
    SciaRegs.SCIFFRX.bit.RXFFOVRCLR  = 1;

    // 重新启用SCI
    SciaRegs.SCICTL1.bit.SWRESET = 1;

    // 恢复中断状态
    IER = tempIER;
    PieCtrlRegs.PIEIER9.all = tempPIEIER;
    PieCtrlRegs.PIEACK.bit.ACK9 = 1;
}

char* msg;
Uint16 recvdate;
Uint16 len=0,n;
Uint16 RecvData[100];
__interrupt void SCIA_Rx_IRQn(void)
{
    // 把FIFO中接收到的数据全部读出
    while(SciaRegs.SCIFFRX.bit.RXFFST > 0)
    {
        recvdate = SciaRegs.SCIRXBUF.all;
        RecvData[len] = recvdate;
        len++;
    }

    // 把接收到的数据发送回去
    msg = " You sent: \0";
    SCIA_SendString(msg);
    for(n=0; n<len; n++)
    {
        SCIA_SendByte(RecvData[n]);
    }
    SCIA_SendString("\r\n\0");
    len = 0;

    if(SciaRegs.SCIFFRX.bit.RXFFOVF);   // 判断FIFO是否溢出
    // 清除相关中断标志位
    SciaRegs.SCIFFRX.bit.RXFFOVRCLR = 1;
    SciaRegs.SCIFFRX.bit.RXFFINTCLR = 1;
    PieCtrlRegs.PIEACK.bit.ACK9 = 1;
}

/*
 * 发送单个通道浮点数到VOFA+
 * 参数： data：浮点数
 * 返回值：SCI_SUCCESS-成功 
*/
int SCIA_SendFloatToVOFA(float data)
{
    int *ptr;
    Uint16 txBuffer[4]; // 浮点数的字节缓冲区
    Uint16 i,j;
    unsigned char tail[4] = {0x00, 0x00, 0x80, 0x7F}; // VOFA+帧尾标识

    // 将浮点数指针转换为整形指针，以便按字节访问
    ptr = (int *)&data;

    // 按小端字节序提取浮点数的4个字节
    txBuffer[0] = (*ptr >> 0) & 0xFF;       // 低字节
    txBuffer[1] = (*ptr >> 8) & 0xFF;
    txBuffer[2] = (*(ptr + 1) >> 0) & 0xFF;
    txBuffer[3] = (*(ptr + 1) >> 8) & 0xFF; // 高字节

    // 发送四个字节
    for(j=0; j<4; j++)
    {
        int status = SCIA_SendByte(txBuffer[j]);
        if(status != SCI_SUCCESS)
        {
            return status;  // 发送失败
        }
    }

    // 发送帧尾标识
    for(j=0; j<4; j++)
    {
        int status = SCIA_SendByte(tail[j]);
        if(status != SCI_SUCCESS)
        {
            return status;  // 发送失败
        }
    }

    return SCI_SUCCESS;
}

/*
 * 发送两个通道浮点数到VOFA+
 * 参数： data：浮点数
 * 返回值：SCI_SUCCESS-成功 
*/
int SCIA_SendFloatToVOFA2(float data1, float data2)
{
    int *ptr1, *ptr2;
    Uint16 txBuffer[8]; // 浮点数的字节缓冲区
    Uint16 i,j;
    unsigned char tail[4] = {0x00, 0x00, 0x80, 0x7F}; // VOFA+帧尾标识

    // 将浮点数指针转换为整形指针，以便按字节访问
    ptr1 = (int *)&data1;

    // 按小端字节序提取浮点数的4个字节
    txBuffer[0] = (*ptr1 >> 0) & 0xFF;       // 低字节
    txBuffer[1] = (*ptr1 >> 8) & 0xFF;
    txBuffer[2] = (*(ptr1 + 1) >> 0) & 0xFF;
    txBuffer[3] = (*(ptr1 + 1) >> 8) & 0xFF; // 高字节

    // 将浮点数指针转换为整形指针，以便按字节访问
    ptr2 = (int *)&data1;

    // 按小端字节序提取浮点数的4个字节
    txBuffer[4] = (*ptr2 >> 0) & 0xFF;       // 低字节
    txBuffer[5] = (*ptr2 >> 8) & 0xFF;
    txBuffer[6] = (*(ptr2 + 1) >> 0) & 0xFF;
    txBuffer[7] = (*(ptr2 + 1) >> 8) & 0xFF; // 高字节

    // 发送四个字节
    for(j=0; j<8; j++)
    {
        int status = SCIA_SendByte(txBuffer[j]);
        if(status != SCI_SUCCESS)
        {
            return status;  // 发送失败
        }
    }

    // 发送帧尾标识
    for(j=0; j<4; j++)
    {
        int status = SCIA_SendByte(tail[j]);
        if(status != SCI_SUCCESS)
        {
            return status;  // 发送失败
        }
    }

    return SCI_SUCCESS;
}

/*
 * 发送三个通道浮点数到VOFA+
 * 参数： data：浮点数
 * 返回值：SCI_SUCCESS-成功 
*/
int SCIA_SendFloatToVOFA3(float data1, float data2, float data3)
{
    int *ptr1, *ptr2, *ptr3;
    Uint16 txBuffer[12]; // 浮点数的字节缓冲区
    Uint16 i,j;
    unsigned char tail[4] = {0x00, 0x00, 0x80, 0x7F}; // VOFA+帧尾标识

    // 将浮点数指针转换为整形指针，以便按字节访问
    ptr1 = (int *)&data1;

    // 按小端字节序提取浮点数的4个字节
    txBuffer[0] = (*ptr1 >> 0) & 0xFF;       // 低字节
    txBuffer[1] = (*ptr1 >> 8) & 0xFF;
    txBuffer[2] = (*(ptr1 + 1) >> 0) & 0xFF;
    txBuffer[3] = (*(ptr1 + 1) >> 8) & 0xFF; // 高字节

    // 将浮点数指针转换为整形指针，以便按字节访问
    ptr2 = (int *)&data2;

    // 按小端字节序提取浮点数的4个字节
    txBuffer[4] = (*ptr2 >> 0) & 0xFF;       // 低字节
    txBuffer[5] = (*ptr2 >> 8) & 0xFF;
    txBuffer[6] = (*(ptr2 + 1) >> 0) & 0xFF;
    txBuffer[7] = (*(ptr2 + 1) >> 8) & 0xFF; // 高字节

    // 将浮点数指针转换为整形指针，以便按字节访问
    ptr3 = (int *)&data3;

    // 按小端字节序提取浮点数的4个字节
    txBuffer[8] = (*ptr3 >> 0) & 0xFF;       // 低字节
    txBuffer[9] = (*ptr3 >> 8) & 0xFF;
    txBuffer[10] = (*(ptr3 + 1) >> 0) & 0xFF;
    txBuffer[11] = (*(ptr3 + 1) >> 8) & 0xFF; // 高字节

    // 发送四个字节
    for(j=0; j<12; j++)
    {
        int status = SCIA_SendByte(txBuffer[j]);
        if(status != SCI_SUCCESS)
        {
            return status;  // 发送失败
        }
    }

    // 发送帧尾标识
    for(j=0; j<4; j++)
    {
        int status = SCIA_SendByte(tail[j]);
        if(status != SCI_SUCCESS)
        {
            return status;  // 发送失败
        }
    }

    return SCI_SUCCESS;
}
