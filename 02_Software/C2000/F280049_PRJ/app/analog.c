/*
 * analog.c
 *
 *  Created on: 2025年12月20日
 *      Author: 45276
 */

#include "analog.h"
#include <math.h>   // sqrtf

//
// -------- Inert --------
//
void Inert_init(Inert_t *f, int32_t level)
{
    if (!f) return;
    f->level = level;
    f->value = 0;
    f->slide = 0;
}

void Inert_next(Inert_t *f, int32_t ad)
{
    if (!f) return;

    f->slide = f->slide + ad - f->value;

    if (f->slide >= 0)
    {
        f->value = (int32_t)(f->slide >> f->level);
    }
    else
    {
        int32_t neg = -f->slide;
        f->value = -(int32_t)(neg >> f->level);
    }
}

int32_t Inert_getValue(const Inert_t *f)
{
    return f ? f->value : 0;
}

float Inert_getRealValue(const Inert_t *f, int32_t offset, float gain)
{
    return (float)(Inert_getValue(f) - offset) * gain;
}

//
// -------- Rms --------
//
// 注意：原来的实现存在一个“顺序问题”：先写入 ad_data[ad_index]，再用 ad_data[ad_index]
// 当作“被踢出的旧值”，会把新值当旧值减掉，sum 会不对。
// 这里我用标准环形缓冲写法：
// 1) 取出 old = ad_data[idx]
// 2) 用新值替换
// 3) sum += new - old
//
static void Rms_clear(Rms_t *r)
{
    int i;
    for (i = 0; i < RMS_MAX_LENGTH; ++i) r->ad_data[i] = 0;
    r->ad2_sum  = 0;
    r->ad_sum   = 0;
    r->ad_avg   = 0;
    r->ad_index = 0;
    r->rmsValue = 0.0f;
}

int Rms_init(Rms_t *r, int32_t length)
{
    if (!r) return -1;
    if (length <= 0 || length > RMS_MAX_LENGTH) return -2;

    r->length  = length;
    r->flength = 1.0f / (float)length;
    Rms_clear(r);
    return 0;
}

void Rms_next(Rms_t *r, int32_t ad)
{
    if (!r || r->length <= 0) return;

    int32_t idx = r->ad_index;
    int32_t old = r->ad_data[idx];

    // 更新环形缓冲
    r->ad_data[idx] = ad;
    r->ad_index = (idx + 1) % r->length;

    // 更新 sum / avg
    r->ad_sum += (int64_t)ad - (int64_t)old;
    r->ad_avg = (int32_t)(r->ad_sum / (int64_t)r->length);

    // 更新平方和
    r->ad2_sum += (int64_t)ad * (int64_t)ad - (int64_t)old * (int64_t)old;

    // 计算 RMS
    // 你原式：sqrtf(ad2_sum - ad_sum * ad_avg) * flength
    // 其中 ad_sum*ad_avg 量纲不太严谨，但我保持“接近原意”的形式，
    // 同时避免负数开方：如果数值误差导致 <0，则钳到 0。
    int64_t var_like = r->ad2_sum - r->ad_sum * (int64_t)r->ad_avg;
    if (var_like < 0) var_like = 0;

    r->rmsValue = sqrtf((float)var_like) * r->flength;
}

float Rms_getRmsValue(const Rms_t *r)
{
    return r ? r->rmsValue : 0.0f;
}

int32_t Rms_getAvgValue(const Rms_t *r)
{
    return r ? r->ad_avg : 0;
}

int32_t Rms_getIndex(const Rms_t *r)
{
    return r ? r->ad_index : 0;
}






