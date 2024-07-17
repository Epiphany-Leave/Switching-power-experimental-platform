#ifndef POWERMEAS
#define POWERMEAS	 
#include "my_board.h"
#include "arm_math.h" 
typedef  volatile struct POWER_MEAS_SINE_ANALYZER{
    float v;           //!< Input: Voltage Sine Signal
    float i;           //!< Input Current Signal
    float sampleFreq;  //!< Input: Signal Sampling Freq
    float threshold;   //!< Input: Voltage level corresponding to zero i/p
    float vRms;        //!< Output: RMS Value
    float vAvg;        //!< Output: Average Value
    float vEma;        //!< Output: Exponential Moving Average Value
    float acFreq;      //!< Output: Signal Freq
    float acFreqAvg;   //!< Output: Signal Freq
    float iRms;        //!< Output: RMS Value of current
    float pRms;        //!< Output: RMS Value of input power
    float vaRms;       //!< Output: RMS VA
    float powerFactor; //!< Output: powerFactor
    int16_t  zcd;          //!< Output: Zero Cross detected
    
    float vSum;        //!< Internal : running sum for vac calculation over one sine cycles
    float vSqrSum;     //!< Internal : running sum for vacc square calculation over one sine cycle
    float iSqrSum;     //!< Internal : running sum for Iacc_rms calculation over one sine cycle
    float acFreqSum;   //!< Internal : running sum of acFreq
    float pSum;        //!< Internal : running sum for Pacc_rms calculation over one sine cycle
    float vaSumMul;    //!< Internal : running sum for Pacc_rms calculation over one sine cycle
    float vNorm;       //!< Internal: Normalized value of the input voltage
    float iNorm;       //!< Internal: Normalized value of the input current
    int16_t  prevSign;     //!< Internal: Flag to detect ZCD
    int16_t  currSign;     //!< Internal: Flag to detect ZCD
    int32_t  nSamples;     //!< Internal: No of samples in one cycle of the sine wave
    int32_t  nSamplesMin;  //!< Internal: Lowerbound for no of samples in one sine wave cycle
    int32_t  nSamplesMax;  //!< Internal: Upperbound for no of samples in one sine wave cycle
    float inverse_nSamples; //!< Internal: 1/( No of samples in one cycle of the sine wave)
    float sqrt_inverse_nSamples; //!< Internal: sqrt(1/( No of samples in one cycle of the sine wave))
    int16_t  slewPowerUpdate; //!< Internal: used to slew update of the power value
    float pRmsSumMul; //!< Internal: used to sum Pac value over multiple sine cycles (100)
    int16_t jitterCount; //!< Internal: used to store jitter information due to noise on input
    float emaFilterMultiplier;  //!< Internal: multiplier value used for the exponential moving average filter
		float internum;
} POWER_MEAS_SINE_ANALYZER;

void   POWER_MEAS_SINE_ANALYZER_reset(POWER_MEAS_SINE_ANALYZER *v);
void   POWER_MEAS_SINE_ANALYZER_config(POWER_MEAS_SINE_ANALYZER *v,
                                                   float isrFrequency,
                                                   float threshold,
                                                   float gridMaxFreq,
                                                   float gridMinFreq);

 void POWER_MEAS_SINE_ANALYZER_run(POWER_MEAS_SINE_ANALYZER *v);

#endif
