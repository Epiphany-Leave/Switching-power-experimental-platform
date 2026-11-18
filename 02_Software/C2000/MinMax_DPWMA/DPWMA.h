#ifndef DPWMA_H
#define DPWMA_H

typedef struct
{
    float INA,INB,INC;
    float OUTA,OUTB,OUTC;
    float outZ;
}DPWMAPATH;

void DI_DPWMA_UPDATE(DPWMAPATH *STRG);

#endif
