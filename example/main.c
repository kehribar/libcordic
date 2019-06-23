// ----------------------------------------------------------------------------
// 
// 
// ----------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "libcordic.h"

// ----------------------------------------------------------------------------
#ifndef M_PI
#define M_PI 3.14159265359
#endif

// ----------------------------------------------------------------------------
static void ground_truth(float i, float q, float* rms, float* phase_rad)
{
  (*rms) = sqrtf((i*i)+(q*q));
  (*phase_rad) = atan2f(q,i);
}

// ----------------------------------------------------------------------------
int main(int argc, char const *argv[])
{
  int32_t i;
  int32_t q;
  float rms_truth;
  float phase_truth;
  int32_t rms_cordic;
  int32_t phase_cordic;
  float phase_cordic_rad;
  float rms_cordic_corrected;

  // ...
  int32_t start = LIBCORDIC_INP_MIN;
  int32_t end = LIBCORDIC_INP_MAX;
  int32_t increment = end / 1024.0;

  // ...
  FILE* fp = fopen("err_log.txt", "w+");
  float max_rms_err = __FLT_MIN__;
  float max_phase_err = __FLT_MIN__;
  for(i=start;i<end;i+=increment)
  {
    for(q=start;q<end;q+=increment)
    {
      if((i != 0.0) || (q != 0.0))
      {
        // ...
        ground_truth(i,q,&rms_truth,&phase_truth);
        libcordic_rotate(i,q,&rms_cordic,&phase_cordic);

        // ...
        rms_cordic_corrected = rms_cordic / LIBCORDIC_GAIN;
        phase_cordic_rad = phase_cordic * M_PI / (float)LIBCORDIC_M_PI;
        
        // ...
        float err_r = rms_cordic_corrected - rms_truth;
        float err_p = phase_cordic_rad - phase_truth;
        fprintf(fp, "%13d, %13d, %13.1f, %9.6f\n",
          i,q,err_r,err_p
        );

        // ...
        if(fabsf(err_r) > max_rms_err)
        {
          max_rms_err = fabsf(err_r);
        }

        // ...
        if(fabsf(err_p) > max_phase_err)
        {
          max_phase_err = fabsf(err_p);
        }
      }
    }
  }

  // ...
  printf("\n");
  printf("Final Error Table\n");
  printf("-----------------\n");
  printf("Max RMS error:   %d (raw)\n", (int32_t)max_rms_err);
  printf("Max RMS error:   %f (relative)\n", 
    (float)max_rms_err / (LIBCORDIC_INP_MAX - LIBCORDIC_INP_MIN)
  );
  printf("Max Phase error: %f (rad)\n", max_phase_err);
  printf("Max Phase error: %f (deg)\n", max_phase_err * 180.0 / M_PI);

  // ...
  fclose(fp);
  printf("\n");
  return 0;
}