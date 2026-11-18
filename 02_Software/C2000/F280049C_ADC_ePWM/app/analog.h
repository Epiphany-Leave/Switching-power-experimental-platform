/*
 * analog.h
 *
 *  Created on: 2025年12月20日
 *      Author: 45276
 */

#ifndef SRC_ANALOG_H_
#define SRC_ANALOG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//
// Inert：惯性滤波器
//
typedef struct
{
    int32_t level;   // 滤波强度
    int32_t value;   // 当前滤波值
    int32_t slide;   // 滑动窗口值（原来是 long）
} Inert_t;

void  Inert_init(Inert_t *f, int32_t level);
void  Inert_next(Inert_t *f, int32_t ad);
int32_t Inert_getValue(const Inert_t *f);
float Inert_getRealValue(const Inert_t *f, int32_t offset, float gain);


//
// Rms：滑动窗口 RMS/平均值
// 说明：固定窗口长度，避免动态分配
//
#ifndef RMS_MAX_LENGTH
#define RMS_MAX_LENGTH 256   // 你可以按需要改（例如 64/128/256）
#endif

typedef struct
{
    int32_t length;                 // 实际窗口长度（<= RMS_MAX_LENGTH）
    int32_t ad_index;               // 当前索引
    int32_t ad_data[RMS_MAX_LENGTH];// 环形缓冲区

    int64_t ad2_sum;                // 平方和（用 64 位更稳）
    int64_t ad_sum;                 // 和
    int32_t ad_avg;                 // 平均值
    float   flength;                // 1/length
    float   rmsValue;               // RMS
} Rms_t;

// length 必须 1..RMS_MAX_LENGTH
// 初始化会把 ad_data 清零、sum 清零
int  Rms_init(Rms_t *r, int32_t length);
void Rms_next(Rms_t *r, int32_t ad);
float Rms_getRmsValue(const Rms_t *r);
int32_t Rms_getAvgValue(const Rms_t *r);
int32_t Rms_getIndex(const Rms_t *r);

#ifdef __cplusplus
}
#endif

#endif /* SRC_ANALOG_H_ */


