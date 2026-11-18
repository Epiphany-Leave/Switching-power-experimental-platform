#include "my_board.h"

uint16 dac_num;
uint32 PWM_PER = 0; // PWM时钟计数周期值
uint16 adc_sample_buf[10];

uint16 adc_sample_buff[30];

void my_adc_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    DMA_InitTypeDef DMA_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;
    ADC_CommonInitTypeDef ADC_CommonInitStructure;

    /* ----------------------------*/
    RCC_ADCCLKConfig(RCC_ADC12PLLCLK_Div1);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC12, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    /* ----------------------------*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_0 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    /* ---------------------------*/
    DMA_DeInit(DMA1_Channel1);
    DMA_DeInit(DMA1_Channel2);
    /* ----------------------------*/
    DMA_StructInit(&DMA_InitStructure);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(0x50000140);
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&adc_sample_buff;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = 15;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel2, &DMA_InitStructure);
	
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(0x50000040);
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&adc_sample_buff[15];
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = 15;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	
    DMA_Cmd(DMA1_Channel2, ENABLE);
    DMA_Cmd(DMA1_Channel1, ENABLE);
    /* ----------------------------*/
    ADC_DeInit(ADC2);
    ADC_DeInit(ADC1);
    /* ----------------------------*/
    ADC_VoltageRegulatorCmd(ADC1, ENABLE);
    ADC_VoltageRegulatorCmd(ADC2, ENABLE);
    delay_ms(10);
    ADC_SelectCalibrationMode(ADC2, ADC_CalibrationMode_Single);
    ADC_SelectCalibrationMode(ADC1, ADC_CalibrationMode_Single);
    ADC_StartCalibration(ADC2);
    ADC_StartCalibration(ADC1);

    while (ADC_GetCalibrationStatus(ADC2) != RESET)//RESET
    {
    }

    while (ADC_GetCalibrationStatus(ADC1) != RESET)//RESET
    {
    }

    ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;         // ADC独立模式，本应用中只用到ADC1
    ADC_CommonInitStructure.ADC_Clock = ADC_Clock_AsynClkMode;       // 时钟异步模式
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_1; // DMA 12bit 分辨率使能
    ADC_CommonInitStructure.ADC_DMAMode = ADC_DMAMode_Circular;      // DMA为连续模式
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = 1;                // 采样时间间隔
    ADC_CommonInit(ADC2, &ADC_CommonInitStructure);
    ADC_CommonInit(ADC1, &ADC_CommonInitStructure);
    /* ----------------------------*/
    ADC_InitStructure.ADC_ContinuousConvMode = ADC_ContinuousConvMode_Disable;
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;                              // 12bit 分辨率
    ADC_InitStructure.ADC_ExternalTrigConvEvent = ADC_ExternalTrigConvEvent_7;          // 配置HRtim的ADCTRIGGER_1为触发信号
    ADC_InitStructure.ADC_ExternalTrigEventEdge = ADC_ExternalTrigEventEdge_RisingEdge; // 触发信号上升沿启动
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;                              // 右对齐
    ADC_InitStructure.ADC_OverrunMode = ADC_OverrunMode_Disable;
    ADC_InitStructure.ADC_AutoInjMode = ADC_AutoInjec_Disable;
    ADC_InitStructure.ADC_NbrOfRegChannel = 15;
    ADC_Init(ADC2, &ADC_InitStructure);
    /* ----------------------------*/
    ADC_InitStructure.ADC_ContinuousConvMode = ADC_ContinuousConvMode_Disable;
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;                               // 12bit 分辨率
    ADC_InitStructure.ADC_ExternalTrigConvEvent = ADC_ExternalTrigConvEvent_8;           // 配置HRtim的ADCTRIGGER_1为触发信号
    ADC_InitStructure.ADC_ExternalTrigEventEdge = ADC_ExternalTrigEventEdge_FallingEdge; // 触发信号上升沿启动
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;                               // 右对齐
    ADC_InitStructure.ADC_OverrunMode = ADC_OverrunMode_Disable;
    ADC_InitStructure.ADC_AutoInjMode = ADC_AutoInjec_Disable;
    ADC_InitStructure.ADC_NbrOfRegChannel = 15;
    ADC_Init(ADC1, &ADC_InitStructure);
    /* ----------------------------*/
    ADC_DMAConfig(ADC2, ADC_DMAMode_Circular);
    ADC_DMAConfig(ADC1, ADC_DMAMode_Circular);
    /* ----------------------------*/
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_61Cycles5); /* to PA0 (Iin)  */  // PA0        1
    ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 2, ADC_SampleTime_61Cycles5); /* to PA1 (Iout) */  // PA1         2
    ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 3, ADC_SampleTime_61Cycles5); /* to PA2 (Vout) */  // PA2         3
    ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 4, ADC_SampleTime_61Cycles5); /* to PA3 (Vin) */   // PA3          4
    ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 5, ADC_SampleTime_61Cycles5); /* to PA0 (Iin)  */  // PC1           7
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 6, ADC_SampleTime_61Cycles5); /* to PA0 (Iin)  */  // PA0        1
    ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 7, ADC_SampleTime_61Cycles5); /* to PA1 (Iout) */  // PA1         2
    ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 8, ADC_SampleTime_61Cycles5); /* to PA2 (Vout) */  // PA2         3
    ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 9, ADC_SampleTime_61Cycles5); /* to PA3 (Vin) */   // PA3          4
    ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 10, ADC_SampleTime_61Cycles5); /* to PA0 (Iin)  */ // PC1           7
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 11, ADC_SampleTime_61Cycles5); /* to PA0 (Iin)  */ // PA0        1
    ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 12, ADC_SampleTime_61Cycles5); /* to PA1 (Iout) */ // PA1         2
    ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 13, ADC_SampleTime_61Cycles5); /* to PA2 (Vout) */ // PA2         3
    ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 14, ADC_SampleTime_61Cycles5); /* to PA3 (Vin) */  // PA3          4
    ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 15, ADC_SampleTime_61Cycles5); /* to PA0 (Iin)  */ // PC1           7
    /* ----------------------------*/
    ADC_RegularChannelConfig(ADC2, ADC_Channel_11, 1, ADC_SampleTime_61Cycles5); /* to PA1 (Iout) */  // PA4           5
    ADC_RegularChannelConfig(ADC2, ADC_Channel_5, 2, ADC_SampleTime_61Cycles5); /* to PA2 (Vout) */   // PC0           6
    ADC_RegularChannelConfig(ADC2, ADC_Channel_7, 3, ADC_SampleTime_61Cycles5); /* to PA3 (Vin) */    // PC2            8
    ADC_RegularChannelConfig(ADC2, ADC_Channel_8, 4, ADC_SampleTime_61Cycles5); /* to PA2 (Vout) */   // PC3              9
    ADC_RegularChannelConfig(ADC2, ADC_Channel_9, 5, ADC_SampleTime_61Cycles5); /* to PA3 (Vin) */    // PC4           10
    ADC_RegularChannelConfig(ADC2, ADC_Channel_11, 6, ADC_SampleTime_61Cycles5); /* to PA1 (Iout) */  // PA4           5
    ADC_RegularChannelConfig(ADC2, ADC_Channel_5, 7, ADC_SampleTime_61Cycles5); /* to PA2 (Vout) */   // PC0           6
    ADC_RegularChannelConfig(ADC2, ADC_Channel_7, 8, ADC_SampleTime_61Cycles5); /* to PA3 (Vin) */    // PC2            8
    ADC_RegularChannelConfig(ADC2, ADC_Channel_8, 9, ADC_SampleTime_61Cycles5); /* to PA2 (Vout) */   // PC3              9
    ADC_RegularChannelConfig(ADC2, ADC_Channel_9, 10, ADC_SampleTime_61Cycles5); /* to PA3 (Vin) */   // PC4           10
    ADC_RegularChannelConfig(ADC2, ADC_Channel_11, 11, ADC_SampleTime_61Cycles5); /* to PA1 (Iout) */ // PA4           5
    ADC_RegularChannelConfig(ADC2, ADC_Channel_5, 12, ADC_SampleTime_61Cycles5); /* to PA2 (Vout) */  // PC0           6
    ADC_RegularChannelConfig(ADC2, ADC_Channel_7, 13, ADC_SampleTime_61Cycles5); /* to PA3 (Vin) */   // PC2            8
    ADC_RegularChannelConfig(ADC2, ADC_Channel_8, 14, ADC_SampleTime_61Cycles5); /* to PA2 (Vout) */  // PC3              9
    ADC_RegularChannelConfig(ADC2, ADC_Channel_9, 15, ADC_SampleTime_61Cycles5); /* to PA3 (Vin) */   // PC4           10
    /* ----------------------------*/
    ADC_VoltageRegulatorCmd(ADC1, ENABLE);
    ADC_VoltageRegulatorCmd(ADC2, ENABLE);
	
    ADC_DMACmd(ADC2, ENABLE);
    ADC_DMACmd(ADC1, ENABLE);
	ADC_DMAConfig(ADC2, ADC_DMAMode_Circular);
    ADC_DMAConfig(ADC1, ADC_DMAMode_Circular);
    ADC_Cmd(ADC2, ENABLE);
    ADC_Cmd(ADC1, ENABLE);
	DMA_Cmd(DMA1_Channel2, ENABLE);
    DMA_Cmd(DMA1_Channel1, ENABLE);
	
    while (!ADC_GetFlagStatus(ADC2, ADC_FLAG_RDY))//!=0
        ; // wait for ADC1 ADRDY

    while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_RDY))//!=0
        ; // wait for ADC1 ADRDY

    ADC_StartConversion(ADC2);
    ADC_StartConversion(ADC1);

}

void my_pwm_init(u32 fsw, uint8 HTIM_CHANNEL, u32 divide_num)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    HRTIM_BaseInitTypeDef HRTIM_BaseInitStructure;
    HRTIM_TimerCfgTypeDef HRTIM_TimerWaveStructure;
    HRTIM_TimerInitTypeDef HRTIM_TimerInitStructure;
    HRTIM_OutputCfgTypeDef HRTIM_TIM_OutputStructure;
    HRTIM_DeadTimeCfgTypeDef HRTIM_DeadTimeStructure;
    HRTIM_ADCTriggerCfgTypeDef HRTIM_ADCTrigStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    memset((void *)&GPIO_InitStructure, 0x0, sizeof(GPIO_InitStructure));
    memset((void *)&HRTIM_BaseInitStructure, 0x0, sizeof(HRTIM_BaseInitStructure));
    memset((void *)&HRTIM_TimerWaveStructure, 0x0, sizeof(HRTIM_TimerWaveStructure));
    memset((void *)&HRTIM_TimerInitStructure, 0x0, sizeof(HRTIM_TimerInitStructure));
    memset((void *)&HRTIM_TIM_OutputStructure, 0x0, sizeof(HRTIM_TIM_OutputStructure));
    memset((void *)&HRTIM_DeadTimeStructure, 0x0, sizeof(HRTIM_DeadTimeStructure));
    memset((void *)&HRTIM_ADCTrigStructure, 0x0, sizeof(HRTIM_ADCTrigStructure));
    memset((void *)&NVIC_InitStructure, 0x0, sizeof(NVIC_InitStructure));




    /* ----------------------------*/
    /*             配置PWM输出GPIO*/
    /* ----------------------------*/
    float pll;
    int spll;
//    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
//    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

    if (fsw <= 37000)
    {
        pll = 1152e6;
        spll = HRTIM_PRESCALERRATIO_MUL8;
    }
    else if (fsw <= 71000)
    {
        pll = 2304e6;
        spll = HRTIM_PRESCALERRATIO_MUL16;
    }
    else
    {
        pll = 4608e6;
        spll = HRTIM_PRESCALERRATIO_MUL32;
    }

    /* ----------------------------*/
    /* HRTIM Global initialization */
    /* ----------------------------*/
    RCC_HRTIM1CLKConfig(RCC_HRTIM1CLK_PLLCLK);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_HRTIM1, ENABLE);
    HRTIM_DLLCalibrationStart(HRTIM1, HRTIM_CALIBRATIONRATE_14);

    while (HRTIM_GetCommonFlagStatus(HRTIM1, HRTIM_ISR_DLLRDY) == RESET)//RESET
        ;

    /* --------------------------------------------------- */
    /* HRTIM_TIMERINDEX_MASTER initialization: timer mode and PWM frequency */
    /* --------------------------------------------------- */
    HRTIM_TimerInitStructure.HalfModeEnable = HRTIM_HALFMODE_DISABLED;
    HRTIM_TimerInitStructure.StartOnSync = HRTIM_SYNCSTART_DISABLED;
    HRTIM_TimerInitStructure.ResetOnSync = HRTIM_SYNCRESET_DISABLED;
    HRTIM_TimerInitStructure.DACSynchro = HRTIM_DACSYNC_NONE;
    HRTIM_TimerInitStructure.PreloadEnable = HRTIM_PRELOAD_ENABLED; // 直接加载
    HRTIM_TimerInitStructure.UpdateGating = HRTIM_UPDATEGATING_INDEPENDENT;
    HRTIM_TimerInitStructure.BurstMode = HRTIM_TIMERBURSTMODE_MAINTAINCLOCK;
    HRTIM_TimerInitStructure.RepetitionUpdate = HRTIM_UPDATEONREPETITION_ENABLED;
    /* --------------------------*/
    HRTIM_BaseInitStructure.Period = pll / fsw;                 // HRTIM周期寄存器, Period = fHRCK / fsw
    HRTIM_BaseInitStructure.RepetitionCounter = divide_num - 1; // 1 ISR every 128 PWM periods
    HRTIM_BaseInitStructure.PrescalerRatio = spll;              // HRTIM时钟倍频系数，2048MHZ
    HRTIM_BaseInitStructure.Mode = HRTIM_MODE_CONTINOUS;        // HETIM运行在连续模式
    HRTIM_Waveform_Init(HRTIM1, HRTIM_TIMERINDEX_MASTER, &HRTIM_BaseInitStructure, &HRTIM_TimerInitStructure);

    //////////////////////////////////////////////////////////////////////////////////
    if ((HTIM_CHANNEL & 0x01) == 0x01)
    {
        //--------------HRTIM_CHB1 == PA10; HRTIM_CHB2 == PA11--------------//
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        //--------------HRTIM_CHC1 == PB12; HRTIM_CHB2 == PB13--------------//
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_13); // PA10复用
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_13); // PA11复用
        /* --------------------------------------------------- */
        /* HRTIMx initialization: timer mode and PWM frequency */
        /* --------------------------------------------------- */
        HRTIM_TimerInitStructure.RepetitionUpdate = HRTIM_UPDATEONREPETITION_ENABLED;
        HRTIM_BaseInitStructure.Period = pll / fsw;          // HRTIM周期寄存器, Period = fHRCK / fsw
        HRTIM_BaseInitStructure.RepetitionCounter = 1;       // 1 ISR every 128 PWM periods
        HRTIM_BaseInitStructure.PrescalerRatio = spll;       // HRTIM时钟倍频系数，512MHZ
        HRTIM_BaseInitStructure.Mode = HRTIM_MODE_CONTINOUS; // HETIM运行在非连续模式，使用MASTER作为复位时钟
        HRTIM_Waveform_Init(HRTIM1, HRTIM_TIMERINDEX_TIMER_A, &HRTIM_BaseInitStructure, &HRTIM_TimerInitStructure);
        /* ------------------------------------------------ */
        /* TIMERx output and registers update configuration */
        /* ------------------------------------------------ */
        HRTIM_TimerWaveStructure.DeadTimeInsertion = HRTIM_TIMDEADTIMEINSERTION_ENABLED;      // 死区时间：使能(对称互补模式)
        HRTIM_TimerWaveStructure.DelayedProtectionMode = HRTIM_TIMDELAYEDPROTECTION_DISABLED; // 延时保护：无
        HRTIM_TimerWaveStructure.FaultEnable = HRTIM_TIMFAULTENABLE_NONE;                     // 故障使能：无
        HRTIM_TimerWaveStructure.FaultLock = HRTIM_TIMFAULTLOCK_READWRITE;                    // 故障位  ：可读写
        HRTIM_TimerWaveStructure.PushPull = HRTIM_TIMPUSHPULLMODE_DISABLED;
        HRTIM_TimerWaveStructure.ResetTrigger = HRTIM_TIMRESETTRIGGER_NONE;
        HRTIM_TimerWaveStructure.ResetUpdate = HRTIM_TIMUPDATEONRESET_DISABLED;
        HRTIM_TimerWaveStructure.UpdateTrigger = HRTIM_TIMUPDATETRIGGER_TIMER_A;
        HRTIM_WaveformTimerConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_A, &HRTIM_TimerWaveStructure);
        /* -------------------------------- */
        /* -------HRTIM CHBx 输出配置 ------*/
        /* -------------------------------- */
        /* -------------------------------- */
        HRTIM_TIM_OutputStructure.Polarity = HRTIM_OUTPUTPOLARITY_HIGH;                       // 极性控制位：正极性
        HRTIM_TIM_OutputStructure.SetSource = HRTIM_RST1R_CMP1;                               // PWM输出高的触发源：CMP1
        HRTIM_TIM_OutputStructure.ResetSource = HRTIM_RST1R_CMP4;                             // PWM输出低的触发源：CMP4
        HRTIM_TIM_OutputStructure.IdleMode = HRTIM_OUTPUTIDLEMODE_NONE;                       // 输出不受空闲状态影响
        HRTIM_TIM_OutputStructure.IdleState = HRTIM_OUTPUTIDLESTATE_INACTIVE;                 // 输出不受空闲状态影响
        HRTIM_TIM_OutputStructure.FaultState = HRTIM_OUTPUTFAULTSTATE_NONE;                   // 故障状态：PWM输出不受故障影响
        HRTIM_TIM_OutputStructure.ChopperModeEnable = HRTIM_OUTPUTCHOPPERMODE_DISABLED;       // 不使用斩波器
        HRTIM_TIM_OutputStructure.BurstModeEntryDelayed = HRTIM_OUTPUTBURSTMODEENTRY_REGULAR; // 死区时间不插入空闲状态
        HRTIM_WaveformOutputConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_A, HRTIM_OUTPUT_TA1, &HRTIM_TIM_OutputStructure);
        HRTIM_DeadTimeStructure.Prescaler = 0x01; // 死区时间预分频器
        HRTIM_DeadTimeStructure.FallingLock = HRTIM_TIMDEADTIME_FALLINGLOCK_WRITE;
        HRTIM_DeadTimeStructure.FallingSign = HRTIM_TIMDEADTIME_FALLINGSIGN_POSITIVE; // 下降沿加死区
        HRTIM_DeadTimeStructure.FallingSignLock = HRTIM_TIMDEADTIME_FALLINGSIGNLOCK_WRITE;
        HRTIM_DeadTimeStructure.FallingValue = DeadTime_Value; // 设定死区时间值
        HRTIM_DeadTimeStructure.RisingLock = HRTIM_TIMDEADTIME_RISINGLOCK_WRITE;
        HRTIM_DeadTimeStructure.RisingSign = HRTIM_TIMDEADTIME_RISINGSIGN_POSITIVE; // 下降沿加死区
        HRTIM_DeadTimeStructure.RisingSignLock = HRTIM_TIMDEADTIME_RISINGSIGNLOCK_WRITE;
        HRTIM_DeadTimeStructure.RisingValue = DeadTime_Value; // 设置上升沿死区时间值
        HRTIM_DeadTimeConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_A, &HRTIM_DeadTimeStructure);
    }

    ///////////////////////////////////////////////////

    if ((HTIM_CHANNEL & 0x02) == 0x02)
    {
        //--------------HRTIM_CHB1 == PA10; HRTIM_CHB2 == PA11--------------//
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        //--------------HRTIM_CHC1 == PB12; HRTIM_CHB2 == PB13--------------//
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_13); // PA10复用
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_13); // PA11复用
        /* --------------------------------------------------- */
        /* HRTIMx initialization: timer mode and PWM frequency */
        /* --------------------------------------------------- */
        HRTIM_TimerInitStructure.RepetitionUpdate = HRTIM_UPDATEONREPETITION_ENABLED;
        HRTIM_BaseInitStructure.Period = pll / fsw;          // HRTIM周期寄存器, Period = fHRCK / fsw
        HRTIM_BaseInitStructure.RepetitionCounter = 1;       // 1 ISR every 128 PWM periods
        HRTIM_BaseInitStructure.PrescalerRatio = spll;       // HRTIM时钟倍频系数，512MHZ
        HRTIM_BaseInitStructure.Mode = HRTIM_MODE_CONTINOUS; // HETIM运行在非连续模式，使用MASTER作为复位时钟
        HRTIM_Waveform_Init(HRTIM1, HRTIM_TIMERINDEX_TIMER_B, &HRTIM_BaseInitStructure, &HRTIM_TimerInitStructure);
        /* ------------------------------------------------ */
        /* TIMERx output and registers update configuration */
        /* ------------------------------------------------ */
        HRTIM_TimerWaveStructure.DeadTimeInsertion = HRTIM_TIMDEADTIMEINSERTION_ENABLED;      // 死区时间：使能(对称互补模式)
        HRTIM_TimerWaveStructure.DelayedProtectionMode = HRTIM_TIMDELAYEDPROTECTION_DISABLED; // 延时保护：无
        HRTIM_TimerWaveStructure.FaultEnable = HRTIM_TIMFAULTENABLE_NONE;                     // 故障使能：无
        HRTIM_TimerWaveStructure.FaultLock = HRTIM_TIMFAULTLOCK_READWRITE;                    // 故障位  ：可读写
        HRTIM_TimerWaveStructure.PushPull = HRTIM_TIMPUSHPULLMODE_DISABLED;
        HRTIM_TimerWaveStructure.ResetTrigger = HRTIM_TIMRESETTRIGGER_MASTER_PER;
        HRTIM_TimerWaveStructure.ResetUpdate = HRTIM_TIMUPDATEONRESET_DISABLED;
        HRTIM_TimerWaveStructure.UpdateTrigger = HRTIM_TIMUPDATETRIGGER_TIMER_B;
        HRTIM_WaveformTimerConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_B, &HRTIM_TimerWaveStructure);
        /* -------------------------------- */
        /* -------HRTIM CHBx 输出配置 ------*/
        /* -------------------------------- */
        /* -------------------------------- */
        HRTIM_TIM_OutputStructure.Polarity = HRTIM_OUTPUTPOLARITY_HIGH;                       // 极性控制位：正极性
        HRTIM_TIM_OutputStructure.SetSource = HRTIM_RST1R_CMP1;                               // PWM输出高的触发源：CMP1
        HRTIM_TIM_OutputStructure.ResetSource = HRTIM_RST1R_CMP4;                             // PWM输出低的触发源：CMP4
        HRTIM_TIM_OutputStructure.IdleMode = HRTIM_OUTPUTIDLEMODE_NONE;                       // 输出不受空闲状态影响
        HRTIM_TIM_OutputStructure.IdleState = HRTIM_OUTPUTIDLESTATE_INACTIVE;                 // 输出不受空闲状态影响
        HRTIM_TIM_OutputStructure.FaultState = HRTIM_OUTPUTFAULTSTATE_NONE;                   // 故障状态：PWM输出不受故障影响
        HRTIM_TIM_OutputStructure.ChopperModeEnable = HRTIM_OUTPUTCHOPPERMODE_DISABLED;       // 不使用斩波器
        HRTIM_TIM_OutputStructure.BurstModeEntryDelayed = HRTIM_OUTPUTBURSTMODEENTRY_REGULAR; // 死区时间不插入空闲状态
        HRTIM_WaveformOutputConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_B, HRTIM_OUTPUT_TB1, &HRTIM_TIM_OutputStructure);
        HRTIM_DeadTimeStructure.Prescaler = 0x01; // 死区时间预分频器
        HRTIM_DeadTimeStructure.FallingLock = HRTIM_TIMDEADTIME_FALLINGLOCK_WRITE;
        HRTIM_DeadTimeStructure.FallingSign = HRTIM_TIMDEADTIME_FALLINGSIGN_POSITIVE; // 下降沿加死区
        HRTIM_DeadTimeStructure.FallingSignLock = HRTIM_TIMDEADTIME_FALLINGSIGNLOCK_WRITE;
        HRTIM_DeadTimeStructure.FallingValue = DeadTime_Value; // 设定死区时间值
        HRTIM_DeadTimeStructure.RisingLock = HRTIM_TIMDEADTIME_RISINGLOCK_WRITE;
        HRTIM_DeadTimeStructure.RisingSign = HRTIM_TIMDEADTIME_RISINGSIGN_POSITIVE; // 下降沿加死区
        HRTIM_DeadTimeStructure.RisingSignLock = HRTIM_TIMDEADTIME_RISINGSIGNLOCK_WRITE;
        HRTIM_DeadTimeStructure.RisingValue = DeadTime_Value; // 设置上升沿死区时间值
        HRTIM_DeadTimeConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_B, &HRTIM_DeadTimeStructure);
    }

    ///////////////////////////////////////////////
    if ((HTIM_CHANNEL & 0x04) == 0x04)
    {
        //--------------HRTIM_CHB1 == PA10; HRTIM_CHB2 == PA11--------------//
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
        //--------------HRTIM_CHC1 == PB12; HRTIM_CHC2 == PB13--------------//
        GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_13); // PA10复用
        GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_13); // PA11复用
        /* --------------------------------------------------- */
        /* HRTIMx initialization: timer mode and PWM frequency */
        /* --------------------------------------------------- */
        HRTIM_TimerInitStructure.RepetitionUpdate = HRTIM_UPDATEONREPETITION_ENABLED;
        HRTIM_BaseInitStructure.Period = pll / fsw;          // HRTIM周期寄存器, Period = fHRCK / fsw
        HRTIM_BaseInitStructure.RepetitionCounter = 1;       // 1 ISR every 128 PWM periods
        HRTIM_BaseInitStructure.PrescalerRatio = spll;       // HRTIM时钟倍频系数，512MHZ
        HRTIM_BaseInitStructure.Mode = HRTIM_MODE_CONTINOUS; // HETIM运行在非连续模式，使用MASTER作为复位时钟
        HRTIM_Waveform_Init(HRTIM1, HRTIM_TIMERINDEX_TIMER_C, &HRTIM_BaseInitStructure, &HRTIM_TimerInitStructure);
        /* ------------------------------------------------ */
        /* TIMERx output and registers update configuration */
        /* ------------------------------------------------ */
        HRTIM_TimerWaveStructure.DeadTimeInsertion = HRTIM_TIMDEADTIMEINSERTION_ENABLED;      // 死区时间：使能(对称互补模式)
        HRTIM_TimerWaveStructure.DelayedProtectionMode = HRTIM_TIMDELAYEDPROTECTION_DISABLED; // 延时保护：无
        HRTIM_TimerWaveStructure.FaultEnable = HRTIM_TIMFAULTENABLE_NONE;                     // 故障使能：无
        HRTIM_TimerWaveStructure.FaultLock = HRTIM_TIMFAULTLOCK_READWRITE;                    // 故障位  ：可读写
        HRTIM_TimerWaveStructure.PushPull = HRTIM_TIMPUSHPULLMODE_DISABLED;
        HRTIM_TimerWaveStructure.ResetTrigger = HRTIM_TIMRESETTRIGGER_NONE;
        HRTIM_TimerWaveStructure.ResetUpdate = HRTIM_TIMUPDATEONRESET_DISABLED;
        HRTIM_TimerWaveStructure.UpdateTrigger = HRTIM_TIMUPDATETRIGGER_TIMER_C;
        HRTIM_WaveformTimerConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_C, &HRTIM_TimerWaveStructure);
        /* -------------------------------- */
        /* -------HRTIM CHBx 输出配置 ------*/
        /* -------------------------------- */
        /* -------------------------------- */
        HRTIM_TIM_OutputStructure.Polarity = HRTIM_OUTPUTPOLARITY_HIGH;                       // 极性控制位：正极性
        HRTIM_TIM_OutputStructure.SetSource = HRTIM_RST1R_CMP1;                               // PWM输出高的触发源：CMP1
        HRTIM_TIM_OutputStructure.ResetSource = HRTIM_RST1R_CMP4;                             // PWM输出低的触发源：CMP4
        HRTIM_TIM_OutputStructure.IdleMode = HRTIM_OUTPUTIDLEMODE_NONE;                       // 输出不受空闲状态影响
        HRTIM_TIM_OutputStructure.IdleState = HRTIM_OUTPUTIDLESTATE_INACTIVE;                 // 输出不受空闲状态影响
        HRTIM_TIM_OutputStructure.FaultState = HRTIM_OUTPUTFAULTSTATE_NONE;                   // 故障状态：PWM输出不受故障影响
        HRTIM_TIM_OutputStructure.ChopperModeEnable = HRTIM_OUTPUTCHOPPERMODE_DISABLED;       // 不使用斩波器
        HRTIM_TIM_OutputStructure.BurstModeEntryDelayed = HRTIM_OUTPUTBURSTMODEENTRY_REGULAR; // 死区时间不插入空闲状态
        HRTIM_WaveformOutputConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_C, HRTIM_OUTPUT_TC1, &HRTIM_TIM_OutputStructure);
        HRTIM_DeadTimeStructure.Prescaler = 0x01; // 死区时间预分频器
        HRTIM_DeadTimeStructure.FallingLock = HRTIM_TIMDEADTIME_FALLINGLOCK_WRITE;
        HRTIM_DeadTimeStructure.FallingSign = HRTIM_TIMDEADTIME_FALLINGSIGN_POSITIVE; // 下降沿加死区
        HRTIM_DeadTimeStructure.FallingSignLock = HRTIM_TIMDEADTIME_FALLINGSIGNLOCK_WRITE;
        HRTIM_DeadTimeStructure.FallingValue = DeadTime_Value; // 设定死区时间值
        HRTIM_DeadTimeStructure.RisingLock = HRTIM_TIMDEADTIME_RISINGLOCK_WRITE;
        HRTIM_DeadTimeStructure.RisingSign = HRTIM_TIMDEADTIME_RISINGSIGN_POSITIVE; // 下降沿加死区
        HRTIM_DeadTimeStructure.RisingSignLock = HRTIM_TIMDEADTIME_RISINGSIGNLOCK_WRITE;
        HRTIM_DeadTimeStructure.RisingValue = DeadTime_Value; // 设置上升沿死区时间值
        HRTIM_DeadTimeConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_C, &HRTIM_DeadTimeStructure);
    }

    ///////////////////////////////////////////////
    if ((HTIM_CHANNEL & 0x08) == 0x08)
    {
        //--------------HRTIM_CHB1 == PA10; HRTIM_CHB2 == PA11--------------//
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
        //--------------HRTIM_CHC1 == PB12; HRTIM_CHB2 == PB13--------------//
        GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_13); // PA10复用
        GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_13); // PA11复用
        /* --------------------------------------------------- */
        /* HRTIMx initialization: timer mode and PWM frequency */
        /* --------------------------------------------------- */
        HRTIM_TimerInitStructure.RepetitionUpdate = HRTIM_UPDATEONREPETITION_ENABLED;
        HRTIM_BaseInitStructure.Period = pll / fsw;          // HRTIM周期寄存器, Period = fHRCK / fsw
        HRTIM_BaseInitStructure.RepetitionCounter = 1;       // 1 ISR every 128 PWM periods
        HRTIM_BaseInitStructure.PrescalerRatio = spll;       // HRTIM时钟倍频系数，512MHZ
        HRTIM_BaseInitStructure.Mode = HRTIM_MODE_CONTINOUS; // HETIM运行在非连续模式，使用MASTER作为复位时钟
        HRTIM_Waveform_Init(HRTIM1, HRTIM_TIMERINDEX_TIMER_D, &HRTIM_BaseInitStructure, &HRTIM_TimerInitStructure);
        /* ------------------------------------------------ */
        /* TIMERx output and registers update configuration */
        /* ------------------------------------------------ */
        HRTIM_TimerWaveStructure.DeadTimeInsertion = HRTIM_TIMDEADTIMEINSERTION_ENABLED;      // 死区时间：使能(对称互补模式)
        HRTIM_TimerWaveStructure.DelayedProtectionMode = HRTIM_TIMDELAYEDPROTECTION_DISABLED; // 延时保护：无
        HRTIM_TimerWaveStructure.FaultEnable = HRTIM_TIMFAULTENABLE_NONE;                     // 故障使能：无
        HRTIM_TimerWaveStructure.FaultLock = HRTIM_TIMFAULTLOCK_READWRITE;                    // 故障位  ：可读写
        HRTIM_TimerWaveStructure.PushPull = HRTIM_TIMPUSHPULLMODE_DISABLED;
        HRTIM_TimerWaveStructure.ResetTrigger = HRTIM_TIMRESETTRIGGER_NONE;
        HRTIM_TimerWaveStructure.ResetUpdate = HRTIM_TIMUPDATEONRESET_DISABLED;
        HRTIM_TimerWaveStructure.UpdateTrigger = HRTIM_TIMUPDATETRIGGER_TIMER_D;
        HRTIM_WaveformTimerConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_D, &HRTIM_TimerWaveStructure);
        /* -------------------------------- */
        /* -------HRTIM CHBx 输出配置 ------*/
        /* -------------------------------- */
        /* -------------------------------- */
        HRTIM_TIM_OutputStructure.Polarity = HRTIM_OUTPUTPOLARITY_HIGH;                       // 极性控制位：正极性
        HRTIM_TIM_OutputStructure.SetSource = HRTIM_RST1R_CMP1;                               // PWM输出高的触发源：CMP1
        HRTIM_TIM_OutputStructure.ResetSource = HRTIM_RST1R_CMP4;                             // PWM输出低的触发源：CMP4
        HRTIM_TIM_OutputStructure.IdleMode = HRTIM_OUTPUTIDLEMODE_NONE;                       // 输出不受空闲状态影响
        HRTIM_TIM_OutputStructure.IdleState = HRTIM_OUTPUTIDLESTATE_INACTIVE;                 // 输出不受空闲状态影响
        HRTIM_TIM_OutputStructure.FaultState = HRTIM_OUTPUTFAULTSTATE_NONE;                   // 故障状态：PWM输出不受故障影响
        HRTIM_TIM_OutputStructure.ChopperModeEnable = HRTIM_OUTPUTCHOPPERMODE_DISABLED;       // 不使用斩波器
        HRTIM_TIM_OutputStructure.BurstModeEntryDelayed = HRTIM_OUTPUTBURSTMODEENTRY_REGULAR; // 死区时间不插入空闲状态
        HRTIM_WaveformOutputConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_D, HRTIM_OUTPUT_TD1, &HRTIM_TIM_OutputStructure);
        /* -------------------------------- */
        /* -----HRTIM PWM 死区时间配置 ---- */
        /* -------------------------------- */
        HRTIM_DeadTimeStructure.Prescaler = 0x01; // 死区时间预分频器
        HRTIM_DeadTimeStructure.FallingLock = HRTIM_TIMDEADTIME_FALLINGLOCK_WRITE;
        HRTIM_DeadTimeStructure.FallingSign = HRTIM_TIMDEADTIME_FALLINGSIGN_POSITIVE; // 下降沿加死区
        HRTIM_DeadTimeStructure.FallingSignLock = HRTIM_TIMDEADTIME_FALLINGSIGNLOCK_WRITE;
        HRTIM_DeadTimeStructure.FallingValue = DeadTime_Value; // 设定死区时间值
        HRTIM_DeadTimeStructure.RisingLock = HRTIM_TIMDEADTIME_RISINGLOCK_WRITE;
        HRTIM_DeadTimeStructure.RisingSign = HRTIM_TIMDEADTIME_RISINGSIGN_POSITIVE; // 下降沿加死区
        HRTIM_DeadTimeStructure.RisingSignLock = HRTIM_TIMDEADTIME_RISINGSIGNLOCK_WRITE;
        HRTIM_DeadTimeStructure.RisingValue = DeadTime_Value; // 设置上升沿死区时间值
        HRTIM_DeadTimeConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_D, &HRTIM_DeadTimeStructure);
    }

    HRTIM_MasterSetCompare(HRTIM1, HRTIM_COMPAREUNIT_1, 0.5 * HRTIM_BaseInitStructure.Period);
    HRTIM_MasterSetCompare(HRTIM1, HRTIM_COMPAREUNIT_4, 0.5 * HRTIM_BaseInitStructure.Period);
    ///////////////////////////////////////////////
    HRTIM_SlaveSetCompare(HRTIM1, HRTIM_TIMERINDEX_TIMER_D, HRTIM_COMPAREUNIT_1, 0.5 * HRTIM_BaseInitStructure.Period);
    HRTIM_SlaveSetCompare(HRTIM1, HRTIM_TIMERINDEX_TIMER_D, HRTIM_COMPAREUNIT_4, 0.5 * HRTIM_BaseInitStructure.Period);
    /* --------------------------*/
    HRTIM_SlaveSetCompare(HRTIM1, HRTIM_TIMERINDEX_TIMER_A, HRTIM_COMPAREUNIT_1, 0.5 * HRTIM_BaseInitStructure.Period);
    HRTIM_SlaveSetCompare(HRTIM1, HRTIM_TIMERINDEX_TIMER_A, HRTIM_COMPAREUNIT_4, 0.5 * HRTIM_BaseInitStructure.Period);
    /* --------------------------*/
    HRTIM_SlaveSetCompare(HRTIM1, HRTIM_TIMERINDEX_TIMER_B, HRTIM_COMPAREUNIT_1, 0.5 * HRTIM_BaseInitStructure.Period);
    HRTIM_SlaveSetCompare(HRTIM1, HRTIM_TIMERINDEX_TIMER_B, HRTIM_COMPAREUNIT_4, 0.5 * HRTIM_BaseInitStructure.Period);
    /* --------------------------*/
    HRTIM_SlaveSetCompare(HRTIM1, HRTIM_TIMERINDEX_TIMER_C, HRTIM_COMPAREUNIT_1, 0.5 * HRTIM_BaseInitStructure.Period);
    HRTIM_SlaveSetCompare(HRTIM1, HRTIM_TIMERINDEX_TIMER_C, HRTIM_COMPAREUNIT_4, 0.5 * HRTIM_BaseInitStructure.Period);
    /* --------------------------*/
    HRTIM_SlaveSetCompare(HRTIM1, HRTIM_TIMERINDEX_TIMER_D, HRTIM_COMPAREUNIT_1, 0.5 * HRTIM_BaseInitStructure.Period);
    HRTIM_SlaveSetCompare(HRTIM1, HRTIM_TIMERINDEX_TIMER_D, HRTIM_COMPAREUNIT_4, 0.5 * HRTIM_BaseInitStructure.Period);
    /* --------------------------*/
    /* ADC trigger initialization */
    /* --------------------------*/
    HRTIM_ADCTrigStructure.Trigger = HRTIM_ADCTRIGGEREVENT24_MASTER_CMP1;
    HRTIM_ADCTrigStructure.UpdateSource = HRTIM_ADCTRIGGERUPDATE_MASTER;
    HRTIM_ADCTriggerConfig(HRTIM1, HRTIM_ADCTRIGGER_3, &HRTIM_ADCTrigStructure);
    /* --------------------------*/
    HRTIM_ADCTrigStructure.Trigger = HRTIM_ADCTRIGGEREVENT13_MASTER_PERIOD;
    HRTIM_ADCTrigStructure.UpdateSource = HRTIM_ADCTRIGGERUPDATE_MASTER;
    HRTIM_ADCTriggerConfig(HRTIM1, HRTIM_ADCTRIGGER_1, &HRTIM_ADCTrigStructure);
    /* -------------------------*/
    /* Interrupt initialization */
    /* -------------------------*/
    /* Configure and enable HRTIM TIMERA interrupt channel in NVIC */
    NVIC_InitStructure.NVIC_IRQChannel = HRTIM1_Master_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    /* TIMER B issues an interrupt on each repetition event */
    HRTIM_ITConfig(HRTIM1, HRTIM_TIMERINDEX_MASTER, HRTIM_TIM_IT_REP, ENABLE);
    HRTIM_WaveformCounterStart(HRTIM1, HRTIM_TIMERID_TIMER_A | HRTIM_TIMERID_TIMER_B | HRTIM_TIMERID_TIMER_C | HRTIM_TIMERID_TIMER_D); // 启动HRTIM PWM模式下的TIMER_D

    if ((HTIM_CHANNEL & 0x01) == 0x01)
    {
        HRTIM_WaveformOutputStart(HRTIM1, HRTIM_OUTPUT_TA1 | HRTIM_OUTPUT_TA2);
    }

    if ((HTIM_CHANNEL & 0x02) == 0x02)
    {
        HRTIM_WaveformOutputStart(HRTIM1, HRTIM_OUTPUT_TB1 | HRTIM_OUTPUT_TB2);
    }

    if ((HTIM_CHANNEL & 0x04) == 0x04)
    {
        HRTIM_WaveformOutputStart(HRTIM1, HRTIM_OUTPUT_TC1 | HRTIM_OUTPUT_TC2);
    }

    if ((HTIM_CHANNEL & 0x08) == 0x08)
    {
        HRTIM_WaveformOutputStart(HRTIM1, HRTIM_OUTPUT_TD1 | HRTIM_OUTPUT_TD2);
    }

    HRTIM_WaveformCounterStart(HRTIM1, HRTIM_TIMERID_MASTER); // 启动HRTIM PWM模式下的MASTER
    PWM_PER = HRTIM_BaseInitStructure.Period;
}

inline void my_pwm_update(float duty, uint32 pwm_chennel)
{
    uint32 PWM_PER_0_5 = 0.5f * PWM_PER;
    HRTIM_SlaveSetCompare(HRTIM1, pwm_chennel, HRTIM_COMPAREUNIT_1, PWM_PER_0_5 - duty * 0.5f * PWM_PER);
    HRTIM_SlaveSetCompare(HRTIM1, pwm_chennel, HRTIM_COMPAREUNIT_4, PWM_PER_0_5 + duty * 0.5f * PWM_PER);
}
inline void my_pwm_fre_update(float fre, uint32 pwm_chennel)
{
    uint32 PWM_per = 1152e6 / fre;
    HRTIM1->HRTIM_TIMERx[pwm_chennel].PERxR = PWM_per;
    /*
    //  if (fre <= 37000)
    //  {
    //  PWM_per = 1152e6 / fre;
    //  HRTIM1->HRTIM_TIMERx[pwm_chennel].PERxR = PWM_per;
    //  HRTIM1->HRTIM_TIMERx[pwm_chennel].TIMxCR &= (uint32_t) ~(HRTIM_TIMCR_CK_PSC);
    //  HRTIM1->HRTIM_TIMERx[pwm_chennel].TIMxCR |= HRTIM_PRESCALERRATIO_MUL8;

    //  }
    //  else if (fre <= 71000)
    //  {
    //  PWM_per = 2304e6 / fre;
    //  HRTIM1->HRTIM_TIMERx[pwm_chennel].PERxR = PWM_per;
    //  HRTIM1->HRTIM_TIMERx[pwm_chennel].TIMxCR &= (uint32_t) ~(HRTIM_TIMCR_CK_PSC);
    //  HRTIM1->HRTIM_TIMERx[pwm_chennel].TIMxCR |= HRTIM_PRESCALERRATIO_MUL16;

    //  }
    //  else
    //  {
    //  PWM_per = 4608e6 / fre;
    //  HRTIM1->HRTIM_TIMERx[pwm_chennel].PERxR = PWM_per;
    //  HRTIM1->HRTIM_TIMERx[pwm_chennel].TIMxCR &= (uint32_t) ~(HRTIM_TIMCR_CK_PSC);
    //  HRTIM1->HRTIM_TIMERx[pwm_chennel].TIMxCR |= HRTIM_PRESCALERRATIO_MUL32;
    //  }
    */
    HRTIM_SlaveSetCompare(HRTIM1, pwm_chennel, HRTIM_COMPAREUNIT_1, 0.25f * PWM_per);
    HRTIM_SlaveSetCompare(HRTIM1, pwm_chennel, HRTIM_COMPAREUNIT_4, 0.75f * PWM_per);
}

inline void my_delay_update(float duty, uint32 pwm_chennel)
{
    HRTIM_SlaveSetCompare(HRTIM1, pwm_chennel, HRTIM_COMPAREUNIT_1, (0.001f + 0.499f * duty) * PWM_PER);
    HRTIM_SlaveSetCompare(HRTIM1, pwm_chennel, HRTIM_COMPAREUNIT_4, (0.5f + 0.499f * duty) * PWM_PER);
}

void Dac1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    DAC_InitTypeDef DAC_InitType;
    RCC_APB2PeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE); // 使能PORTA通道时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);  // 使能DAC通道时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;            // 端口配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;         // 模拟输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    DAC_InitType.DAC_Trigger = DAC_Trigger_None; // 不使用触发功能 TEN1=0
    DAC_InitType.DAC_WaveGeneration = DAC_WaveGeneration_None;
    DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
    DAC_InitType.DAC_Buffer_Switch = DAC_BufferSwitch_Disable;
    DAC_Init(DAC1, DAC_Channel_1, &DAC_InitType);
    DAC_Cmd(DAC1, DAC_Channel_1, ENABLE);
    DAC_SetChannel1Data(DAC1, DAC_Align_12b_R, 0);
}
void my_system_config(void)
{
    SysTick_Config(SystemCoreClock / 1000);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
}
void PWM_ClearITPendingBit(void)
{
    HRTIM_ClearITPendingBit(HRTIM1, HRTIM_TIMERINDEX_MASTER, HRTIM_TIM_FLAG_REP);
}

u16 get_middle_num_adc(u16 temp1, u16 temp2, u16 temp3)
{
    if (temp1 > temp2)
    {
        if (temp2 > temp3)
            return temp2;
        else
            if (temp3 > temp1)
                return temp1;
            else
                return temp3;
    }
    else
    {
        if (temp2 < temp3)
            return temp2;
        else
            if (temp3 < temp1)
                return temp1;
            else
                return temp3;
    }
}

int main(void)
{
    my_board_init();

    while (1)
    {
        main_circle_func();
    }
}
