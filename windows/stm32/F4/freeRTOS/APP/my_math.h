#ifndef __MY_MATH_H
#define __MY_MATH_H

#include "system.h"

#define abs(x) ((x) > 0 ? (x) : (-(x)))
#define BYTE0(dwTemp) (*(char *)(&dwTemp))
#define BYTE1(dwTemp) (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp) (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp) (*((char *)(&dwTemp) + 3))

void constrain_int(int *amt, int low, int high);
void constrain_float(float *amt, float low, float high);
void fabs_limit(float *amt, float ABS_MAX);

void critical_value_handle(float get, float *set, float mid);

void moving_average_filter(float data, u8 num, float *filter_out);

#endif
