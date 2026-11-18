#include "power_meas_sine_analyzer.h"



void   POWER_MEAS_SINE_ANALYZER_reset(POWER_MEAS_SINE_ANALYZER *v)
{
    v->vRms=0;
    v->vAvg=0;
    v->vEma=0;
    v->acFreq=0;
    v->iRms=0;
    v->pRms=0;
    v->vaRms=0;
    v->powerFactor=0;
    v->zcd=0;
    v->vSum=0;
    v->vSqrSum=0;
    v->iSqrSum=0;
    v->pSum=0;
    v->vaSumMul=0;
    v->vNorm=0;
    v->iNorm=0;
    v->prevSign=0;
    v->currSign=0;
    v->nSamples=0;
    v->nSamplesMin = 0;
    v->nSamplesMax = 0;
    v->inverse_nSamples=0;
    v->sqrt_inverse_nSamples=0;
    v->pRmsSumMul=0;
    v->acFreqSum=0;
    v->acFreqAvg=0;
    v->jitterCount=0;
    v->emaFilterMultiplier=0;
}

//! \brief Configures the power measurment module
//! \param *v The POWER_MEAS_SINE_ANALYZER structure pointer
//! \param isrFrequency Frequency at which SPLL module is run
//! \param threshold Threshold value to avoid zero crossing issues
//! \param gridMaxFreq Max grid frequency
//! \param gridMinFreq Min grid frequency
//! \return None
//!
void   POWER_MEAS_SINE_ANALYZER_config(POWER_MEAS_SINE_ANALYZER *v,
                                                   float isrFrequency,
                                                   float threshold,
                                                   float gridMaxFreq,
                                                   float gridMinFreq)
{
    v->sampleFreq = (float)(isrFrequency);
    v->threshold = (float)(threshold);
    v->nSamplesMax=isrFrequency/gridMinFreq;
    v->nSamplesMin=isrFrequency/gridMaxFreq;
    v->emaFilterMultiplier=2.0f/isrFrequency;
}

//! \brief Perform calculations using the POWER_MEAS_SINE_ANALYZER module
//! \param *v The POWER_MEAS_SINE_ANALYZER structure pointer
//! \return None
//!
void   POWER_MEAS_SINE_ANALYZER_run(POWER_MEAS_SINE_ANALYZER *v)
{
     arm_abs_f32( (float32_t*)&(v->v),(float32_t*)&(v->vNorm),1);
	   arm_abs_f32( (float32_t*)&(v->i),(float32_t*)&(v->iNorm),1);
	
	  //v->vNorm = fabsf(v->v);
   // v->iNorm = fabsf(v->i);
    v->currSign = ( v->v > v->threshold) ? 1 : 0;
    v->nSamples++;
    v->vSum = v->vSum+v->vNorm;
    v->vSqrSum = v->vSqrSum+(v->vNorm*v->vNorm);
    v->vEma = v->vEma+(v->emaFilterMultiplier*(v->vNorm - v->vEma));
    v->iSqrSum = v->iSqrSum+(v->iNorm*v->iNorm);
    v->pSum = v->pSum+(v->i*v->v);
    v->zcd=0;

    if((v->prevSign != v->currSign) && (v->currSign == 1))
    {
        //
        // check if the nSamples are in the ball park of a real frequency
        // that can be on the grid, this is done by comparing the nSamples
        // with the max value and min value it can be for the 
        // AC Grid Connection these Max and Min are initialized by the 
        // user in the code
        //
        if(v->nSamplesMin < v->nSamples )
        {
            v->zcd=1;
            v->inverse_nSamples = (1.0f)/(v->nSamples);
					
					 arm_sqrt_f32((float32_t)v->inverse_nSamples,(float32_t*)&(v->sqrt_inverse_nSamples));
         //   v->sqrt_inverse_nSamples = sqrtf(v->inverse_nSamples);
            v->vAvg = (v->vSum*v->inverse_nSamples);
					arm_sqrt_f32((float32_t)v->vSqrSum,(float32_t*)&(v->internum));
					v->vRms=v->sqrt_inverse_nSamples*v->internum;
           // v->vRms = sqrtf(v->vSqrSum)*v->sqrt_inverse_nSamples;
					 arm_sqrt_f32((float32_t)v->iSqrSum,(float32_t*)&(v->internum));
					v->iRms=v->internum*v->sqrt_inverse_nSamples;
           // v->iRms = sqrtf(v->iSqrSum)*v->sqrt_inverse_nSamples;
            v->pRmsSumMul = v->pRmsSumMul + (v->pSum*v->inverse_nSamples);
            v->vaSumMul = v->vaSumMul + v->vRms*v->iRms;
            v->acFreq = (v->sampleFreq*v->inverse_nSamples);
            v->acFreqSum = v->acFreqSum + v->acFreq;

            v->slewPowerUpdate++;

            if(v->slewPowerUpdate >= 100)
            {
                v->slewPowerUpdate=0;
                v->pRms = (v->pRmsSumMul*(0.01f));
                v->pRmsSumMul = 0;
                v->vaRms = v->vaSumMul * (0.01f);
                v->vaSumMul = 0;
                v->powerFactor=v->pRms/v->vaRms;
                v->acFreqAvg=v->acFreqSum*0.01f;
                v->acFreqSum=0;
            }

            v->jitterCount=0;

            v->nSamples=0;
            v->vSum=0;
            v->vSqrSum=0;
            v->iSqrSum=0;
            v->pSum =0;
        }
        else
        {
            //
            // otherwise it may be jitter ignore this reading
            // but count the number of jitters you are getting
            // but do not count to infinity as then when the grid comes back
            // it will take too much time to wind down the jitter count
            //
            if(v->jitterCount<30)
            {
                v->jitterCount++;
            }
            v->nSamples=0;
        }
    }

    if(v->nSamples>v->nSamplesMax || v->jitterCount>20)
    {
        //
        // most certainly the AC voltage is not present
        //
        v->vRms = 0;
        v->vAvg = 0;
        v->vEma = 0;
        v->acFreq=0;
        v->iRms = 0;
        v->pRms = 0;
        v->vaRms =0;
        v->powerFactor=0;

        v->zcd=0;
        v->vSum=0;
        v->vSqrSum=0;
        v->iSqrSum=0;
        v->pSum=0;
        v->vaSumMul=0;
        v->pRmsSumMul = 0;
        v->acFreqAvg = 0;
        v->acFreqSum =0 ;
        v->nSamples=0;
        v->jitterCount=0;
    }

    v->prevSign = v->currSign;
}
