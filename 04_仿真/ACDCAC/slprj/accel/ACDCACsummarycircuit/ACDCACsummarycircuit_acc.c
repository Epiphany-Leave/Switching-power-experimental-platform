#include "ACDCACsummarycircuit_acc.h"
#include "ACDCACsummarycircuit_acc_types.h"
#include "rtwtypes.h"
#include "ACDCACsummarycircuit_acc_private.h"
#include "mwmathutil.h"
#include <string.h>
#include "multiword_types.h"
#include <stdio.h>
#include "slexec_vm_simstruct_bridge.h"
#include "slexec_vm_zc_functions.h"
#include "slexec_vm_lookup_functions.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "simtarget/slSimTgtMdlrefSfcnBridge.h"
#include "simstruc.h"
#include "fixedpoint.h"
#define CodeFormat S-Function
#define AccDefine1 Accelerator_S-Function
#include "simtarget/slAccSfcnBridge.h"
#ifndef __RTW_UTFREE__  
extern void * utMalloc ( size_t ) ; extern void utFree ( void * ) ;
#endif
boolean_T ACDCACsummarycircuit_acc_rt_TDelayUpdateTailOrGrowBuf ( int_T *
bufSzPtr , int_T * tailPtr , int_T * headPtr , int_T * lastPtr , real_T
tMinusDelay , real_T * * uBufPtr , boolean_T isfixedbuf , boolean_T
istransportdelay , int_T * maxNewBufSzPtr ) { int_T testIdx ; int_T tail = *
tailPtr ; int_T bufSz = * bufSzPtr ; real_T * tBuf = * uBufPtr + bufSz ;
real_T * xBuf = ( NULL ) ; int_T numBuffer = 2 ; if ( istransportdelay ) {
numBuffer = 3 ; xBuf = * uBufPtr + 2 * bufSz ; } testIdx = ( tail < ( bufSz -
1 ) ) ? ( tail + 1 ) : 0 ; if ( ( tMinusDelay <= tBuf [ testIdx ] ) && !
isfixedbuf ) { int_T j ; real_T * tempT ; real_T * tempU ; real_T * tempX = (
NULL ) ; real_T * uBuf = * uBufPtr ; int_T newBufSz = bufSz + 1024 ; if (
newBufSz > * maxNewBufSzPtr ) { * maxNewBufSzPtr = newBufSz ; } tempU = (
real_T * ) utMalloc ( numBuffer * newBufSz * sizeof ( real_T ) ) ; if ( tempU
== ( NULL ) ) { return ( false ) ; } tempT = tempU + newBufSz ; if (
istransportdelay ) tempX = tempT + newBufSz ; for ( j = tail ; j < bufSz ; j
++ ) { tempT [ j - tail ] = tBuf [ j ] ; tempU [ j - tail ] = uBuf [ j ] ; if
( istransportdelay ) tempX [ j - tail ] = xBuf [ j ] ; } for ( j = 0 ; j <
tail ; j ++ ) { tempT [ j + bufSz - tail ] = tBuf [ j ] ; tempU [ j + bufSz -
tail ] = uBuf [ j ] ; if ( istransportdelay ) tempX [ j + bufSz - tail ] =
xBuf [ j ] ; } if ( * lastPtr > tail ) { * lastPtr -= tail ; } else { *
lastPtr += ( bufSz - tail ) ; } * tailPtr = 0 ; * headPtr = bufSz ; utFree (
uBuf ) ; * bufSzPtr = newBufSz ; * uBufPtr = tempU ; } else { * tailPtr =
testIdx ; } return ( true ) ; } real_T
ACDCACsummarycircuit_acc_rt_TDelayInterpolate ( real_T tMinusDelay , real_T
tStart , real_T * uBuf , int_T bufSz , int_T * lastIdx , int_T oldestIdx ,
int_T newIdx , real_T initOutput , boolean_T discrete , boolean_T
minorStepAndTAtLastMajorOutput ) { int_T i ; real_T yout , t1 , t2 , u1 , u2
; real_T * tBuf = uBuf + bufSz ; if ( ( newIdx == 0 ) && ( oldestIdx == 0 )
&& ( tMinusDelay > tStart ) ) return initOutput ; if ( tMinusDelay <= tStart
) return initOutput ; if ( ( tMinusDelay <= tBuf [ oldestIdx ] ) ) { if (
discrete ) { return ( uBuf [ oldestIdx ] ) ; } else { int_T tempIdx =
oldestIdx + 1 ; if ( oldestIdx == bufSz - 1 ) tempIdx = 0 ; t1 = tBuf [
oldestIdx ] ; t2 = tBuf [ tempIdx ] ; u1 = uBuf [ oldestIdx ] ; u2 = uBuf [
tempIdx ] ; if ( t2 == t1 ) { if ( tMinusDelay >= t2 ) { yout = u2 ; } else {
yout = u1 ; } } else { real_T f1 = ( t2 - tMinusDelay ) / ( t2 - t1 ) ;
real_T f2 = 1.0 - f1 ; yout = f1 * u1 + f2 * u2 ; } return yout ; } } if (
minorStepAndTAtLastMajorOutput ) { if ( newIdx != 0 ) { if ( * lastIdx ==
newIdx ) { ( * lastIdx ) -- ; } newIdx -- ; } else { if ( * lastIdx == newIdx
) { * lastIdx = bufSz - 1 ; } newIdx = bufSz - 1 ; } } i = * lastIdx ; if (
tBuf [ i ] < tMinusDelay ) { while ( tBuf [ i ] < tMinusDelay ) { if ( i ==
newIdx ) break ; i = ( i < ( bufSz - 1 ) ) ? ( i + 1 ) : 0 ; } } else { while
( tBuf [ i ] >= tMinusDelay ) { i = ( i > 0 ) ? i - 1 : ( bufSz - 1 ) ; } i =
( i < ( bufSz - 1 ) ) ? ( i + 1 ) : 0 ; } * lastIdx = i ; if ( discrete ) {
double tempEps = ( DBL_EPSILON ) * 128.0 ; double localEps = tempEps *
muDoubleScalarAbs ( tBuf [ i ] ) ; if ( tempEps > localEps ) { localEps =
tempEps ; } localEps = localEps / 2.0 ; if ( tMinusDelay >= ( tBuf [ i ] -
localEps ) ) { yout = uBuf [ i ] ; } else { if ( i == 0 ) { yout = uBuf [
bufSz - 1 ] ; } else { yout = uBuf [ i - 1 ] ; } } } else { if ( i == 0 ) {
t1 = tBuf [ bufSz - 1 ] ; u1 = uBuf [ bufSz - 1 ] ; } else { t1 = tBuf [ i -
1 ] ; u1 = uBuf [ i - 1 ] ; } t2 = tBuf [ i ] ; u2 = uBuf [ i ] ; if ( t2 ==
t1 ) { if ( tMinusDelay >= t2 ) { yout = u2 ; } else { yout = u1 ; } } else {
real_T f1 = ( t2 - tMinusDelay ) / ( t2 - t1 ) ; real_T f2 = 1.0 - f1 ; yout
= f1 * u1 + f2 * u2 ; } } return ( yout ) ; } real_T look1_binlxpw ( real_T
u0 , const real_T bp0 [ ] , const real_T table [ ] , uint32_T maxIndex ) {
real_T frac ; real_T yL_0d0 ; uint32_T bpIdx ; uint32_T iLeft ; uint32_T
iRght ; if ( u0 <= bp0 [ 0U ] ) { iLeft = 0U ; frac = ( u0 - bp0 [ 0U ] ) / (
bp0 [ 1U ] - bp0 [ 0U ] ) ; } else if ( u0 < bp0 [ maxIndex ] ) { bpIdx =
maxIndex >> 1U ; iLeft = 0U ; iRght = maxIndex ; while ( iRght - iLeft > 1U )
{ if ( u0 < bp0 [ bpIdx ] ) { iRght = bpIdx ; } else { iLeft = bpIdx ; }
bpIdx = ( iRght + iLeft ) >> 1U ; } frac = ( u0 - bp0 [ iLeft ] ) / ( bp0 [
iLeft + 1U ] - bp0 [ iLeft ] ) ; } else { iLeft = maxIndex - 1U ; frac = ( u0
- bp0 [ maxIndex - 1U ] ) / ( bp0 [ maxIndex ] - bp0 [ maxIndex - 1U ] ) ; }
yL_0d0 = table [ iLeft ] ; return ( table [ iLeft + 1U ] - yL_0d0 ) * frac +
yL_0d0 ; } void rt_ssGetBlockPath ( SimStruct * S , int_T sysIdx , int_T
blkIdx , char_T * * path ) { _ssGetBlockPath ( S , sysIdx , blkIdx , path ) ;
} void rt_ssSet_slErrMsg ( void * S , void * diag ) { SimStruct * castedS = (
SimStruct * ) S ; if ( ! _ssIsErrorStatusAslErrMsg ( castedS ) ) {
_ssSet_slErrMsg ( castedS , diag ) ; } else { _ssDiscardDiagnostic ( castedS
, diag ) ; } } void rt_ssReportDiagnosticAsWarning ( void * S , void * diag )
{ _ssReportDiagnosticAsWarning ( ( SimStruct * ) S , diag ) ; } void
rt_ssReportDiagnosticAsInfo ( void * S , void * diag ) {
_ssReportDiagnosticAsInfo ( ( SimStruct * ) S , diag ) ; } void
ACDCACsummarycircuit_PR_Init ( SimStruct * S , X_PR_ACDCACsummarycircuit_T *
localX ) { localX -> TransferFcn_CSTATE_n [ 0 ] = 0.0 ; localX ->
TransferFcn_CSTATE_n [ 1 ] = 0.0 ; } void ACDCACsummarycircuit_PR ( SimStruct
* S , real_T rtu_err , B_PR_ACDCACsummarycircuit_T * localB ,
P_PR_ACDCACsummarycircuit_T * localP , X_PR_ACDCACsummarycircuit_T * localX )
{ real_T u0 ; localB -> B_2_222_1688 = localP -> P_1 * rtu_err ; u0 = (
localP -> P_3 [ 0 ] * localX -> TransferFcn_CSTATE_n [ 0 ] + localP -> P_3 [
1 ] * localX -> TransferFcn_CSTATE_n [ 1 ] ) + localP -> P_0 * rtu_err ; if (
u0 > localP -> P_4 ) { localB -> B_2_223_1696 = localP -> P_4 ; } else if (
u0 < localP -> P_5 ) { localB -> B_2_223_1696 = localP -> P_5 ; } else {
localB -> B_2_223_1696 = u0 ; } } void ACDCACsummarycircuit_PR_Deriv (
SimStruct * S , B_PR_ACDCACsummarycircuit_T * localB ,
P_PR_ACDCACsummarycircuit_T * localP , X_PR_ACDCACsummarycircuit_T * localX ,
XDot_PR_ACDCACsummarycircuit_T * localXdot ) { localXdot ->
TransferFcn_CSTATE_n [ 0 ] = 0.0 ; localXdot -> TransferFcn_CSTATE_n [ 0 ] +=
localP -> P_2 [ 0 ] * localX -> TransferFcn_CSTATE_n [ 0 ] ; localXdot ->
TransferFcn_CSTATE_n [ 1 ] = 0.0 ; localXdot -> TransferFcn_CSTATE_n [ 0 ] +=
localP -> P_2 [ 1 ] * localX -> TransferFcn_CSTATE_n [ 1 ] ; localXdot ->
TransferFcn_CSTATE_n [ 1 ] += localX -> TransferFcn_CSTATE_n [ 0 ] ;
localXdot -> TransferFcn_CSTATE_n [ 0 ] += localB -> B_2_222_1688 ; } void
ACDCACsummarycircuit_PR_Term ( SimStruct * const S ) { } void
ACDCACsummarycircuit_RMS_Init ( SimStruct * S , B_RMS_ACDCACsummarycircuit_T
* localB , DW_RMS_ACDCACsummarycircuit_T * localDW ,
P_RMS_ACDCACsummarycircuit_T * localP , X_RMS_ACDCACsummarycircuit_T * localX
) { localX -> integrator_CSTATE_f = localP -> P_3 ; localDW ->
Memory_PreviousInput = localP -> P_7 ; localX -> integrator_CSTATE_d = localP
-> P_8 ; localDW -> Memory_PreviousInput_n = localP -> P_12 ; localB ->
B_6_219_1664 = localP -> P_2 ; } void ACDCACsummarycircuit_RMS_Disable (
SimStruct * S , DW_RMS_ACDCACsummarycircuit_T * localDW ) { localDW ->
RMS_MODE = false ; } void ACDCACsummarycircuit_RMS ( SimStruct * S ,
boolean_T rtu_Enable , real_T rtu_In , B_RMS_ACDCACsummarycircuit_T * localB
, DW_RMS_ACDCACsummarycircuit_T * localDW , P_RMS_ACDCACsummarycircuit_T *
localP , X_RMS_ACDCACsummarycircuit_T * localX ,
XDis_RMS_ACDCACsummarycircuit_T * localXdis ) { real_T B_6_454_3432 ; real_T
B_6_456_3448 ; int32_T isHit ; boolean_T rtb_B_6_466_3528 ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( ( isHit != 0 ) && ssIsModeUpdateTimeStep (
S ) ) { if ( rtu_Enable ) { if ( ! localDW -> RMS_MODE ) { if ( ssGetTaskTime
( S , 1 ) != ssGetTStart ( S ) ) { ssSetBlockStateForSolverChangedAtMajorStep
( S ) ; } ( void ) memset ( & ( localXdis -> integrator_CSTATE_f ) , 0 , 2 *
sizeof ( boolean_T ) ) ; localDW -> RMS_MODE = true ; } } else { if (
ssGetTaskTime ( S , 1 ) == ssGetTStart ( S ) ) { ( void ) memset ( & (
localXdis -> integrator_CSTATE_f ) , 1 , 2 * sizeof ( boolean_T ) ) ; } if (
localDW -> RMS_MODE ) { ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; (
void ) memset ( & ( localXdis -> integrator_CSTATE_f ) , 1 , 2 * sizeof (
boolean_T ) ) ; ACDCACsummarycircuit_RMS_Disable ( S , localDW ) ; } } } if (
localDW -> RMS_MODE ) { localB -> B_6_209_1584 = localX ->
integrator_CSTATE_f ; { real_T * * uBuffer = ( real_T * * ) & localDW ->
TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S ) ;
real_T tMinusDelay = simTime - localP -> P_4 ; B_6_454_3432 =
ACDCACsummarycircuit_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * uBuffer
, localDW -> TransportDelay_IWORK . CircularBufSize , & localDW ->
TransportDelay_IWORK . Last , localDW -> TransportDelay_IWORK . Tail ,
localDW -> TransportDelay_IWORK . Head , localP -> P_5 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ( * uBuffer + localDW -> TransportDelay_IWORK .
CircularBufSize ) [ localDW -> TransportDelay_IWORK . Head ] == ssGetT ( S )
) ) ) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { localB ->
B_6_210_1592 = localP -> P_6 ; } rtb_B_6_466_3528 = ( ssGetT ( S ) >= localB
-> B_6_210_1592 ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
localB -> B_6_211_1600 = localDW -> Memory_PreviousInput ; } if (
rtb_B_6_466_3528 ) { localB -> B_6_212_1608 = ( localB -> B_6_209_1584 -
B_6_454_3432 ) * localP -> P_1 ; } else { localB -> B_6_212_1608 = localB ->
B_6_211_1600 ; } localB -> B_6_213_1616 = localX -> integrator_CSTATE_d ; {
real_T * * uBuffer = ( real_T * * ) & localDW -> TransportDelay_PWORK_e .
TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - localP -> P_9 ; B_6_456_3448 =
ACDCACsummarycircuit_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * uBuffer
, localDW -> TransportDelay_IWORK_d . CircularBufSize , & localDW ->
TransportDelay_IWORK_d . Last , localDW -> TransportDelay_IWORK_d . Tail ,
localDW -> TransportDelay_IWORK_d . Head , localP -> P_10 , 0 , ( boolean_T )
( ssIsMinorTimeStep ( S ) && ( ( * uBuffer + localDW ->
TransportDelay_IWORK_d . CircularBufSize ) [ localDW ->
TransportDelay_IWORK_d . Head ] == ssGetT ( S ) ) ) ) ; } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { localB -> B_6_214_1624 =
localP -> P_11 ; } rtb_B_6_466_3528 = ( ssGetT ( S ) >= localB ->
B_6_214_1624 ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
localB -> B_6_215_1632 = localDW -> Memory_PreviousInput_n ; } if (
rtb_B_6_466_3528 ) { localB -> B_6_216_1640 = ( localB -> B_6_213_1616 -
B_6_456_3448 ) * localP -> P_0 ; } else { localB -> B_6_216_1640 = localB ->
B_6_215_1632 ; } localB -> B_6_217_1648 = ( muDoubleScalarSin ( localP ->
P_15 * ssGetTaskTime ( S , 0 ) + localP -> P_16 ) * localP -> P_13 + localP
-> P_14 ) * rtu_In ; localB -> B_6_218_1656 = ( muDoubleScalarSin ( localP ->
P_19 * ssGetTaskTime ( S , 0 ) + localP -> P_20 ) * localP -> P_17 + localP
-> P_18 ) * rtu_In ; localB -> B_6_219_1664 = localP -> P_21 *
muDoubleScalarHypot ( localB -> B_6_212_1608 , localB -> B_6_216_1640 ) ; if
( ssIsModeUpdateTimeStep ( S ) ) { srUpdateBC ( localDW -> RMS_SubsysRanBC )
; } } } void ACDCACsummarycircuit_RMS_Update ( SimStruct * S ,
B_RMS_ACDCACsummarycircuit_T * localB , DW_RMS_ACDCACsummarycircuit_T *
localDW , P_RMS_ACDCACsummarycircuit_T * localP ) { int32_T isHit ; if (
localDW -> RMS_MODE ) { { real_T * * uBuffer = ( real_T * * ) & localDW ->
TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S ) ;
localDW -> TransportDelay_IWORK . Head = ( ( localDW -> TransportDelay_IWORK
. Head < ( localDW -> TransportDelay_IWORK . CircularBufSize - 1 ) ) ? (
localDW -> TransportDelay_IWORK . Head + 1 ) : 0 ) ; if ( localDW ->
TransportDelay_IWORK . Head == localDW -> TransportDelay_IWORK . Tail ) { if
( ! ACDCACsummarycircuit_acc_rt_TDelayUpdateTailOrGrowBuf ( & localDW ->
TransportDelay_IWORK . CircularBufSize , & localDW -> TransportDelay_IWORK .
Tail , & localDW -> TransportDelay_IWORK . Head , & localDW ->
TransportDelay_IWORK . Last , simTime - localP -> P_4 , uBuffer , ( boolean_T
) 0 , false , & localDW -> TransportDelay_IWORK . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
uBuffer + localDW -> TransportDelay_IWORK . CircularBufSize ) [ localDW ->
TransportDelay_IWORK . Head ] = simTime ; ( * uBuffer ) [ localDW ->
TransportDelay_IWORK . Head ] = localB -> B_6_209_1584 ; } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { localDW ->
Memory_PreviousInput = localB -> B_6_212_1608 ; } { real_T * * uBuffer = (
real_T * * ) & localDW -> TransportDelay_PWORK_e . TUbufferPtrs [ 0 ] ;
real_T simTime = ssGetT ( S ) ; localDW -> TransportDelay_IWORK_d . Head = (
( localDW -> TransportDelay_IWORK_d . Head < ( localDW ->
TransportDelay_IWORK_d . CircularBufSize - 1 ) ) ? ( localDW ->
TransportDelay_IWORK_d . Head + 1 ) : 0 ) ; if ( localDW ->
TransportDelay_IWORK_d . Head == localDW -> TransportDelay_IWORK_d . Tail ) {
if ( ! ACDCACsummarycircuit_acc_rt_TDelayUpdateTailOrGrowBuf ( & localDW ->
TransportDelay_IWORK_d . CircularBufSize , & localDW ->
TransportDelay_IWORK_d . Tail , & localDW -> TransportDelay_IWORK_d . Head ,
& localDW -> TransportDelay_IWORK_d . Last , simTime - localP -> P_9 ,
uBuffer , ( boolean_T ) 0 , false , & localDW -> TransportDelay_IWORK_d .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * uBuffer + localDW -> TransportDelay_IWORK_d .
CircularBufSize ) [ localDW -> TransportDelay_IWORK_d . Head ] = simTime ; (
* uBuffer ) [ localDW -> TransportDelay_IWORK_d . Head ] = localB ->
B_6_213_1616 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
localDW -> Memory_PreviousInput_n = localB -> B_6_216_1640 ; } } } void
ACDCACsummarycircuit_RMS_Deriv ( SimStruct * S , B_RMS_ACDCACsummarycircuit_T
* localB , DW_RMS_ACDCACsummarycircuit_T * localDW ,
XDot_RMS_ACDCACsummarycircuit_T * localXdot ) { if ( localDW -> RMS_MODE ) {
localXdot -> integrator_CSTATE_f = localB -> B_6_217_1648 ; localXdot ->
integrator_CSTATE_d = localB -> B_6_218_1656 ; } else { { real_T * dx ; int_T
i ; dx = & ( localXdot -> integrator_CSTATE_f ) ; for ( i = 0 ; i < 2 ; i ++
) { dx [ i ] = 0.0 ; } } } } void ACDCACsummarycircuit_RMS_Term ( SimStruct *
const S ) { } void ACDCACsummarycircuit_TrueRMS_Init ( SimStruct * S ,
B_TrueRMS_ACDCACsummarycircuit_T * localB , DW_TrueRMS_ACDCACsummarycircuit_T
* localDW , P_TrueRMS_ACDCACsummarycircuit_T * localP ,
X_TrueRMS_ACDCACsummarycircuit_T * localX ) { localX -> integrator_CSTATE_no
= localP -> P_2 ; localDW -> Memory_PreviousInput = localP -> P_6 ; localB ->
B_8_208_1576 = localP -> P_1 ; } void ACDCACsummarycircuit_TrueRMS_Disable (
SimStruct * S , DW_TrueRMS_ACDCACsummarycircuit_T * localDW ) { localDW ->
TrueRMS_MODE = false ; } void ACDCACsummarycircuit_TrueRMS ( SimStruct * S ,
boolean_T rtu_Enable , real_T rtu_In , B_TrueRMS_ACDCACsummarycircuit_T *
localB , DW_TrueRMS_ACDCACsummarycircuit_T * localDW ,
P_TrueRMS_ACDCACsummarycircuit_T * localP , X_TrueRMS_ACDCACsummarycircuit_T
* localX , XDis_TrueRMS_ACDCACsummarycircuit_T * localXdis ) { real_T
B_8_448_3376 ; real_T tmp ; int32_T isHit ; isHit = ssIsSampleHit ( S , 1 , 0
) ; if ( ( isHit != 0 ) && ssIsModeUpdateTimeStep ( S ) ) { if ( rtu_Enable )
{ if ( ! localDW -> TrueRMS_MODE ) { if ( ssGetTaskTime ( S , 1 ) !=
ssGetTStart ( S ) ) { ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } (
void ) memset ( & ( localXdis -> integrator_CSTATE_no ) , 0 , 1 * sizeof (
boolean_T ) ) ; localDW -> TrueRMS_MODE = true ; } } else { if (
ssGetTaskTime ( S , 1 ) == ssGetTStart ( S ) ) { ( void ) memset ( & (
localXdis -> integrator_CSTATE_no ) , 1 , 1 * sizeof ( boolean_T ) ) ; } if (
localDW -> TrueRMS_MODE ) { ssSetBlockStateForSolverChangedAtMajorStep ( S )
; ( void ) memset ( & ( localXdis -> integrator_CSTATE_no ) , 1 , 1 * sizeof
( boolean_T ) ) ; ACDCACsummarycircuit_TrueRMS_Disable ( S , localDW ) ; } }
} if ( localDW -> TrueRMS_MODE ) { localB -> B_8_203_1536 = localX ->
integrator_CSTATE_no ; { real_T * * uBuffer = ( real_T * * ) & localDW ->
TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S ) ;
real_T tMinusDelay = simTime - localP -> P_3 ; B_8_448_3376 =
ACDCACsummarycircuit_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * uBuffer
, localDW -> TransportDelay_IWORK . CircularBufSize , & localDW ->
TransportDelay_IWORK . Last , localDW -> TransportDelay_IWORK . Tail ,
localDW -> TransportDelay_IWORK . Head , localP -> P_4 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ( * uBuffer + localDW -> TransportDelay_IWORK .
CircularBufSize ) [ localDW -> TransportDelay_IWORK . Head ] == ssGetT ( S )
) ) ) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { localB ->
B_8_204_1544 = localP -> P_5 ; localB -> B_8_205_1552 = localDW ->
Memory_PreviousInput ; } if ( ssGetT ( S ) >= localB -> B_8_204_1544 ) {
localB -> B_8_206_1560 = ( localB -> B_8_203_1536 - B_8_448_3376 ) * localP
-> P_0 ; } else { localB -> B_8_206_1560 = localB -> B_8_205_1552 ; } localB
-> B_8_207_1568 = rtu_In * rtu_In ; if ( localB -> B_8_206_1560 > localP ->
P_7 ) { tmp = localP -> P_7 ; } else if ( localB -> B_8_206_1560 < localP ->
P_8 ) { tmp = localP -> P_8 ; } else { tmp = localB -> B_8_206_1560 ; }
localB -> B_8_208_1576 = muDoubleScalarSqrt ( tmp ) ; if (
ssIsModeUpdateTimeStep ( S ) ) { srUpdateBC ( localDW -> TrueRMS_SubsysRanBC
) ; } } } void ACDCACsummarycircuit_TrueRMS_Update ( SimStruct * S ,
B_TrueRMS_ACDCACsummarycircuit_T * localB , DW_TrueRMS_ACDCACsummarycircuit_T
* localDW , P_TrueRMS_ACDCACsummarycircuit_T * localP ) { int32_T isHit ; if
( localDW -> TrueRMS_MODE ) { { real_T * * uBuffer = ( real_T * * ) & localDW
-> TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S )
; localDW -> TransportDelay_IWORK . Head = ( ( localDW ->
TransportDelay_IWORK . Head < ( localDW -> TransportDelay_IWORK .
CircularBufSize - 1 ) ) ? ( localDW -> TransportDelay_IWORK . Head + 1 ) : 0
) ; if ( localDW -> TransportDelay_IWORK . Head == localDW ->
TransportDelay_IWORK . Tail ) { if ( !
ACDCACsummarycircuit_acc_rt_TDelayUpdateTailOrGrowBuf ( & localDW ->
TransportDelay_IWORK . CircularBufSize , & localDW -> TransportDelay_IWORK .
Tail , & localDW -> TransportDelay_IWORK . Head , & localDW ->
TransportDelay_IWORK . Last , simTime - localP -> P_3 , uBuffer , ( boolean_T
) 0 , false , & localDW -> TransportDelay_IWORK . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
uBuffer + localDW -> TransportDelay_IWORK . CircularBufSize ) [ localDW ->
TransportDelay_IWORK . Head ] = simTime ; ( * uBuffer ) [ localDW ->
TransportDelay_IWORK . Head ] = localB -> B_8_203_1536 ; } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { localDW ->
Memory_PreviousInput = localB -> B_8_206_1560 ; } } } void
ACDCACsummarycircuit_TrueRMS_Deriv ( SimStruct * S ,
B_TrueRMS_ACDCACsummarycircuit_T * localB , DW_TrueRMS_ACDCACsummarycircuit_T
* localDW , XDot_TrueRMS_ACDCACsummarycircuit_T * localXdot ) { if ( localDW
-> TrueRMS_MODE ) { localXdot -> integrator_CSTATE_no = localB ->
B_8_207_1568 ; } else { localXdot -> integrator_CSTATE_no = 0.0 ; } } void
ACDCACsummarycircuit_TrueRMS_Term ( SimStruct * const S ) { } static void
mdlOutputs ( SimStruct * S , int_T tid ) { real_T B_31_243_1856 ; real_T
B_31_246_1880 ; real_T B_31_251_1920 ; real_T B_31_254_1944 ; real_T
B_31_270_2072 ; real_T B_31_274_2104 ; real_T B_31_283_2176 ; real_T
B_31_286_2200 ; real_T B_31_291_2240 ; real_T B_31_294_2264 ; real_T
B_31_312_2408 ; B_ACDCACsummarycircuit_T * _rtB ; DW_ACDCACsummarycircuit_T *
_rtDW ; P_ACDCACsummarycircuit_T * _rtP ; X_ACDCACsummarycircuit_T * _rtX ;
real_T rtb_B_31_224_1704 ; real_T rtb_B_31_226_1720 ; real_T
rtb_B_31_230_1752 ; real_T rtb_B_31_231_1760 ; real_T rtb_B_31_242_1848 ;
real_T rtb_B_31_255_1952 ; int32_T isHit ; boolean_T rtb_B_31_347_2674 ;
boolean_T rtb_B_31_348_2675 ; boolean_T rtb_B_31_354_2681 ; _rtDW = ( (
DW_ACDCACsummarycircuit_T * ) ssGetRootDWork ( S ) ) ; _rtX = ( (
X_ACDCACsummarycircuit_T * ) ssGetContStates ( S ) ) ; _rtP = ( (
P_ACDCACsummarycircuit_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_ACDCACsummarycircuit_T * ) _ssGetModelBlockIO ( S ) ) ; _rtB -> B_31_0_0 =
muDoubleScalarSin ( _rtP -> P_6 * ssGetTaskTime ( S , 0 ) + _rtP -> P_7 ) *
_rtP -> P_4 + _rtP -> P_5 ; isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit
!= 0 ) { ssCallAccelRunBlock ( S , 31 , 1 , SS_CALL_MDL_OUTPUTS ) ; } isHit =
ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_31_34_272 = _rtP
-> P_20 * _rtB -> B_31_1_8 [ 18 ] ; } _rtB -> B_31_35_280 = _rtP -> P_19 *
_rtX -> _CSTATE - _rtB -> B_31_34_272 ; ACDCACsummarycircuit_PR ( S , _rtB ->
B_31_35_280 , & _rtB -> PR , & _rtP -> PR , & _rtX -> PR ) ; isHit =
ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_31_36_288 = _rtP
-> P_21 * _rtB -> B_31_1_8 [ 15 ] ; } rtb_B_31_224_1704 = _rtB -> PR .
B_2_223_1696 / _rtB -> B_31_36_288 ; rtb_B_31_226_1720 = muDoubleScalarAbs (
rtb_B_31_224_1704 ) ; rtb_B_31_230_1752 = look1_binlxpw ( muDoubleScalarRem (
ssGetT ( S ) - _rtB -> B_31_37_296 , _rtB -> B_31_120_960 ) , _rtP -> P_23 ,
_rtP -> P_22 , 2U ) ; rtb_B_31_347_2674 = ( rtb_B_31_226_1720 >=
rtb_B_31_230_1752 ) ; rtb_B_31_348_2675 = ( rtb_B_31_226_1720 <
rtb_B_31_230_1752 ) ; if ( rtb_B_31_224_1704 > _rtP -> P_24 ) { _rtB ->
B_31_38_304 = rtb_B_31_347_2674 ; } else { _rtB -> B_31_38_304 =
rtb_B_31_348_2675 ; } if ( rtb_B_31_224_1704 > _rtP -> P_25 ) { _rtB ->
B_31_39_312 = rtb_B_31_348_2675 ; } else { _rtB -> B_31_39_312 =
rtb_B_31_347_2674 ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 )
{ _rtB -> B_31_40_320 = _rtP -> P_26 * _rtB -> B_31_1_8 [ 14 ] ; } _rtB ->
B_31_41_328 = _rtB -> B_31_116_928 - ( ( _rtP -> P_28 [ 0 ] * _rtX ->
TransferFcn_CSTATE [ 0 ] + _rtP -> P_28 [ 1 ] * _rtX -> TransferFcn_CSTATE [
1 ] ) + _rtP -> P_29 * _rtB -> B_31_36_288 ) ; rtb_B_31_231_1760 = _rtP ->
P_30 * _rtB -> B_31_41_328 + _rtX -> Integrator_CSTATE ; if (
rtb_B_31_231_1760 > _rtP -> P_32 ) { _rtB -> B_31_42_336 = _rtP -> P_32 ; }
else if ( rtb_B_31_231_1760 < _rtP -> P_33 ) { _rtB -> B_31_42_336 = _rtP ->
P_33 ; } else { _rtB -> B_31_42_336 = rtb_B_31_231_1760 ; } isHit =
ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_31_43_344 = _rtP
-> P_34 * _rtB -> B_31_40_320 ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if (
isHit != 0 ) { _rtB -> B_31_44_352 = _rtP -> P_35 * _rtB -> B_31_1_8 [ 17 ] ;
} _rtB -> B_31_45_360 = _rtB -> B_31_42_336 * _rtB -> B_31_43_344 - _rtB ->
B_31_44_352 ; ACDCACsummarycircuit_PR ( S , _rtB -> B_31_45_360 , & _rtB ->
PR_i , & _rtP -> PR_i , & _rtX -> PR_i ) ; rtb_B_31_226_1720 = ( _rtB ->
B_31_40_320 - _rtB -> PR_i . B_2_223_1696 ) / _rtB -> B_31_36_288 ;
rtb_B_31_230_1752 = muDoubleScalarAbs ( rtb_B_31_226_1720 ) ;
rtb_B_31_242_1848 = look1_binlxpw ( muDoubleScalarRem ( ssGetT ( S ) - _rtB
-> B_31_46_368 , _rtB -> B_31_118_944 ) , _rtP -> P_37 , _rtP -> P_36 , 2U )
; rtb_B_31_347_2674 = ( rtb_B_31_230_1752 >= rtb_B_31_242_1848 ) ;
rtb_B_31_348_2675 = ( rtb_B_31_230_1752 < rtb_B_31_242_1848 ) ; if (
rtb_B_31_226_1720 > _rtP -> P_38 ) { _rtB -> B_31_47_376 = rtb_B_31_347_2674
; } else { _rtB -> B_31_47_376 = rtb_B_31_348_2675 ; } rtb_B_31_354_2681 = (
rtb_B_31_226_1720 >= _rtB -> B_31_117_936 ) ; _rtB -> B_31_48_384 = !
rtb_B_31_354_2681 ; if ( rtb_B_31_226_1720 > _rtP -> P_39 ) { _rtB ->
B_31_122_976 = rtb_B_31_348_2675 ; } else { _rtB -> B_31_122_976 =
rtb_B_31_347_2674 ; } _rtB -> B_31_49_392 = _rtB -> B_31_122_976 ; _rtB ->
B_31_50_400 = rtb_B_31_354_2681 ; rtb_B_31_347_2674 = ( rtb_B_31_224_1704 >=
_rtB -> B_31_119_952 ) ; _rtB -> B_31_51_408 = rtb_B_31_347_2674 ; _rtB ->
B_31_52_416 = ! rtb_B_31_347_2674 ; isHit = ssIsSampleHit ( S , 2 , 0 ) ; if
( isHit != 0 ) { ssCallAccelRunBlock ( S , 31 , 114 , SS_CALL_MDL_OUTPUTS ) ;
} isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
ssCallAccelRunBlock ( S , 31 , 115 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 31 , 116 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 31 , 117 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 31 , 118 , SS_CALL_MDL_OUTPUTS ) ; } isHit =
ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { ssCallAccelRunBlock ( S ,
31 , 119 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_31_53_424 = _rtP -> P_40 * _rtB
-> B_31_1_8 [ 16 ] ; ssCallAccelRunBlock ( S , 31 , 121 , SS_CALL_MDL_OUTPUTS
) ; } _rtB -> B_31_54_432 = _rtX -> integ1_CSTATE ; { real_T * * uBuffer = (
real_T * * ) & _rtDW -> T_PWORK . TUbufferPtrs [ 0 ] ; real_T simTime =
ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_42 ; B_31_243_1856 =
ACDCACsummarycircuit_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * uBuffer
, _rtDW -> T_IWORK . CircularBufSize , & _rtDW -> T_IWORK . Last , _rtDW ->
T_IWORK . Tail , _rtDW -> T_IWORK . Head , _rtP -> P_43 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ( * uBuffer + _rtDW -> T_IWORK . CircularBufSize
) [ _rtDW -> T_IWORK . Head ] == ssGetT ( S ) ) ) ) ; } rtb_B_31_226_1720 =
_rtB -> B_31_54_432 - B_31_243_1856 ; _rtB -> B_31_55_440 = _rtX ->
Integ2_CSTATE ; { real_T * * uBuffer = ( real_T * * ) & _rtDW -> T1_PWORK .
TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_45 ; B_31_246_1880 =
ACDCACsummarycircuit_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * uBuffer
, _rtDW -> T1_IWORK . CircularBufSize , & _rtDW -> T1_IWORK . Last , _rtDW ->
T1_IWORK . Tail , _rtDW -> T1_IWORK . Head , _rtP -> P_46 , 0 , ( boolean_T )
( ssIsMinorTimeStep ( S ) && ( ( * uBuffer + _rtDW -> T1_IWORK .
CircularBufSize ) [ _rtDW -> T1_IWORK . Head ] == ssGetT ( S ) ) ) ) ; }
rtb_B_31_230_1752 = _rtB -> B_31_55_440 - B_31_246_1880 ; _rtB -> B_31_56_448
= _rtX -> integ1_CSTATE_m ; { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
T_PWORK_f . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S ) ; real_T
tMinusDelay = simTime - _rtP -> P_48 ; B_31_251_1920 =
ACDCACsummarycircuit_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * uBuffer
, _rtDW -> T_IWORK_f . CircularBufSize , & _rtDW -> T_IWORK_f . Last , _rtDW
-> T_IWORK_f . Tail , _rtDW -> T_IWORK_f . Head , _rtP -> P_49 , 0 , (
boolean_T ) ( ssIsMinorTimeStep ( S ) && ( ( * uBuffer + _rtDW -> T_IWORK_f .
CircularBufSize ) [ _rtDW -> T_IWORK_f . Head ] == ssGetT ( S ) ) ) ) ; }
rtb_B_31_242_1848 = _rtB -> B_31_56_448 - B_31_251_1920 ; _rtB -> B_31_57_456
= _rtX -> Integ2_CSTATE_a ; { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
T1_PWORK_j . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S ) ; real_T
tMinusDelay = simTime - _rtP -> P_51 ; B_31_254_1944 =
ACDCACsummarycircuit_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * uBuffer
, _rtDW -> T1_IWORK_h . CircularBufSize , & _rtDW -> T1_IWORK_h . Last ,
_rtDW -> T1_IWORK_h . Tail , _rtDW -> T1_IWORK_h . Head , _rtP -> P_52 , 0 ,
( boolean_T ) ( ssIsMinorTimeStep ( S ) && ( ( * uBuffer + _rtDW ->
T1_IWORK_h . CircularBufSize ) [ _rtDW -> T1_IWORK_h . Head ] == ssGetT ( S )
) ) ) ; } rtb_B_31_255_1952 = _rtB -> B_31_57_456 - B_31_254_1944 ;
rtb_B_31_224_1704 = muDoubleScalarSqrt ( rtb_B_31_226_1720 *
rtb_B_31_226_1720 + rtb_B_31_230_1752 * rtb_B_31_230_1752 ) *
muDoubleScalarSqrt ( rtb_B_31_242_1848 * rtb_B_31_242_1848 +
rtb_B_31_255_1952 * rtb_B_31_255_1952 ) ; rtb_B_31_226_1720 = ( _rtP -> P_53
* muDoubleScalarAtan2 ( rtb_B_31_230_1752 , rtb_B_31_226_1720 ) - _rtP ->
P_54 * muDoubleScalarAtan2 ( rtb_B_31_255_1952 , rtb_B_31_242_1848 ) ) * _rtP
-> P_55 ; _rtB -> B_31_58_464 [ 0 ] = rtb_B_31_224_1704 * muDoubleScalarCos (
rtb_B_31_226_1720 ) * _rtP -> P_56 ; _rtB -> B_31_58_464 [ 1 ] =
rtb_B_31_224_1704 * muDoubleScalarSin ( rtb_B_31_226_1720 ) * _rtP -> P_56 ;
_rtB -> B_31_60_480 = _rtX -> integrator_CSTATE ; { real_T * * uBuffer = (
real_T * * ) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T
simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_58 ;
B_31_270_2072 = ACDCACsummarycircuit_acc_rt_TDelayInterpolate ( tMinusDelay ,
0.0 , * uBuffer , _rtDW -> TransportDelay_IWORK . CircularBufSize , & _rtDW
-> TransportDelay_IWORK . Last , _rtDW -> TransportDelay_IWORK . Tail , _rtDW
-> TransportDelay_IWORK . Head , _rtP -> P_59 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ( * uBuffer + _rtDW -> TransportDelay_IWORK .
CircularBufSize ) [ _rtDW -> TransportDelay_IWORK . Head ] == ssGetT ( S ) )
) ) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB ->
B_31_61_488 = _rtP -> P_60 ; } rtb_B_31_347_2674 = ( ssGetT ( S ) >= _rtB ->
B_31_61_488 ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
_rtB -> B_31_62_496 = _rtDW -> Memory_PreviousInput ; } if (
rtb_B_31_347_2674 ) { _rtB -> B_31_63_504 = ( _rtB -> B_31_60_480 -
B_31_270_2072 ) * _rtP -> P_0 ; } else { _rtB -> B_31_63_504 = _rtB ->
B_31_62_496 ; } ACDCACsummarycircuit_TrueRMS ( S , _rtB -> B_31_131_985 ,
_rtB -> B_31_63_504 , & _rtB -> TrueRMS_o , & _rtDW -> TrueRMS_o , & _rtP ->
TrueRMS_o , & _rtX -> TrueRMS_o , & ( ( XDis_ACDCACsummarycircuit_T * )
ssGetContStateDisabled ( S ) ) -> TrueRMS_o ) ; ACDCACsummarycircuit_RMS ( S
, _rtB -> B_31_132_986 , _rtB -> B_31_63_504 , & _rtB -> RMS_g , & _rtDW ->
RMS_g , & _rtP -> RMS_g , & _rtX -> RMS_g , & ( ( XDis_ACDCACsummarycircuit_T
* ) ssGetContStateDisabled ( S ) ) -> RMS_g ) ; if ( _rtB -> B_31_131_985 ) {
rtb_B_31_224_1704 = _rtB -> TrueRMS_o . B_8_208_1576 ; } else {
rtb_B_31_224_1704 = _rtB -> RMS_g . B_6_219_1664 ; } _rtB -> B_31_64_512 =
_rtX -> integrator_CSTATE_n ; { real_T * * uBuffer = ( real_T * * ) & _rtDW
-> TransportDelay_PWORK_f . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S
) ; real_T tMinusDelay = simTime - _rtP -> P_63 ; B_31_274_2104 =
ACDCACsummarycircuit_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * uBuffer
, _rtDW -> TransportDelay_IWORK_o . CircularBufSize , & _rtDW ->
TransportDelay_IWORK_o . Last , _rtDW -> TransportDelay_IWORK_o . Tail ,
_rtDW -> TransportDelay_IWORK_o . Head , _rtP -> P_64 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ( * uBuffer + _rtDW -> TransportDelay_IWORK_o .
CircularBufSize ) [ _rtDW -> TransportDelay_IWORK_o . Head ] == ssGetT ( S )
) ) ) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB ->
B_31_65_520 = _rtP -> P_65 ; } rtb_B_31_347_2674 = ( ssGetT ( S ) >= _rtB ->
B_31_65_520 ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
_rtB -> B_31_66_528 = _rtDW -> Memory_PreviousInput_p ; } if (
rtb_B_31_347_2674 ) { _rtB -> B_31_67_536 = ( _rtB -> B_31_64_512 -
B_31_274_2104 ) * _rtP -> P_2 ; } else { _rtB -> B_31_67_536 = _rtB ->
B_31_66_528 ; } rtb_B_31_226_1720 = _rtB -> B_31_67_536 * _rtB -> B_31_67_536
; ACDCACsummarycircuit_TrueRMS ( S , _rtB -> B_31_133_987 , _rtB ->
B_31_63_504 , & _rtB -> TrueRMS_f , & _rtDW -> TrueRMS_f , & _rtP ->
TrueRMS_f , & _rtX -> TrueRMS_f , & ( ( XDis_ACDCACsummarycircuit_T * )
ssGetContStateDisabled ( S ) ) -> TrueRMS_f ) ; ACDCACsummarycircuit_RMS ( S
, _rtB -> B_31_134_988 , _rtB -> B_31_63_504 , & _rtB -> RMS_ge , & _rtDW ->
RMS_ge , & _rtP -> RMS_ge , & _rtX -> RMS_ge , & ( (
XDis_ACDCACsummarycircuit_T * ) ssGetContStateDisabled ( S ) ) -> RMS_ge ) ;
if ( _rtB -> B_31_133_987 ) { rtb_B_31_230_1752 = _rtB -> TrueRMS_f .
B_8_208_1576 ; } else { rtb_B_31_230_1752 = _rtB -> RMS_ge . B_6_219_1664 ; }
rtb_B_31_230_1752 *= rtb_B_31_230_1752 ; if ( rtb_B_31_230_1752 > _rtP ->
P_67 ) { rtb_B_31_242_1848 = _rtP -> P_67 ; } else if ( rtb_B_31_230_1752 <
_rtP -> P_68 ) { rtb_B_31_242_1848 = _rtP -> P_68 ; } else {
rtb_B_31_242_1848 = rtb_B_31_230_1752 ; } rtb_B_31_224_1704 = ( (
rtb_B_31_224_1704 * rtb_B_31_224_1704 - rtb_B_31_226_1720 ) -
rtb_B_31_230_1752 ) / rtb_B_31_242_1848 ; if ( rtb_B_31_224_1704 > _rtP ->
P_69 ) { rtb_B_31_224_1704 = _rtP -> P_69 ; } else if ( rtb_B_31_224_1704 <
_rtP -> P_70 ) { rtb_B_31_224_1704 = _rtP -> P_70 ; } _rtB -> B_31_68_544 =
muDoubleScalarSqrt ( rtb_B_31_224_1704 ) ; ssCallAccelRunBlock ( S , 1 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0
) { ssCallAccelRunBlock ( S , 31 , 185 , SS_CALL_MDL_OUTPUTS ) ; } _rtB ->
B_31_69_552 = _rtX -> integ1_CSTATE_p ; { real_T * * uBuffer = ( real_T * * )
& _rtDW -> T_PWORK_fh . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S ) ;
real_T tMinusDelay = simTime - _rtP -> P_72 ; B_31_283_2176 =
ACDCACsummarycircuit_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * uBuffer
, _rtDW -> T_IWORK_o . CircularBufSize , & _rtDW -> T_IWORK_o . Last , _rtDW
-> T_IWORK_o . Tail , _rtDW -> T_IWORK_o . Head , _rtP -> P_73 , 0 , (
boolean_T ) ( ssIsMinorTimeStep ( S ) && ( ( * uBuffer + _rtDW -> T_IWORK_o .
CircularBufSize ) [ _rtDW -> T_IWORK_o . Head ] == ssGetT ( S ) ) ) ) ; }
rtb_B_31_226_1720 = _rtB -> B_31_69_552 - B_31_283_2176 ; _rtB -> B_31_70_560
= _rtX -> Integ2_CSTATE_o ; { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
T1_PWORK_h . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S ) ; real_T
tMinusDelay = simTime - _rtP -> P_75 ; B_31_286_2200 =
ACDCACsummarycircuit_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * uBuffer
, _rtDW -> T1_IWORK_hc . CircularBufSize , & _rtDW -> T1_IWORK_hc . Last ,
_rtDW -> T1_IWORK_hc . Tail , _rtDW -> T1_IWORK_hc . Head , _rtP -> P_76 , 0
, ( boolean_T ) ( ssIsMinorTimeStep ( S ) && ( ( * uBuffer + _rtDW ->
T1_IWORK_hc . CircularBufSize ) [ _rtDW -> T1_IWORK_hc . Head ] == ssGetT ( S
) ) ) ) ; } rtb_B_31_230_1752 = _rtB -> B_31_70_560 - B_31_286_2200 ; _rtB ->
B_31_71_568 = _rtX -> integ1_CSTATE_i ; { real_T * * uBuffer = ( real_T * * )
& _rtDW -> T_PWORK_h . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S ) ;
real_T tMinusDelay = simTime - _rtP -> P_78 ; B_31_291_2240 =
ACDCACsummarycircuit_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * uBuffer
, _rtDW -> T_IWORK_fa . CircularBufSize , & _rtDW -> T_IWORK_fa . Last ,
_rtDW -> T_IWORK_fa . Tail , _rtDW -> T_IWORK_fa . Head , _rtP -> P_79 , 0 ,
( boolean_T ) ( ssIsMinorTimeStep ( S ) && ( ( * uBuffer + _rtDW ->
T_IWORK_fa . CircularBufSize ) [ _rtDW -> T_IWORK_fa . Head ] == ssGetT ( S )
) ) ) ; } rtb_B_31_242_1848 = _rtB -> B_31_71_568 - B_31_291_2240 ; _rtB ->
B_31_72_576 = _rtX -> Integ2_CSTATE_c ; { real_T * * uBuffer = ( real_T * * )
& _rtDW -> T1_PWORK_hj . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S ) ;
real_T tMinusDelay = simTime - _rtP -> P_81 ; B_31_294_2264 =
ACDCACsummarycircuit_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * uBuffer
, _rtDW -> T1_IWORK_c . CircularBufSize , & _rtDW -> T1_IWORK_c . Last ,
_rtDW -> T1_IWORK_c . Tail , _rtDW -> T1_IWORK_c . Head , _rtP -> P_82 , 0 ,
( boolean_T ) ( ssIsMinorTimeStep ( S ) && ( ( * uBuffer + _rtDW ->
T1_IWORK_c . CircularBufSize ) [ _rtDW -> T1_IWORK_c . Head ] == ssGetT ( S )
) ) ) ; } rtb_B_31_255_1952 = _rtB -> B_31_72_576 - B_31_294_2264 ;
rtb_B_31_224_1704 = muDoubleScalarSqrt ( rtb_B_31_226_1720 *
rtb_B_31_226_1720 + rtb_B_31_230_1752 * rtb_B_31_230_1752 ) *
muDoubleScalarSqrt ( rtb_B_31_242_1848 * rtb_B_31_242_1848 +
rtb_B_31_255_1952 * rtb_B_31_255_1952 ) ; rtb_B_31_226_1720 = ( _rtP -> P_83
* muDoubleScalarAtan2 ( rtb_B_31_230_1752 , rtb_B_31_226_1720 ) - _rtP ->
P_84 * muDoubleScalarAtan2 ( rtb_B_31_255_1952 , rtb_B_31_242_1848 ) ) * _rtP
-> P_85 ; _rtB -> B_31_73_584 [ 0 ] = rtb_B_31_224_1704 * muDoubleScalarCos (
rtb_B_31_226_1720 ) * _rtP -> P_86 ; _rtB -> B_31_73_584 [ 1 ] =
rtb_B_31_224_1704 * muDoubleScalarSin ( rtb_B_31_226_1720 ) * _rtP -> P_86 ;
_rtB -> B_31_75_600 = _rtB -> B_31_73_584 [ 0 ] / _rtB -> B_31_58_464 [ 0 ] ;
isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { ssCallAccelRunBlock
( S , 31 , 219 , SS_CALL_MDL_OUTPUTS ) ; } isHit = ssIsSampleHit ( S , 2 , 0
) ; if ( isHit != 0 ) { ssCallAccelRunBlock ( S , 31 , 220 ,
SS_CALL_MDL_OUTPUTS ) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit !=
0 ) { ssCallAccelRunBlock ( S , 31 , 221 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 31 , 222 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 31 , 223 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 31 , 224 , SS_CALL_MDL_OUTPUTS ) ; }
ACDCACsummarycircuit_TrueRMS ( S , _rtB -> B_31_127_981 , _rtB -> B_31_53_424
, & _rtB -> TrueRMS_i , & _rtDW -> TrueRMS_i , & _rtP -> TrueRMS_i , & _rtX
-> TrueRMS_i , & ( ( XDis_ACDCACsummarycircuit_T * ) ssGetContStateDisabled (
S ) ) -> TrueRMS_i ) ; ACDCACsummarycircuit_RMS ( S , _rtB -> B_31_128_982 ,
_rtB -> B_31_53_424 , & _rtB -> RMS_l , & _rtDW -> RMS_l , & _rtP -> RMS_l ,
& _rtX -> RMS_l , & ( ( XDis_ACDCACsummarycircuit_T * )
ssGetContStateDisabled ( S ) ) -> RMS_l ) ; if ( _rtB -> B_31_127_981 ) {
rtb_B_31_224_1704 = _rtB -> TrueRMS_i . B_8_208_1576 ; } else {
rtb_B_31_224_1704 = _rtB -> RMS_l . B_6_219_1664 ; } _rtB -> B_31_76_608 =
_rtX -> integrator_CSTATE_e ; { real_T * * uBuffer = ( real_T * * ) & _rtDW
-> TransportDelay_PWORK_l . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S
) ; real_T tMinusDelay = simTime - _rtP -> P_88 ; B_31_312_2408 =
ACDCACsummarycircuit_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * uBuffer
, _rtDW -> TransportDelay_IWORK_h . CircularBufSize , & _rtDW ->
TransportDelay_IWORK_h . Last , _rtDW -> TransportDelay_IWORK_h . Tail ,
_rtDW -> TransportDelay_IWORK_h . Head , _rtP -> P_89 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ( * uBuffer + _rtDW -> TransportDelay_IWORK_h .
CircularBufSize ) [ _rtDW -> TransportDelay_IWORK_h . Head ] == ssGetT ( S )
) ) ) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB ->
B_31_77_616 = _rtP -> P_90 ; } rtb_B_31_347_2674 = ( ssGetT ( S ) >= _rtB ->
B_31_77_616 ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
_rtB -> B_31_78_624 = _rtDW -> Memory_PreviousInput_pe ; } if (
rtb_B_31_347_2674 ) { _rtB -> B_31_79_632 = ( _rtB -> B_31_76_608 -
B_31_312_2408 ) * _rtP -> P_1 ; } else { _rtB -> B_31_79_632 = _rtB ->
B_31_78_624 ; } rtb_B_31_226_1720 = _rtB -> B_31_79_632 * _rtB -> B_31_79_632
; ACDCACsummarycircuit_TrueRMS ( S , _rtB -> B_31_129_983 , _rtB ->
B_31_53_424 , & _rtB -> TrueRMS_k , & _rtDW -> TrueRMS_k , & _rtP ->
TrueRMS_k , & _rtX -> TrueRMS_k , & ( ( XDis_ACDCACsummarycircuit_T * )
ssGetContStateDisabled ( S ) ) -> TrueRMS_k ) ; ACDCACsummarycircuit_RMS ( S
, _rtB -> B_31_130_984 , _rtB -> B_31_53_424 , & _rtB -> RMS_i , & _rtDW ->
RMS_i , & _rtP -> RMS_i , & _rtX -> RMS_i , & ( ( XDis_ACDCACsummarycircuit_T
* ) ssGetContStateDisabled ( S ) ) -> RMS_i ) ; if ( _rtB -> B_31_129_983 ) {
rtb_B_31_230_1752 = _rtB -> TrueRMS_k . B_8_208_1576 ; } else {
rtb_B_31_230_1752 = _rtB -> RMS_i . B_6_219_1664 ; } rtb_B_31_230_1752 *=
rtb_B_31_230_1752 ; if ( rtb_B_31_230_1752 > _rtP -> P_92 ) {
rtb_B_31_242_1848 = _rtP -> P_92 ; } else if ( rtb_B_31_230_1752 < _rtP ->
P_93 ) { rtb_B_31_242_1848 = _rtP -> P_93 ; } else { rtb_B_31_242_1848 =
rtb_B_31_230_1752 ; } rtb_B_31_224_1704 = ( ( rtb_B_31_224_1704 *
rtb_B_31_224_1704 - rtb_B_31_226_1720 ) - rtb_B_31_230_1752 ) /
rtb_B_31_242_1848 ; if ( rtb_B_31_224_1704 > _rtP -> P_94 ) {
rtb_B_31_224_1704 = _rtP -> P_94 ; } else if ( rtb_B_31_224_1704 < _rtP ->
P_95 ) { rtb_B_31_224_1704 = _rtP -> P_95 ; } _rtB -> B_31_80_640 =
muDoubleScalarSqrt ( rtb_B_31_224_1704 ) ; isHit = ssIsSampleHit ( S , 1 , 0
) ; if ( isHit != 0 ) { ssCallAccelRunBlock ( S , 31 , 247 ,
SS_CALL_MDL_OUTPUTS ) ; } ACDCACsummarycircuit_TrueRMS ( S , _rtB ->
B_31_125_979 , _rtB -> B_31_53_424 , & _rtB -> TrueRMS , & _rtDW -> TrueRMS ,
& _rtP -> TrueRMS , & _rtX -> TrueRMS , & ( ( XDis_ACDCACsummarycircuit_T * )
ssGetContStateDisabled ( S ) ) -> TrueRMS ) ; ACDCACsummarycircuit_RMS ( S ,
_rtB -> B_31_126_980 , _rtB -> B_31_53_424 , & _rtB -> RMS , & _rtDW -> RMS ,
& _rtP -> RMS , & _rtX -> RMS , & ( ( XDis_ACDCACsummarycircuit_T * )
ssGetContStateDisabled ( S ) ) -> RMS ) ; if ( _rtB -> B_31_125_979 ) { _rtB
-> B_31_81_648 = _rtB -> TrueRMS . B_8_208_1576 ; } else { _rtB ->
B_31_81_648 = _rtB -> RMS . B_6_219_1664 ; } isHit = ssIsSampleHit ( S , 1 ,
0 ) ; if ( isHit != 0 ) { ssCallAccelRunBlock ( S , 31 , 251 ,
SS_CALL_MDL_OUTPUTS ) ; } if ( rtb_B_31_231_1760 > _rtP -> P_98 ) {
rtb_B_31_224_1704 = rtb_B_31_231_1760 - _rtP -> P_98 ; } else if (
rtb_B_31_231_1760 >= _rtP -> P_97 ) { rtb_B_31_224_1704 = 0.0 ; } else {
rtb_B_31_224_1704 = rtb_B_31_231_1760 - _rtP -> P_97 ; } rtb_B_31_226_1720 =
_rtP -> P_99 * _rtB -> B_31_41_328 ; rtb_B_31_242_1848 = muDoubleScalarSign (
rtb_B_31_224_1704 ) ; if ( muDoubleScalarIsNaN ( rtb_B_31_242_1848 ) ) {
rtb_B_31_242_1848 = 0.0 ; } else { rtb_B_31_242_1848 = muDoubleScalarRem (
rtb_B_31_242_1848 , 256.0 ) ; } rtb_B_31_230_1752 = muDoubleScalarSign (
rtb_B_31_226_1720 ) ; if ( muDoubleScalarIsNaN ( rtb_B_31_230_1752 ) ) {
rtb_B_31_230_1752 = 0.0 ; } else { rtb_B_31_230_1752 = muDoubleScalarRem (
rtb_B_31_230_1752 , 256.0 ) ; } _rtB -> B_31_123_977 = ( ( _rtP -> P_96 *
rtb_B_31_231_1760 != rtb_B_31_224_1704 ) && ( ( rtb_B_31_242_1848 < 0.0 ? (
int32_T ) ( int8_T ) - ( int8_T ) ( uint8_T ) - rtb_B_31_242_1848 : ( int32_T
) ( int8_T ) ( uint8_T ) rtb_B_31_242_1848 ) == ( rtb_B_31_230_1752 < 0.0 ? (
int32_T ) ( int8_T ) - ( int8_T ) ( uint8_T ) - rtb_B_31_230_1752 : ( int32_T
) ( int8_T ) ( uint8_T ) rtb_B_31_230_1752 ) ) ) ; isHit = ssIsSampleHit ( S
, 1 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_31_124_978 = _rtDW ->
Memory_PreviousInput_b ; } if ( _rtB -> B_31_124_978 ) { _rtB -> B_31_82_656
= ACDCACsummarycircuit_rtC ( S ) -> B_31_474_3584 ; } else { _rtB ->
B_31_82_656 = rtb_B_31_226_1720 ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if
( isHit != 0 ) { _rtB -> B_31_83_664 = _rtP -> P_100 * _rtB -> B_31_44_352 ;
} _rtB -> B_31_84_672 = ( muDoubleScalarSin ( _rtP -> P_103 * ssGetTaskTime (
S , 0 ) + _rtP -> P_104 ) * _rtP -> P_101 + _rtP -> P_102 ) * _rtB ->
B_31_83_664 ; _rtB -> B_31_85_680 = ( muDoubleScalarSin ( _rtP -> P_107 *
ssGetTaskTime ( S , 0 ) + _rtP -> P_108 ) * _rtP -> P_105 + _rtP -> P_106 ) *
_rtB -> B_31_83_664 ; isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 )
{ _rtB -> B_31_86_688 = _rtP -> P_109 * _rtB -> B_31_40_320 ; } _rtB ->
B_31_87_696 = ( muDoubleScalarSin ( _rtP -> P_112 * ssGetTaskTime ( S , 0 ) +
_rtP -> P_113 ) * _rtP -> P_110 + _rtP -> P_111 ) * _rtB -> B_31_86_688 ;
_rtB -> B_31_88_704 = ( muDoubleScalarSin ( _rtP -> P_116 * ssGetTaskTime ( S
, 0 ) + _rtP -> P_117 ) * _rtP -> P_114 + _rtP -> P_115 ) * _rtB ->
B_31_86_688 ; isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB
-> B_31_89_712 = _rtP -> P_118 * _rtB -> B_31_34_272 ; } _rtB -> B_31_90_720
= ( muDoubleScalarSin ( _rtP -> P_121 * ssGetTaskTime ( S , 0 ) + _rtP ->
P_122 ) * _rtP -> P_119 + _rtP -> P_120 ) * _rtB -> B_31_89_712 ; _rtB ->
B_31_91_728 = ( muDoubleScalarSin ( _rtP -> P_125 * ssGetTaskTime ( S , 0 ) +
_rtP -> P_126 ) * _rtP -> P_123 + _rtP -> P_124 ) * _rtB -> B_31_89_712 ;
isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_31_92_736
= _rtP -> P_127 * _rtB -> B_31_53_424 ; } _rtB -> B_31_93_744 = (
muDoubleScalarSin ( _rtP -> P_130 * ssGetTaskTime ( S , 0 ) + _rtP -> P_131 )
* _rtP -> P_128 + _rtP -> P_129 ) * _rtB -> B_31_92_736 ; _rtB -> B_31_94_752
= ( muDoubleScalarSin ( _rtP -> P_134 * ssGetTaskTime ( S , 0 ) + _rtP ->
P_135 ) * _rtP -> P_132 + _rtP -> P_133 ) * _rtB -> B_31_92_736 ; isHit =
ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_31_95_760 = _rtB
-> B_31_40_320 - _rtB -> B_31_53_424 ; } UNUSED_PARAMETER ( tid ) ; } static
void mdlOutputsTID3 ( SimStruct * S , int_T tid ) { B_ACDCACsummarycircuit_T
* _rtB ; P_ACDCACsummarycircuit_T * _rtP ; _rtP = ( (
P_ACDCACsummarycircuit_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_ACDCACsummarycircuit_T * ) _ssGetModelBlockIO ( S ) ) ; memcpy ( & _rtB ->
B_31_96_768 [ 0 ] , & _rtP -> P_136 [ 0 ] , 14U * sizeof ( real_T ) ) ; _rtB
-> B_31_110_880 = _rtP -> P_137 ; _rtB -> B_31_111_888 = _rtP -> P_138 ; _rtB
-> B_31_112_896 = _rtP -> P_139 ; _rtB -> B_31_113_904 = _rtP -> P_140 ; _rtB
-> B_31_114_912 = _rtP -> P_141 ; _rtB -> B_31_115_920 = _rtP -> P_142 ; _rtB
-> B_31_116_928 = _rtP -> P_143 ; _rtB -> B_31_125_979 = ( _rtP -> P_144 !=
0.0 ) ; _rtB -> B_31_126_980 = ! _rtB -> B_31_125_979 ; _rtB -> B_31_127_981
= ( _rtP -> P_145 != 0.0 ) ; _rtB -> B_31_128_982 = ! _rtB -> B_31_127_981 ;
_rtB -> B_31_129_983 = ( _rtP -> P_146 != 0.0 ) ; _rtB -> B_31_130_984 = !
_rtB -> B_31_129_983 ; _rtB -> B_31_131_985 = ( _rtP -> P_147 != 0.0 ) ; _rtB
-> B_31_132_986 = ! _rtB -> B_31_131_985 ; _rtB -> B_31_133_987 = ( _rtP ->
P_148 != 0.0 ) ; _rtB -> B_31_134_988 = ! _rtB -> B_31_133_987 ; _rtB ->
B_31_117_936 = _rtP -> P_149 ; _rtB -> B_31_118_944 = _rtP -> P_150 ; _rtB ->
B_31_119_952 = _rtP -> P_151 ; _rtB -> B_31_120_960 = _rtP -> P_152 ;
UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) {
B_ACDCACsummarycircuit_T * _rtB ; DW_ACDCACsummarycircuit_T * _rtDW ;
P_ACDCACsummarycircuit_T * _rtP ; int32_T isHit ; _rtDW = ( (
DW_ACDCACsummarycircuit_T * ) ssGetRootDWork ( S ) ) ; _rtP = ( (
P_ACDCACsummarycircuit_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_ACDCACsummarycircuit_T * ) _ssGetModelBlockIO ( S ) ) ; isHit =
ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { ssCallAccelRunBlock ( S ,
31 , 1 , SS_CALL_MDL_UPDATE ) ; } { real_T * * uBuffer = ( real_T * * ) &
_rtDW -> T_PWORK . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S ) ; _rtDW
-> T_IWORK . Head = ( ( _rtDW -> T_IWORK . Head < ( _rtDW -> T_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> T_IWORK . Head + 1 ) : 0 ) ; if ( _rtDW
-> T_IWORK . Head == _rtDW -> T_IWORK . Tail ) { if ( !
ACDCACsummarycircuit_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW -> T_IWORK .
CircularBufSize , & _rtDW -> T_IWORK . Tail , & _rtDW -> T_IWORK . Head , &
_rtDW -> T_IWORK . Last , simTime - _rtP -> P_42 , uBuffer , ( boolean_T ) 0
, false , & _rtDW -> T_IWORK . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * uBuffer + _rtDW ->
T_IWORK . CircularBufSize ) [ _rtDW -> T_IWORK . Head ] = simTime ; ( *
uBuffer ) [ _rtDW -> T_IWORK . Head ] = _rtB -> B_31_54_432 ; } { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> T1_PWORK . TUbufferPtrs [ 0 ] ; real_T
simTime = ssGetT ( S ) ; _rtDW -> T1_IWORK . Head = ( ( _rtDW -> T1_IWORK .
Head < ( _rtDW -> T1_IWORK . CircularBufSize - 1 ) ) ? ( _rtDW -> T1_IWORK .
Head + 1 ) : 0 ) ; if ( _rtDW -> T1_IWORK . Head == _rtDW -> T1_IWORK . Tail
) { if ( ! ACDCACsummarycircuit_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
T1_IWORK . CircularBufSize , & _rtDW -> T1_IWORK . Tail , & _rtDW -> T1_IWORK
. Head , & _rtDW -> T1_IWORK . Last , simTime - _rtP -> P_45 , uBuffer , (
boolean_T ) 0 , false , & _rtDW -> T1_IWORK . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
uBuffer + _rtDW -> T1_IWORK . CircularBufSize ) [ _rtDW -> T1_IWORK . Head ]
= simTime ; ( * uBuffer ) [ _rtDW -> T1_IWORK . Head ] = _rtB -> B_31_55_440
; } { real_T * * uBuffer = ( real_T * * ) & _rtDW -> T_PWORK_f . TUbufferPtrs
[ 0 ] ; real_T simTime = ssGetT ( S ) ; _rtDW -> T_IWORK_f . Head = ( ( _rtDW
-> T_IWORK_f . Head < ( _rtDW -> T_IWORK_f . CircularBufSize - 1 ) ) ? (
_rtDW -> T_IWORK_f . Head + 1 ) : 0 ) ; if ( _rtDW -> T_IWORK_f . Head ==
_rtDW -> T_IWORK_f . Tail ) { if ( !
ACDCACsummarycircuit_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW -> T_IWORK_f
. CircularBufSize , & _rtDW -> T_IWORK_f . Tail , & _rtDW -> T_IWORK_f . Head
, & _rtDW -> T_IWORK_f . Last , simTime - _rtP -> P_48 , uBuffer , (
boolean_T ) 0 , false , & _rtDW -> T_IWORK_f . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
uBuffer + _rtDW -> T_IWORK_f . CircularBufSize ) [ _rtDW -> T_IWORK_f . Head
] = simTime ; ( * uBuffer ) [ _rtDW -> T_IWORK_f . Head ] = _rtB ->
B_31_56_448 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW -> T1_PWORK_j .
TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S ) ; _rtDW -> T1_IWORK_h .
Head = ( ( _rtDW -> T1_IWORK_h . Head < ( _rtDW -> T1_IWORK_h .
CircularBufSize - 1 ) ) ? ( _rtDW -> T1_IWORK_h . Head + 1 ) : 0 ) ; if (
_rtDW -> T1_IWORK_h . Head == _rtDW -> T1_IWORK_h . Tail ) { if ( !
ACDCACsummarycircuit_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW -> T1_IWORK_h
. CircularBufSize , & _rtDW -> T1_IWORK_h . Tail , & _rtDW -> T1_IWORK_h .
Head , & _rtDW -> T1_IWORK_h . Last , simTime - _rtP -> P_51 , uBuffer , (
boolean_T ) 0 , false , & _rtDW -> T1_IWORK_h . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
uBuffer + _rtDW -> T1_IWORK_h . CircularBufSize ) [ _rtDW -> T1_IWORK_h .
Head ] = simTime ; ( * uBuffer ) [ _rtDW -> T1_IWORK_h . Head ] = _rtB ->
B_31_57_456 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S ) ;
_rtDW -> TransportDelay_IWORK . Head = ( ( _rtDW -> TransportDelay_IWORK .
Head < ( _rtDW -> TransportDelay_IWORK . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay_IWORK . Head + 1 ) : 0 ) ; if ( _rtDW -> TransportDelay_IWORK
. Head == _rtDW -> TransportDelay_IWORK . Tail ) { if ( !
ACDCACsummarycircuit_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK . CircularBufSize , & _rtDW -> TransportDelay_IWORK .
Tail , & _rtDW -> TransportDelay_IWORK . Head , & _rtDW ->
TransportDelay_IWORK . Last , simTime - _rtP -> P_58 , uBuffer , ( boolean_T
) 0 , false , & _rtDW -> TransportDelay_IWORK . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
uBuffer + _rtDW -> TransportDelay_IWORK . CircularBufSize ) [ _rtDW ->
TransportDelay_IWORK . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay_IWORK . Head ] = _rtB -> B_31_60_480 ; } isHit = ssIsSampleHit
( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW -> Memory_PreviousInput = _rtB ->
B_31_63_504 ; } ACDCACsummarycircuit_TrueRMS_Update ( S , & _rtB -> TrueRMS_o
, & _rtDW -> TrueRMS_o , & _rtP -> TrueRMS_o ) ;
ACDCACsummarycircuit_RMS_Update ( S , & _rtB -> RMS_g , & _rtDW -> RMS_g , &
_rtP -> RMS_g ) ; { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_f . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S ) ;
_rtDW -> TransportDelay_IWORK_o . Head = ( ( _rtDW -> TransportDelay_IWORK_o
. Head < ( _rtDW -> TransportDelay_IWORK_o . CircularBufSize - 1 ) ) ? (
_rtDW -> TransportDelay_IWORK_o . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay_IWORK_o . Head == _rtDW -> TransportDelay_IWORK_o . Tail ) {
if ( ! ACDCACsummarycircuit_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_o . CircularBufSize , & _rtDW -> TransportDelay_IWORK_o
. Tail , & _rtDW -> TransportDelay_IWORK_o . Head , & _rtDW ->
TransportDelay_IWORK_o . Last , simTime - _rtP -> P_63 , uBuffer , (
boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_o . MaxNewBufSize ) )
{ ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } (
* uBuffer + _rtDW -> TransportDelay_IWORK_o . CircularBufSize ) [ _rtDW ->
TransportDelay_IWORK_o . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay_IWORK_o . Head ] = _rtB -> B_31_64_512 ; } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW ->
Memory_PreviousInput_p = _rtB -> B_31_67_536 ; }
ACDCACsummarycircuit_TrueRMS_Update ( S , & _rtB -> TrueRMS_f , & _rtDW ->
TrueRMS_f , & _rtP -> TrueRMS_f ) ; ACDCACsummarycircuit_RMS_Update ( S , &
_rtB -> RMS_ge , & _rtDW -> RMS_ge , & _rtP -> RMS_ge ) ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> T_PWORK_fh . TUbufferPtrs [ 0 ] ; real_T
simTime = ssGetT ( S ) ; _rtDW -> T_IWORK_o . Head = ( ( _rtDW -> T_IWORK_o .
Head < ( _rtDW -> T_IWORK_o . CircularBufSize - 1 ) ) ? ( _rtDW -> T_IWORK_o
. Head + 1 ) : 0 ) ; if ( _rtDW -> T_IWORK_o . Head == _rtDW -> T_IWORK_o .
Tail ) { if ( ! ACDCACsummarycircuit_acc_rt_TDelayUpdateTailOrGrowBuf ( &
_rtDW -> T_IWORK_o . CircularBufSize , & _rtDW -> T_IWORK_o . Tail , & _rtDW
-> T_IWORK_o . Head , & _rtDW -> T_IWORK_o . Last , simTime - _rtP -> P_72 ,
uBuffer , ( boolean_T ) 0 , false , & _rtDW -> T_IWORK_o . MaxNewBufSize ) )
{ ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } (
* uBuffer + _rtDW -> T_IWORK_o . CircularBufSize ) [ _rtDW -> T_IWORK_o .
Head ] = simTime ; ( * uBuffer ) [ _rtDW -> T_IWORK_o . Head ] = _rtB ->
B_31_69_552 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW -> T1_PWORK_h .
TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S ) ; _rtDW -> T1_IWORK_hc .
Head = ( ( _rtDW -> T1_IWORK_hc . Head < ( _rtDW -> T1_IWORK_hc .
CircularBufSize - 1 ) ) ? ( _rtDW -> T1_IWORK_hc . Head + 1 ) : 0 ) ; if (
_rtDW -> T1_IWORK_hc . Head == _rtDW -> T1_IWORK_hc . Tail ) { if ( !
ACDCACsummarycircuit_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
T1_IWORK_hc . CircularBufSize , & _rtDW -> T1_IWORK_hc . Tail , & _rtDW ->
T1_IWORK_hc . Head , & _rtDW -> T1_IWORK_hc . Last , simTime - _rtP -> P_75 ,
uBuffer , ( boolean_T ) 0 , false , & _rtDW -> T1_IWORK_hc . MaxNewBufSize )
) { ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } }
( * uBuffer + _rtDW -> T1_IWORK_hc . CircularBufSize ) [ _rtDW -> T1_IWORK_hc
. Head ] = simTime ; ( * uBuffer ) [ _rtDW -> T1_IWORK_hc . Head ] = _rtB ->
B_31_70_560 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW -> T_PWORK_h .
TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S ) ; _rtDW -> T_IWORK_fa .
Head = ( ( _rtDW -> T_IWORK_fa . Head < ( _rtDW -> T_IWORK_fa .
CircularBufSize - 1 ) ) ? ( _rtDW -> T_IWORK_fa . Head + 1 ) : 0 ) ; if (
_rtDW -> T_IWORK_fa . Head == _rtDW -> T_IWORK_fa . Tail ) { if ( !
ACDCACsummarycircuit_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW -> T_IWORK_fa
. CircularBufSize , & _rtDW -> T_IWORK_fa . Tail , & _rtDW -> T_IWORK_fa .
Head , & _rtDW -> T_IWORK_fa . Last , simTime - _rtP -> P_78 , uBuffer , (
boolean_T ) 0 , false , & _rtDW -> T_IWORK_fa . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
uBuffer + _rtDW -> T_IWORK_fa . CircularBufSize ) [ _rtDW -> T_IWORK_fa .
Head ] = simTime ; ( * uBuffer ) [ _rtDW -> T_IWORK_fa . Head ] = _rtB ->
B_31_71_568 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW -> T1_PWORK_hj
. TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S ) ; _rtDW -> T1_IWORK_c .
Head = ( ( _rtDW -> T1_IWORK_c . Head < ( _rtDW -> T1_IWORK_c .
CircularBufSize - 1 ) ) ? ( _rtDW -> T1_IWORK_c . Head + 1 ) : 0 ) ; if (
_rtDW -> T1_IWORK_c . Head == _rtDW -> T1_IWORK_c . Tail ) { if ( !
ACDCACsummarycircuit_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW -> T1_IWORK_c
. CircularBufSize , & _rtDW -> T1_IWORK_c . Tail , & _rtDW -> T1_IWORK_c .
Head , & _rtDW -> T1_IWORK_c . Last , simTime - _rtP -> P_81 , uBuffer , (
boolean_T ) 0 , false , & _rtDW -> T1_IWORK_c . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
uBuffer + _rtDW -> T1_IWORK_c . CircularBufSize ) [ _rtDW -> T1_IWORK_c .
Head ] = simTime ; ( * uBuffer ) [ _rtDW -> T1_IWORK_c . Head ] = _rtB ->
B_31_72_576 ; } ACDCACsummarycircuit_TrueRMS_Update ( S , & _rtB -> TrueRMS_i
, & _rtDW -> TrueRMS_i , & _rtP -> TrueRMS_i ) ;
ACDCACsummarycircuit_RMS_Update ( S , & _rtB -> RMS_l , & _rtDW -> RMS_l , &
_rtP -> RMS_l ) ; { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_l . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S ) ;
_rtDW -> TransportDelay_IWORK_h . Head = ( ( _rtDW -> TransportDelay_IWORK_h
. Head < ( _rtDW -> TransportDelay_IWORK_h . CircularBufSize - 1 ) ) ? (
_rtDW -> TransportDelay_IWORK_h . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay_IWORK_h . Head == _rtDW -> TransportDelay_IWORK_h . Tail ) {
if ( ! ACDCACsummarycircuit_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_h . CircularBufSize , & _rtDW -> TransportDelay_IWORK_h
. Tail , & _rtDW -> TransportDelay_IWORK_h . Head , & _rtDW ->
TransportDelay_IWORK_h . Last , simTime - _rtP -> P_88 , uBuffer , (
boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_h . MaxNewBufSize ) )
{ ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } (
* uBuffer + _rtDW -> TransportDelay_IWORK_h . CircularBufSize ) [ _rtDW ->
TransportDelay_IWORK_h . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay_IWORK_h . Head ] = _rtB -> B_31_76_608 ; } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW ->
Memory_PreviousInput_pe = _rtB -> B_31_79_632 ; }
ACDCACsummarycircuit_TrueRMS_Update ( S , & _rtB -> TrueRMS_k , & _rtDW ->
TrueRMS_k , & _rtP -> TrueRMS_k ) ; ACDCACsummarycircuit_RMS_Update ( S , &
_rtB -> RMS_i , & _rtDW -> RMS_i , & _rtP -> RMS_i ) ;
ACDCACsummarycircuit_TrueRMS_Update ( S , & _rtB -> TrueRMS , & _rtDW ->
TrueRMS , & _rtP -> TrueRMS ) ; ACDCACsummarycircuit_RMS_Update ( S , & _rtB
-> RMS , & _rtDW -> RMS , & _rtP -> RMS ) ; isHit = ssIsSampleHit ( S , 1 , 0
) ; if ( isHit != 0 ) { _rtDW -> Memory_PreviousInput_b = _rtB ->
B_31_123_977 ; } UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdateTID3 ( SimStruct * S , int_T tid ) { UNUSED_PARAMETER (
tid ) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) { B_ACDCACsummarycircuit_T *
_rtB ; DW_ACDCACsummarycircuit_T * _rtDW ; P_ACDCACsummarycircuit_T * _rtP ;
XDot_ACDCACsummarycircuit_T * _rtXdot ; X_ACDCACsummarycircuit_T * _rtX ;
_rtDW = ( ( DW_ACDCACsummarycircuit_T * ) ssGetRootDWork ( S ) ) ; _rtXdot =
( ( XDot_ACDCACsummarycircuit_T * ) ssGetdX ( S ) ) ; _rtX = ( (
X_ACDCACsummarycircuit_T * ) ssGetContStates ( S ) ) ; _rtP = ( (
P_ACDCACsummarycircuit_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_ACDCACsummarycircuit_T * ) _ssGetModelBlockIO ( S ) ) ; _rtXdot -> _CSTATE
= 0.0 ; _rtXdot -> _CSTATE += _rtP -> P_18 * _rtX -> _CSTATE ; _rtXdot ->
_CSTATE += _rtB -> B_31_95_760 ; ACDCACsummarycircuit_PR_Deriv ( S , & _rtB
-> PR , & _rtP -> PR , & _rtX -> PR , & _rtXdot -> PR ) ; _rtXdot ->
TransferFcn_CSTATE [ 0 ] = 0.0 ; _rtXdot -> TransferFcn_CSTATE [ 0 ] += _rtP
-> P_27 [ 0 ] * _rtX -> TransferFcn_CSTATE [ 0 ] ; _rtXdot ->
TransferFcn_CSTATE [ 1 ] = 0.0 ; _rtXdot -> TransferFcn_CSTATE [ 0 ] += _rtP
-> P_27 [ 1 ] * _rtX -> TransferFcn_CSTATE [ 1 ] ; _rtXdot ->
TransferFcn_CSTATE [ 1 ] += _rtX -> TransferFcn_CSTATE [ 0 ] ; _rtXdot ->
TransferFcn_CSTATE [ 0 ] += _rtB -> B_31_36_288 ; _rtXdot ->
Integrator_CSTATE = _rtB -> B_31_82_656 ; ACDCACsummarycircuit_PR_Deriv ( S ,
& _rtB -> PR_i , & _rtP -> PR_i , & _rtX -> PR_i , & _rtXdot -> PR_i ) ;
_rtXdot -> integ1_CSTATE = _rtB -> B_31_87_696 ; _rtXdot -> Integ2_CSTATE =
_rtB -> B_31_88_704 ; _rtXdot -> integ1_CSTATE_m = _rtB -> B_31_84_672 ;
_rtXdot -> Integ2_CSTATE_a = _rtB -> B_31_85_680 ; _rtXdot ->
integrator_CSTATE = _rtB -> B_31_44_352 ; ACDCACsummarycircuit_TrueRMS_Deriv
( S , & _rtB -> TrueRMS_o , & _rtDW -> TrueRMS_o , & _rtXdot -> TrueRMS_o ) ;
ACDCACsummarycircuit_RMS_Deriv ( S , & _rtB -> RMS_g , & _rtDW -> RMS_g , &
_rtXdot -> RMS_g ) ; _rtXdot -> integrator_CSTATE_n = _rtB -> B_31_63_504 ;
ACDCACsummarycircuit_TrueRMS_Deriv ( S , & _rtB -> TrueRMS_f , & _rtDW ->
TrueRMS_f , & _rtXdot -> TrueRMS_f ) ; ACDCACsummarycircuit_RMS_Deriv ( S , &
_rtB -> RMS_ge , & _rtDW -> RMS_ge , & _rtXdot -> RMS_ge ) ; _rtXdot ->
integ1_CSTATE_p = _rtB -> B_31_93_744 ; _rtXdot -> Integ2_CSTATE_o = _rtB ->
B_31_94_752 ; _rtXdot -> integ1_CSTATE_i = _rtB -> B_31_90_720 ; _rtXdot ->
Integ2_CSTATE_c = _rtB -> B_31_91_728 ; ACDCACsummarycircuit_TrueRMS_Deriv (
S , & _rtB -> TrueRMS_i , & _rtDW -> TrueRMS_i , & _rtXdot -> TrueRMS_i ) ;
ACDCACsummarycircuit_RMS_Deriv ( S , & _rtB -> RMS_l , & _rtDW -> RMS_l , &
_rtXdot -> RMS_l ) ; _rtXdot -> integrator_CSTATE_e = _rtB -> B_31_53_424 ;
ACDCACsummarycircuit_TrueRMS_Deriv ( S , & _rtB -> TrueRMS_k , & _rtDW ->
TrueRMS_k , & _rtXdot -> TrueRMS_k ) ; ACDCACsummarycircuit_RMS_Deriv ( S , &
_rtB -> RMS_i , & _rtDW -> RMS_i , & _rtXdot -> RMS_i ) ;
ACDCACsummarycircuit_TrueRMS_Deriv ( S , & _rtB -> TrueRMS , & _rtDW ->
TrueRMS , & _rtXdot -> TrueRMS ) ; ACDCACsummarycircuit_RMS_Deriv ( S , &
_rtB -> RMS , & _rtDW -> RMS , & _rtXdot -> RMS ) ; } static void
mdlInitializeSizes ( SimStruct * S ) { ssSetChecksumVal ( S , 0 , 377185424U
) ; ssSetChecksumVal ( S , 1 , 2961424570U ) ; ssSetChecksumVal ( S , 2 ,
2062734004U ) ; ssSetChecksumVal ( S , 3 , 46465600U ) ; { mxArray *
slVerStructMat = ( NULL ) ; mxArray * slStrMat = mxCreateString ( "simulink"
) ; char slVerChar [ 10 ] ; int status = mexCallMATLAB ( 1 , & slVerStructMat
, 1 , & slStrMat , "ver" ) ; if ( status == 0 ) { mxArray * slVerMat =
mxGetField ( slVerStructMat , 0 , "Version" ) ; if ( slVerMat == ( NULL ) ) {
status = 1 ; } else { status = mxGetString ( slVerMat , slVerChar , 10 ) ; }
} mxDestroyArray ( slStrMat ) ; mxDestroyArray ( slVerStructMat ) ; if ( (
status == 1 ) || ( strcmp ( slVerChar , "23.2" ) != 0 ) ) { return ; } }
ssSetOptions ( S , SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork (
S ) != ( SLSize ) sizeof ( DW_ACDCACsummarycircuit_T ) ) { static char msg [
256 ] ; snprintf ( msg , 256 , "Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file (%ld vs %lu)." , ( signed long )
ssGetSizeofDWork ( S ) , ( unsigned long ) sizeof ( DW_ACDCACsummarycircuit_T
) ) ; ssSetErrorStatus ( S , msg ) ; } if ( ssGetSizeofGlobalBlockIO ( S ) !=
( SLSize ) sizeof ( B_ACDCACsummarycircuit_T ) ) { static char msg [ 256 ] ;
snprintf ( msg , 256 , "Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file (%ld vs %lu)." , ( signed long )
ssGetSizeofGlobalBlockIO ( S ) , ( unsigned long ) sizeof (
B_ACDCACsummarycircuit_T ) ) ; ssSetErrorStatus ( S , msg ) ; } { int
ssSizeofParams ; ssGetSizeofParams ( S , & ssSizeofParams ) ; if (
ssSizeofParams != sizeof ( P_ACDCACsummarycircuit_T ) ) { static char msg [
256 ] ; snprintf ( msg , 256 ,
"Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file (%d vs %lu)." , ssSizeofParams , (
unsigned long ) sizeof ( P_ACDCACsummarycircuit_T ) ) ; ssSetErrorStatus ( S
, msg ) ; } } _ssSetModelRtp ( S , ( real_T * ) &
ACDCACsummarycircuit_rtDefaultP ) ; _ssSetConstBlockIO ( S , &
ACDCACsummarycircuit_rtInvariant ) ; rt_InitInfAndNaN ( sizeof ( real_T ) ) ;
( ( P_ACDCACsummarycircuit_T * ) ssGetModelRtp ( S ) ) -> P_67 = rtInf ; ( (
P_ACDCACsummarycircuit_T * ) ssGetModelRtp ( S ) ) -> P_69 = rtInf ; ( (
P_ACDCACsummarycircuit_T * ) ssGetModelRtp ( S ) ) -> P_92 = rtInf ; ( (
P_ACDCACsummarycircuit_T * ) ssGetModelRtp ( S ) ) -> P_94 = rtInf ; ( (
P_ACDCACsummarycircuit_T * ) ssGetModelRtp ( S ) ) -> TrueRMS_f . P_7 = rtInf
; ( ( P_ACDCACsummarycircuit_T * ) ssGetModelRtp ( S ) ) -> TrueRMS_o . P_7 =
rtInf ; ( ( P_ACDCACsummarycircuit_T * ) ssGetModelRtp ( S ) ) -> TrueRMS_k .
P_7 = rtInf ; ( ( P_ACDCACsummarycircuit_T * ) ssGetModelRtp ( S ) ) ->
TrueRMS_i . P_7 = rtInf ; ( ( P_ACDCACsummarycircuit_T * ) ssGetModelRtp ( S
) ) -> TrueRMS . P_7 = rtInf ; } static void mdlInitializeSampleTimes (
SimStruct * S ) { { SimStruct * childS ; SysOutputFcn * callSysFcns ; childS
= ssGetSFunction ( S , 0 ) ; callSysFcns = ssGetCallSystemOutputFcnList (
childS ) ; callSysFcns [ 3 + 0 ] = ( SysOutputFcn ) ( NULL ) ; }
slAccRegPrmChangeFcn ( S , mdlOutputsTID3 ) ; } static void mdlTerminate (
SimStruct * S ) { }
#include "simulink.c"
