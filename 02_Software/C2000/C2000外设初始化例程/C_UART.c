/*
 * UART.c
 *
 *  Created on: 2025年6月4日
 *      Author: chens
 */

#include "H_CAN_Deal.h"
#include "H_UART.h"
#include "H_CRC.h"
#include "H_Uart_Drv.h"

__interrupt void SCI_RXINT(void);
__interrupt void SCI_TXINT(void);

comm7E_Rece_t opComm7ERece = {
    .state = 0,      // 状态类型
    .cnt = 0,        // 计数器
};
Data576 Re576;

/*==============================================================================
函数名称：UART_Init(void)
函数功能：串口初始化
输入参数：
输出参数：
返 回 值：
其它说明：
==============================================================================*/
void UART_Init(void){

    // GPIO28 29初始化
    EALLOW;
    GPIO_SetupPinMux(28, GPIO_MUX_CPU1, 1);  // GPIO28 = SCIRXDA
    GPIO_SetupPinMux(29, GPIO_MUX_CPU1, 1);  // GPIO29 = SCITXDA

    // 配置输入限定（可选）
    GPIO_SetupPinOptions(28, GPIO_INPUT, GPIO_ASYNC); // 异步输入
    GPIO_SetupPinOptions(29, GPIO_OUTPUT, GPIO_PUSHPULL); // 推挽输出
    EDIS;


    // 使能SCI外设时钟
    EALLOW;
    CpuSysRegs.PCLKCR7.bit.SCI_A = 1;
    EDIS;

    // 配置通信格式
    SciaRegs.SCICCR.all = 0x0007;    // 1停止位，无奇偶校验，8位数据，异步模式
    ClkCfgRegs.LOSPCP.bit.LSPCLKDIV = 0x02;
    // 设置波特率（LSPCLK=25MHz，9600波特率）
    // BRR = (LSPCLK/(SCI波特率×8))-1 = (50,000,000/(9600×8))-1 ≈ 650 → 144
    SciaRegs.SCIHBAUD.all = 0x0001;      // 高位波特率寄存器
    SciaRegs.SCILBAUD.all = 0x0044;      // 低位波特率寄存器

    SciaRegs.SCICCR.bit.LOOPBKENA = 0; // 使能回环

    // 配置控制寄存器
    SciaRegs.SCICTL1.all = 0x0003;   // 使能TX和RX，禁用休眠模式
    SciaRegs.SCICTL2.bit.TXINTENA = 1; // 使能发送中断
    SciaRegs.SCICTL2.bit.RXBKINTENA = 1; // 使能接收中断

    // 4. 使能SCI
    SciaRegs.SCICTL1.all = 0x0023;   // 重新使能SCI

    // 初始化PIE向量表
    EALLOW;
    PieVectTable.SCIA_RX_INT = &SCI_RXINT;  // 接收中断服务程序
    PieVectTable.SCIA_TX_INT = &SCI_TXINT;  // 发送中断服务程序
    EDIS;

    // 使能PIE组9中断（SCIA在INT9.1和INT9.2）
    PieCtrlRegs.PIEIER9.bit.INTx1 = 1;  // 使能SCIA_RX_INT (INT9.1)
    PieCtrlRegs.PIEIER9.bit.INTx2 = 1;  // 使能SCIA_TX_INT (INT9.2)

    // 使能CPU INT9和全局中断
    IER |= M_INT9;      // 使能CPU INT9

}

char RX_BUF;
/*==============================================================================
函数名称：SCI_RXINT(void)
函数功能：串口接收中断
输入参数：
输出参数：
返 回 值：
其它说明：
==============================================================================*/
__interrupt void SCI_RXINT(void){
    //do RX stuff
    RX_BUF = SciaRegs.SCIRXBUF.all;
    // 接收处理函数
//    CANDataMess.Out_DCCur.u32 = RX_BUF*1000;
    RX_Deal(RX_BUF);
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}

/*==============================================================================
函数名称：SCI_TXINT(void)
函数功能：串口发送中断
输入参数：
输出参数：
返 回 值：
其它说明：
==============================================================================*/
__interrupt void SCI_TXINT(void){
    //do TX stuff

    if( Mdu_UARTSend.eIx != Mdu_UARTSend.sIx  ){
        Mdu_UARTSend.sIx++;
        Mdu_UARTSend.sIx %= 64;
        SciaRegs.SCITXBUF.all = Mdu_UARTSend.sendbuf[ Mdu_UARTSend.sIx ];
    }
    else{
        Mdu_UARTSend.busy = 0;
    }

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}


char flag_Rx=0;
/*==============================================================================
函数名称：RX_Deal(void)
函数功能：接收数据检测 (7E数据包)
          数据包合理后flag_Rx置1
输入参数：
输出参数：
返 回 值：
其它说明：
==============================================================================*/
void RX_Deal(char rece){
    switch( opComm7ERece.state ){
        case 0: // 空闲状态
            if( rece == 0x7E ){
                opComm7ERece.cnt = 0;
                opComm7ERece.state = 1; // 转去接收数据包
            }
            break;
        case 1: // 数据体内容处理
            if( rece == 0x7E ){  // 收到7E时
                opComm7ERece.state = 3;
                flag_Rx = 1;
            }
            else{
                if( rece == 0x7D ){ // 收到7D时
                    opComm7ERece.state = 2; // 转去转义处理
                }
                else{ // 非7D 7E时
                    opComm7ERece.buf[opComm7ERece.cnt++] = rece;
                }
            }
            break;
        case 2:
            if( rece == 0x01 ){ // 收到00时
                opComm7ERece.buf[ opComm7ERece.cnt++] = 0x7D;
                opComm7ERece.state = 1; // 转去继续接收数据内容
            }
            else{ // 01时
                if( rece == 0x02 ){
                    opComm7ERece.buf[ opComm7ERece.cnt++] = 0x7E;
                    opComm7ERece.state = 1; // 转去继续接收数据内容
                }
                else{
                    opComm7ERece.state = 0; // 数据内容错误 重新检索包头
                }
            }
            break;
        case 3:

            break;
        default:
            opComm7ERece.state = 0;
            break;
    }
}

/*==============================================================================
函数名称：Rx_Data_Deal(void)
函数功能：数据包CRC校验和转换
          flag_Rx置1后将数据包进行CRC16校验并转移到Re576.Data_Buf中
输入参数：
输出参数：
返 回 值：
其它说明：
==============================================================================*/
void Rx_Data_Deal(){
    int i;
    if(flag_Rx == 1){
        flag_Rx = 0;
        if( opComm7ERece.cnt > 2 ){ // 解析数据包
            Re576.ID =  opComm7ERece.buf[1];
            // 校验
            if( Fun_CRC16Valid( &opComm7ERece.buf[1], opComm7ERece.cnt-1 ) ){
                // 填入相应的缓冲区
                for( i = 0; i < opComm7ERece.cnt; i++ ){
                    Re576.Data_Buf[i] = opComm7ERece.buf[i];
                }
                Re576.canDecFlg = 1;
                // 转为空闲态
                opComm7ERece.state = 0;
                opComm7ERece.cnt = 0;
            }else{
                // 以结尾为头重新接收
                opComm7ERece.state = 1;
                opComm7ERece.cnt = 0;
            }
        }
        else{ // 以结尾为头重新接收
            opComm7ERece.cnt = 0;
            opComm7ERece.state = 1;
        }
    }
}

