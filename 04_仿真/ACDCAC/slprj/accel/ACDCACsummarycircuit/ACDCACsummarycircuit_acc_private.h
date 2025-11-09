#ifndef RTW_HEADER_ACDCACsummarycircuit_acc_private_h_
#define RTW_HEADER_ACDCACsummarycircuit_acc_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "ACDCACsummarycircuit_acc.h"
#include "ACDCACsummarycircuit_acc_types.h"
#if !defined(ss_VALIDATE_MEMORY)
#define ss_VALIDATE_MEMORY(S, ptr)     if(!(ptr)) {\
    ssSetErrorStatus(S, RT_MEMORY_ALLOCATION_ERROR);\
    }
#endif
#if !defined(rt_FREE)
#if !defined(_WIN32)
#define rt_FREE(ptr)     if((ptr) != (NULL)) {\
    free((ptr));\
    (ptr) = (NULL);\
    }
#else
#define rt_FREE(ptr)     if((ptr) != (NULL)) {\
    free((void *)(ptr));\
    (ptr) = (NULL);\
    }
#endif
#endif
#ifndef __RTW_UTFREE__
extern void * utMalloc ( size_t ) ; extern void utFree ( void * ) ;
#endif
boolean_T ACDCACsummarycircuit_acc_rt_TDelayUpdateTailOrGrowBuf ( int_T *
bufSzPtr , int_T * tailPtr , int_T * headPtr , int_T * lastPtr , real_T
tMinusDelay , real_T * * uBufPtr , boolean_T isfixedbuf , boolean_T
istransportdelay , int_T * maxNewBufSzPtr ) ; real_T
ACDCACsummarycircuit_acc_rt_TDelayInterpolate ( real_T tMinusDelay , real_T
tStart , real_T * uBuf , int_T bufSz , int_T * lastIdx , int_T oldestIdx ,
int_T newIdx , real_T initOutput , boolean_T discrete , boolean_T
minorStepAndTAtLastMajorOutput ) ; extern real_T look1_binlxpw ( real_T u0 ,
const real_T bp0 [ ] , const real_T table [ ] , uint32_T maxIndex ) ; void
ACDCACsummarycircuit_PR_Init ( SimStruct * S , X_PR_ACDCACsummarycircuit_T *
localX ) ; void ACDCACsummarycircuit_PR_Deriv ( SimStruct * S ,
B_PR_ACDCACsummarycircuit_T * localB , P_PR_ACDCACsummarycircuit_T * localP ,
X_PR_ACDCACsummarycircuit_T * localX , XDot_PR_ACDCACsummarycircuit_T *
localXdot ) ; void ACDCACsummarycircuit_PR ( SimStruct * S , real_T rtu_err ,
B_PR_ACDCACsummarycircuit_T * localB , P_PR_ACDCACsummarycircuit_T * localP ,
X_PR_ACDCACsummarycircuit_T * localX ) ; void ACDCACsummarycircuit_RMS_Init (
SimStruct * S , B_RMS_ACDCACsummarycircuit_T * localB ,
DW_RMS_ACDCACsummarycircuit_T * localDW , P_RMS_ACDCACsummarycircuit_T *
localP , X_RMS_ACDCACsummarycircuit_T * localX ) ; void
ACDCACsummarycircuit_RMS_Deriv ( SimStruct * S , B_RMS_ACDCACsummarycircuit_T
* localB , DW_RMS_ACDCACsummarycircuit_T * localDW ,
XDot_RMS_ACDCACsummarycircuit_T * localXdot ) ; void
ACDCACsummarycircuit_RMS_Disable ( SimStruct * S ,
DW_RMS_ACDCACsummarycircuit_T * localDW ) ; void
ACDCACsummarycircuit_RMS_Update ( SimStruct * S ,
B_RMS_ACDCACsummarycircuit_T * localB , DW_RMS_ACDCACsummarycircuit_T *
localDW , P_RMS_ACDCACsummarycircuit_T * localP ) ; void
ACDCACsummarycircuit_RMS ( SimStruct * S , boolean_T rtu_Enable , real_T
rtu_In , B_RMS_ACDCACsummarycircuit_T * localB ,
DW_RMS_ACDCACsummarycircuit_T * localDW , P_RMS_ACDCACsummarycircuit_T *
localP , X_RMS_ACDCACsummarycircuit_T * localX ,
XDis_RMS_ACDCACsummarycircuit_T * localXdis ) ; void
ACDCACsummarycircuit_TrueRMS_Init ( SimStruct * S ,
B_TrueRMS_ACDCACsummarycircuit_T * localB , DW_TrueRMS_ACDCACsummarycircuit_T
* localDW , P_TrueRMS_ACDCACsummarycircuit_T * localP ,
X_TrueRMS_ACDCACsummarycircuit_T * localX ) ; void
ACDCACsummarycircuit_TrueRMS_Deriv ( SimStruct * S ,
B_TrueRMS_ACDCACsummarycircuit_T * localB , DW_TrueRMS_ACDCACsummarycircuit_T
* localDW , XDot_TrueRMS_ACDCACsummarycircuit_T * localXdot ) ; void
ACDCACsummarycircuit_TrueRMS_Disable ( SimStruct * S ,
DW_TrueRMS_ACDCACsummarycircuit_T * localDW ) ; void
ACDCACsummarycircuit_TrueRMS_Update ( SimStruct * S ,
B_TrueRMS_ACDCACsummarycircuit_T * localB , DW_TrueRMS_ACDCACsummarycircuit_T
* localDW , P_TrueRMS_ACDCACsummarycircuit_T * localP ) ; void
ACDCACsummarycircuit_TrueRMS ( SimStruct * S , boolean_T rtu_Enable , real_T
rtu_In , B_TrueRMS_ACDCACsummarycircuit_T * localB ,
DW_TrueRMS_ACDCACsummarycircuit_T * localDW ,
P_TrueRMS_ACDCACsummarycircuit_T * localP , X_TrueRMS_ACDCACsummarycircuit_T
* localX , XDis_TrueRMS_ACDCACsummarycircuit_T * localXdis ) ; void
ACDCACsummarycircuit_PR_Term ( SimStruct * const S ) ; void
ACDCACsummarycircuit_RMS_Term ( SimStruct * const S ) ; void
ACDCACsummarycircuit_TrueRMS_Term ( SimStruct * const S ) ;
#endif
