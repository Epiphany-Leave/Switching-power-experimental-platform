#include "DPWMA.h"

void DI_DPWMA_UPDATE(DPWMAPATH *STRG)
{
    static float A,B,C,min,max;
    //最小值部分A
    (STRG->INA>0.0)?(A=1.001-STRG->INA):(A=-STRG->INA);
    (STRG->INB>0.0)?(B=1.001-STRG->INB):(B=-STRG->INB);
    (STRG->INC>0.0)?(C=1.001-STRG->INC):(C=-STRG->INC);
    //minmax解算
    (A<B)?(min=A,max=B):(min=B,max=A);
    (min>C)?(min=C):((max<C)?max=C:0);
    max=1.001-max;

    if(min<=max) STRG->outZ=min;
    else STRG->outZ=-max;
    STRG->OUTA=STRG->INA+STRG->outZ;
    STRG->OUTB=STRG->INB+STRG->outZ;
    STRG->OUTC=STRG->INC+STRG->outZ;
}
