#ifndef RTW_HEADER_ACDCACsummarycircuit_acc_h_
#define RTW_HEADER_ACDCACsummarycircuit_acc_h_
#ifndef ACDCACsummarycircuit_acc_COMMON_INCLUDES_
#define ACDCACsummarycircuit_acc_COMMON_INCLUDES_
#include <stdlib.h>
#define S_FUNCTION_NAME simulink_only_sfcn
#define S_FUNCTION_LEVEL 2
#ifndef RTW_GENERATED_S_FUNCTION
#define RTW_GENERATED_S_FUNCTION
#endif
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#endif
#include "ACDCACsummarycircuit_acc_types.h"
#include <stddef.h>
#include <float.h>
#include "mwmathutil.h"
#include <string.h>
#include "rt_defines.h"
#include "rt_nonfinite.h"
typedef struct { real_T B_2_222_1688 ; real_T B_2_223_1696 ; }
B_PR_ACDCACsummarycircuit_T ; typedef struct { int32_T PR_sysIdxToRun ;
char_T pad_PR_sysIdxToRun [ 4 ] ; } DW_PR_ACDCACsummarycircuit_T ; typedef
struct { real_T TransferFcn_CSTATE_n [ 2 ] ; } X_PR_ACDCACsummarycircuit_T ;
typedef struct { real_T TransferFcn_CSTATE_n [ 2 ] ; }
XDot_PR_ACDCACsummarycircuit_T ; typedef struct { boolean_T
TransferFcn_CSTATE_n [ 2 ] ; } XDis_PR_ACDCACsummarycircuit_T ; typedef
struct { real_T B_6_209_1584 ; real_T B_6_210_1592 ; real_T B_6_211_1600 ;
real_T B_6_212_1608 ; real_T B_6_213_1616 ; real_T B_6_214_1624 ; real_T
B_6_215_1632 ; real_T B_6_216_1640 ; real_T B_6_217_1648 ; real_T
B_6_218_1656 ; real_T B_6_219_1664 ; } B_RMS_ACDCACsummarycircuit_T ; typedef
struct { real_T Memory_PreviousInput ; real_T Memory_PreviousInput_n ; struct
{ real_T modelTStart ; } TransportDelay_RWORK ; struct { real_T modelTStart ;
} TransportDelay_RWORK_m ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay_PWORK ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay_PWORK_e ; int32_T RMS_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun_j ; struct { int_T Tail ; int_T
Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay_IWORK ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay_IWORK_d ; int8_T
RMS_SubsysRanBC ; boolean_T RMS_MODE ; char_T pad_RMS_MODE [ 2 ] ; }
DW_RMS_ACDCACsummarycircuit_T ; typedef struct { real_T integrator_CSTATE_f ;
real_T integrator_CSTATE_d ; } X_RMS_ACDCACsummarycircuit_T ; typedef struct
{ real_T integrator_CSTATE_f ; real_T integrator_CSTATE_d ; }
XDot_RMS_ACDCACsummarycircuit_T ; typedef struct { boolean_T
integrator_CSTATE_f ; boolean_T integrator_CSTATE_d ; }
XDis_RMS_ACDCACsummarycircuit_T ; typedef struct { real_T B_8_203_1536 ;
real_T B_8_204_1544 ; real_T B_8_205_1552 ; real_T B_8_206_1560 ; real_T
B_8_207_1568 ; real_T B_8_208_1576 ; } B_TrueRMS_ACDCACsummarycircuit_T ;
typedef struct { real_T Memory_PreviousInput ; struct { real_T modelTStart ;
} TransportDelay_RWORK ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay_PWORK ; int32_T TrueRMS_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun ; struct { int_T Tail ; int_T Head
; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay_IWORK ; int8_T TrueRMS_SubsysRanBC ; boolean_T TrueRMS_MODE ;
char_T pad_TrueRMS_MODE [ 2 ] ; } DW_TrueRMS_ACDCACsummarycircuit_T ; typedef
struct { real_T integrator_CSTATE_no ; } X_TrueRMS_ACDCACsummarycircuit_T ;
typedef struct { real_T integrator_CSTATE_no ; }
XDot_TrueRMS_ACDCACsummarycircuit_T ; typedef struct { boolean_T
integrator_CSTATE_no ; } XDis_TrueRMS_ACDCACsummarycircuit_T ; typedef struct
{ real_T B_31_0_0 ; real_T B_31_1_8 [ 19 ] ; real_T B_31_20_160 [ 14 ] ;
real_T B_31_34_272 ; real_T B_31_35_280 ; real_T B_31_36_288 ; real_T
B_31_37_296 ; real_T B_31_38_304 ; real_T B_31_39_312 ; real_T B_31_40_320 ;
real_T B_31_41_328 ; real_T B_31_42_336 ; real_T B_31_43_344 ; real_T
B_31_44_352 ; real_T B_31_45_360 ; real_T B_31_46_368 ; real_T B_31_47_376 ;
real_T B_31_48_384 ; real_T B_31_49_392 ; real_T B_31_50_400 ; real_T
B_31_51_408 ; real_T B_31_52_416 ; real_T B_31_53_424 ; real_T B_31_54_432 ;
real_T B_31_55_440 ; real_T B_31_56_448 ; real_T B_31_57_456 ; real_T
B_31_58_464 [ 2 ] ; real_T B_31_60_480 ; real_T B_31_61_488 ; real_T
B_31_62_496 ; real_T B_31_63_504 ; real_T B_31_64_512 ; real_T B_31_65_520 ;
real_T B_31_66_528 ; real_T B_31_67_536 ; real_T B_31_68_544 ; real_T
B_31_69_552 ; real_T B_31_70_560 ; real_T B_31_71_568 ; real_T B_31_72_576 ;
real_T B_31_73_584 [ 2 ] ; real_T B_31_75_600 ; real_T B_31_76_608 ; real_T
B_31_77_616 ; real_T B_31_78_624 ; real_T B_31_79_632 ; real_T B_31_80_640 ;
real_T B_31_81_648 ; real_T B_31_82_656 ; real_T B_31_83_664 ; real_T
B_31_84_672 ; real_T B_31_85_680 ; real_T B_31_86_688 ; real_T B_31_87_696 ;
real_T B_31_88_704 ; real_T B_31_89_712 ; real_T B_31_90_720 ; real_T
B_31_91_728 ; real_T B_31_92_736 ; real_T B_31_93_744 ; real_T B_31_94_752 ;
real_T B_31_95_760 ; real_T B_31_96_768 [ 14 ] ; real_T B_31_110_880 ; real_T
B_31_111_888 ; real_T B_31_112_896 ; real_T B_31_113_904 ; real_T
B_31_114_912 ; real_T B_31_115_920 ; real_T B_31_116_928 ; real_T
B_31_117_936 ; real_T B_31_118_944 ; real_T B_31_119_952 ; real_T
B_31_120_960 ; real_T B_1_121_968 ; boolean_T B_31_122_976 ; boolean_T
B_31_123_977 ; boolean_T B_31_124_978 ; boolean_T B_31_125_979 ; boolean_T
B_31_126_980 ; boolean_T B_31_127_981 ; boolean_T B_31_128_982 ; boolean_T
B_31_129_983 ; boolean_T B_31_130_984 ; boolean_T B_31_131_985 ; boolean_T
B_31_132_986 ; boolean_T B_31_133_987 ; boolean_T B_31_134_988 ; char_T
pad_B_31_134_988 [ 3 ] ; B_TrueRMS_ACDCACsummarycircuit_T TrueRMS_f ;
B_RMS_ACDCACsummarycircuit_T RMS_ge ; B_TrueRMS_ACDCACsummarycircuit_T
TrueRMS_o ; B_RMS_ACDCACsummarycircuit_T RMS_g ;
B_TrueRMS_ACDCACsummarycircuit_T TrueRMS_k ; B_RMS_ACDCACsummarycircuit_T
RMS_i ; B_TrueRMS_ACDCACsummarycircuit_T TrueRMS_i ;
B_RMS_ACDCACsummarycircuit_T RMS_l ; B_TrueRMS_ACDCACsummarycircuit_T TrueRMS
; B_RMS_ACDCACsummarycircuit_T RMS ; B_PR_ACDCACsummarycircuit_T PR_i ;
B_PR_ACDCACsummarycircuit_T PR ; } B_ACDCACsummarycircuit_T ; typedef struct
{ real_T StateSpace_DSTATE [ 4 ] ; real_T Memory_PreviousInput ; real_T
Memory_PreviousInput_p ; real_T Memory_PreviousInput_pe ; struct { real_T
modelTStart ; } T_RWORK ; struct { real_T modelTStart ; } T1_RWORK ; struct {
real_T modelTStart ; } T_RWORK_a ; struct { real_T modelTStart ; } T1_RWORK_j
; struct { real_T modelTStart ; } TransportDelay_RWORK ; struct { real_T
modelTStart ; } TransportDelay_RWORK_n ; struct { real_T modelTStart ; }
T_RWORK_d ; struct { real_T modelTStart ; } T1_RWORK_g ; struct { real_T
modelTStart ; } T_RWORK_j ; struct { real_T modelTStart ; } T1_RWORK_n ;
struct { real_T modelTStart ; } TransportDelay_RWORK_o ; struct { void * AS ;
void * BS ; void * CS ; void * DS ; void * DX_COL ; void * BD_COL ; void *
TMP1 ; void * TMP2 ; void * XTMP ; void * SWITCH_STATUS ; void *
SWITCH_STATUS_INIT ; void * SW_CHG ; void * G_STATE ; void * USWLAST ; void *
XKM12 ; void * XKP12 ; void * XLAST ; void * ULAST ; void * IDX_SW_CHG ; void
* Y_SWITCH ; void * SWITCH_TYPES ; void * IDX_OUT_SW ; void *
SWITCH_TOPO_SAVED_IDX ; void * SWITCH_MAP ; } StateSpace_PWORK ; void *
Scope_PWORK ; void * Scope3_PWORK [ 2 ] ; void * Scope4_PWORK ; void *
Scope5_PWORK [ 2 ] ; void * Scope6_PWORK [ 2 ] ; void * Scope7_PWORK [ 2 ] ;
void * Scope8_PWORK [ 2 ] ; struct { void * TUbufferPtrs [ 2 ] ; } T_PWORK ;
struct { void * TUbufferPtrs [ 2 ] ; } T1_PWORK ; struct { void *
TUbufferPtrs [ 2 ] ; } T_PWORK_f ; struct { void * TUbufferPtrs [ 2 ] ; }
T1_PWORK_j ; struct { void * TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK ;
struct { void * TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK_f ; struct { void
* TUbufferPtrs [ 2 ] ; } T_PWORK_fh ; struct { void * TUbufferPtrs [ 2 ] ; }
T1_PWORK_h ; struct { void * TUbufferPtrs [ 2 ] ; } T_PWORK_h ; struct { void
* TUbufferPtrs [ 2 ] ; } T1_PWORK_hj ; void * _PWORK ; struct { void *
TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK_l ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun_a ; int32_T PFC_sysIdxToRun ;
int32_T TmpAtomicSubsysAtSwitchInport1_sysIdxToRun_l ; int_T StateSpace_IWORK
[ 11 ] ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } T_IWORK ; struct { int_T Tail ;
int_T Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
T1_IWORK ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } T_IWORK_f ; struct { int_T Tail ;
int_T Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
T1_IWORK_h ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay_IWORK ; struct {
int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay_IWORK_o ; struct { int_T Tail ; int_T Head ;
int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; } T_IWORK_o ;
struct { int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } T1_IWORK_hc ; struct { int_T Tail ; int_T Head ; int_T Last
; int_T CircularBufSize ; int_T MaxNewBufSize ; } T_IWORK_fa ; struct { int_T
Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize
; } T1_IWORK_c ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay_IWORK_h ; boolean_T
Memory_PreviousInput_b ; char_T pad_Memory_PreviousInput_b [ 7 ] ;
DW_TrueRMS_ACDCACsummarycircuit_T TrueRMS_f ; DW_RMS_ACDCACsummarycircuit_T
RMS_ge ; DW_TrueRMS_ACDCACsummarycircuit_T TrueRMS_o ;
DW_RMS_ACDCACsummarycircuit_T RMS_g ; DW_TrueRMS_ACDCACsummarycircuit_T
TrueRMS_k ; DW_RMS_ACDCACsummarycircuit_T RMS_i ;
DW_TrueRMS_ACDCACsummarycircuit_T TrueRMS_i ; DW_RMS_ACDCACsummarycircuit_T
RMS_l ; DW_TrueRMS_ACDCACsummarycircuit_T TrueRMS ;
DW_RMS_ACDCACsummarycircuit_T RMS ; DW_PR_ACDCACsummarycircuit_T PR_i ;
DW_PR_ACDCACsummarycircuit_T PR ; } DW_ACDCACsummarycircuit_T ; typedef
struct { real_T _CSTATE ; real_T TransferFcn_CSTATE [ 2 ] ; real_T
Integrator_CSTATE ; real_T integ1_CSTATE ; real_T Integ2_CSTATE ; real_T
integ1_CSTATE_m ; real_T Integ2_CSTATE_a ; real_T integrator_CSTATE ; real_T
integrator_CSTATE_n ; real_T integ1_CSTATE_p ; real_T Integ2_CSTATE_o ;
real_T integ1_CSTATE_i ; real_T Integ2_CSTATE_c ; real_T integrator_CSTATE_e
; X_TrueRMS_ACDCACsummarycircuit_T TrueRMS_f ; X_RMS_ACDCACsummarycircuit_T
RMS_ge ; X_TrueRMS_ACDCACsummarycircuit_T TrueRMS_o ;
X_RMS_ACDCACsummarycircuit_T RMS_g ; X_TrueRMS_ACDCACsummarycircuit_T
TrueRMS_k ; X_RMS_ACDCACsummarycircuit_T RMS_i ;
X_TrueRMS_ACDCACsummarycircuit_T TrueRMS_i ; X_RMS_ACDCACsummarycircuit_T
RMS_l ; X_TrueRMS_ACDCACsummarycircuit_T TrueRMS ;
X_RMS_ACDCACsummarycircuit_T RMS ; X_PR_ACDCACsummarycircuit_T PR_i ;
X_PR_ACDCACsummarycircuit_T PR ; } X_ACDCACsummarycircuit_T ; typedef struct
{ real_T _CSTATE ; real_T TransferFcn_CSTATE [ 2 ] ; real_T Integrator_CSTATE
; real_T integ1_CSTATE ; real_T Integ2_CSTATE ; real_T integ1_CSTATE_m ;
real_T Integ2_CSTATE_a ; real_T integrator_CSTATE ; real_T
integrator_CSTATE_n ; real_T integ1_CSTATE_p ; real_T Integ2_CSTATE_o ;
real_T integ1_CSTATE_i ; real_T Integ2_CSTATE_c ; real_T integrator_CSTATE_e
; XDot_TrueRMS_ACDCACsummarycircuit_T TrueRMS_f ;
XDot_RMS_ACDCACsummarycircuit_T RMS_ge ; XDot_TrueRMS_ACDCACsummarycircuit_T
TrueRMS_o ; XDot_RMS_ACDCACsummarycircuit_T RMS_g ;
XDot_TrueRMS_ACDCACsummarycircuit_T TrueRMS_k ;
XDot_RMS_ACDCACsummarycircuit_T RMS_i ; XDot_TrueRMS_ACDCACsummarycircuit_T
TrueRMS_i ; XDot_RMS_ACDCACsummarycircuit_T RMS_l ;
XDot_TrueRMS_ACDCACsummarycircuit_T TrueRMS ; XDot_RMS_ACDCACsummarycircuit_T
RMS ; XDot_PR_ACDCACsummarycircuit_T PR_i ; XDot_PR_ACDCACsummarycircuit_T PR
; } XDot_ACDCACsummarycircuit_T ; typedef struct { boolean_T _CSTATE ;
boolean_T TransferFcn_CSTATE [ 2 ] ; boolean_T Integrator_CSTATE ; boolean_T
integ1_CSTATE ; boolean_T Integ2_CSTATE ; boolean_T integ1_CSTATE_m ;
boolean_T Integ2_CSTATE_a ; boolean_T integrator_CSTATE ; boolean_T
integrator_CSTATE_n ; boolean_T integ1_CSTATE_p ; boolean_T Integ2_CSTATE_o ;
boolean_T integ1_CSTATE_i ; boolean_T Integ2_CSTATE_c ; boolean_T
integrator_CSTATE_e ; XDis_TrueRMS_ACDCACsummarycircuit_T TrueRMS_f ;
XDis_RMS_ACDCACsummarycircuit_T RMS_ge ; XDis_TrueRMS_ACDCACsummarycircuit_T
TrueRMS_o ; XDis_RMS_ACDCACsummarycircuit_T RMS_g ;
XDis_TrueRMS_ACDCACsummarycircuit_T TrueRMS_k ;
XDis_RMS_ACDCACsummarycircuit_T RMS_i ; XDis_TrueRMS_ACDCACsummarycircuit_T
TrueRMS_i ; XDis_RMS_ACDCACsummarycircuit_T RMS_l ;
XDis_TrueRMS_ACDCACsummarycircuit_T TrueRMS ; XDis_RMS_ACDCACsummarycircuit_T
RMS ; XDis_PR_ACDCACsummarycircuit_T PR_i ; XDis_PR_ACDCACsummarycircuit_T PR
; } XDis_ACDCACsummarycircuit_T ; typedef struct { const real_T B_31_474_3584
; } ConstB_ACDCACsummarycircuit_T ;
#define ACDCACsummarycircuit_rtC(S) ((ConstB_ACDCACsummarycircuit_T *) _ssGetConstBlockIO(S))
struct P_PR_ACDCACsummarycircuit_T_ { real_T P_0 ; real_T P_1 ; real_T P_2 [
2 ] ; real_T P_3 [ 2 ] ; real_T P_4 ; real_T P_5 ; } ; struct
P_RMS_ACDCACsummarycircuit_T_ { real_T P_0 ; real_T P_1 ; real_T P_2 ; real_T
P_3 ; real_T P_4 ; real_T P_5 ; real_T P_6 ; real_T P_7 ; real_T P_8 ; real_T
P_9 ; real_T P_10 ; real_T P_11 ; real_T P_12 ; real_T P_13 ; real_T P_14 ;
real_T P_15 ; real_T P_16 ; real_T P_17 ; real_T P_18 ; real_T P_19 ; real_T
P_20 ; real_T P_21 ; } ; struct P_TrueRMS_ACDCACsummarycircuit_T_ { real_T
P_0 ; real_T P_1 ; real_T P_2 ; real_T P_3 ; real_T P_4 ; real_T P_5 ; real_T
P_6 ; real_T P_7 ; real_T P_8 ; } ; struct P_ACDCACsummarycircuit_T_ { real_T
P_0 ; real_T P_1 ; real_T P_2 ; real_T P_3 ; real_T P_4 ; real_T P_5 ; real_T
P_6 ; real_T P_7 ; real_T P_8 [ 2 ] ; real_T P_9 [ 16 ] ; real_T P_10 [ 2 ] ;
real_T P_11 [ 84 ] ; real_T P_12 [ 2 ] ; real_T P_13 [ 76 ] ; real_T P_14 [ 2
] ; real_T P_15 [ 399 ] ; real_T P_16 [ 2 ] ; real_T P_17 [ 4 ] ; real_T P_18
; real_T P_19 ; real_T P_20 ; real_T P_21 ; real_T P_22 [ 3 ] ; real_T P_23 [
3 ] ; real_T P_24 ; real_T P_25 ; real_T P_26 ; real_T P_27 [ 2 ] ; real_T
P_28 [ 2 ] ; real_T P_29 ; real_T P_30 ; real_T P_31 ; real_T P_32 ; real_T
P_33 ; real_T P_34 ; real_T P_35 ; real_T P_36 [ 3 ] ; real_T P_37 [ 3 ] ;
real_T P_38 ; real_T P_39 ; real_T P_40 ; real_T P_41 ; real_T P_42 ; real_T
P_43 ; real_T P_44 ; real_T P_45 ; real_T P_46 ; real_T P_47 ; real_T P_48 ;
real_T P_49 ; real_T P_50 ; real_T P_51 ; real_T P_52 ; real_T P_53 ; real_T
P_54 ; real_T P_55 ; real_T P_56 ; real_T P_57 ; real_T P_58 ; real_T P_59 ;
real_T P_60 ; real_T P_61 ; real_T P_62 ; real_T P_63 ; real_T P_64 ; real_T
P_65 ; real_T P_66 ; real_T P_67 ; real_T P_68 ; real_T P_69 ; real_T P_70 ;
real_T P_71 ; real_T P_72 ; real_T P_73 ; real_T P_74 ; real_T P_75 ; real_T
P_76 ; real_T P_77 ; real_T P_78 ; real_T P_79 ; real_T P_80 ; real_T P_81 ;
real_T P_82 ; real_T P_83 ; real_T P_84 ; real_T P_85 ; real_T P_86 ; real_T
P_87 ; real_T P_88 ; real_T P_89 ; real_T P_90 ; real_T P_91 ; real_T P_92 ;
real_T P_93 ; real_T P_94 ; real_T P_95 ; real_T P_96 ; real_T P_97 ; real_T
P_98 ; real_T P_99 ; real_T P_100 ; real_T P_101 ; real_T P_102 ; real_T
P_103 ; real_T P_104 ; real_T P_105 ; real_T P_106 ; real_T P_107 ; real_T
P_108 ; real_T P_109 ; real_T P_110 ; real_T P_111 ; real_T P_112 ; real_T
P_113 ; real_T P_114 ; real_T P_115 ; real_T P_116 ; real_T P_117 ; real_T
P_118 ; real_T P_119 ; real_T P_120 ; real_T P_121 ; real_T P_122 ; real_T
P_123 ; real_T P_124 ; real_T P_125 ; real_T P_126 ; real_T P_127 ; real_T
P_128 ; real_T P_129 ; real_T P_130 ; real_T P_131 ; real_T P_132 ; real_T
P_133 ; real_T P_134 ; real_T P_135 ; real_T P_136 [ 14 ] ; real_T P_137 ;
real_T P_138 ; real_T P_139 ; real_T P_140 ; real_T P_141 ; real_T P_142 ;
real_T P_143 ; real_T P_144 ; real_T P_145 ; real_T P_146 ; real_T P_147 ;
real_T P_148 ; real_T P_149 ; real_T P_150 ; real_T P_151 ; real_T P_152 ;
boolean_T P_153 ; char_T pad_P_153 [ 7 ] ; P_TrueRMS_ACDCACsummarycircuit_T
TrueRMS_f ; P_RMS_ACDCACsummarycircuit_T RMS_ge ;
P_TrueRMS_ACDCACsummarycircuit_T TrueRMS_o ; P_RMS_ACDCACsummarycircuit_T
RMS_g ; P_TrueRMS_ACDCACsummarycircuit_T TrueRMS_k ;
P_RMS_ACDCACsummarycircuit_T RMS_i ; P_TrueRMS_ACDCACsummarycircuit_T
TrueRMS_i ; P_RMS_ACDCACsummarycircuit_T RMS_l ;
P_TrueRMS_ACDCACsummarycircuit_T TrueRMS ; P_RMS_ACDCACsummarycircuit_T RMS ;
P_PR_ACDCACsummarycircuit_T PR_i ; P_PR_ACDCACsummarycircuit_T PR ; } ;
extern P_ACDCACsummarycircuit_T ACDCACsummarycircuit_rtDefaultP ; extern
const ConstB_ACDCACsummarycircuit_T ACDCACsummarycircuit_rtInvariant ;
#endif
