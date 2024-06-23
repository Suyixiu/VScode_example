#include "my_math.h"

void constrain_int(int *amt, int low, int high)
{
  if (*amt > high)
    *amt = high;
  if (*amt < low)
    *amt = low;
}

void constrain_float(float *amt, float low, float high)
{
  if (*amt > high)
    *amt = high;
  if (*amt < low)
    *amt = low;
}

void fabs_limit(float *amt, float ABS_MAX)
{
  if (*amt > ABS_MAX)
    *amt = ABS_MAX;
  if (*amt < -ABS_MAX)
    *amt = -ABS_MAX;
}

void moving_average_filter(float data, u8 num, float *filter_out)
{
  u8 i;
  float data_buf[num + 1];
  float data_sum = 0;

  data_buf[num] = data;
  for (i = 0; i < num; i++)
  {
    data_buf[i] = data_buf[i + 1];
    data_sum += data_buf[i];
  }
  *filter_out = data_sum / num;
}
