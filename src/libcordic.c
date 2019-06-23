// ----------------------------------------------------------------------------
// 
// 
// ----------------------------------------------------------------------------
#include "libcordic.h"

// ----------------------------------------------------------------------------
void libcordic_rotate(int32_t i, int32_t q, int32_t* rms, int32_t* phase)
{
  int32_t x = i;
  int32_t y = q;
  int32_t total_rad = 0;

  // Handle special cases
  if((x == 0) && (y > 0))
  {
    (*rms) = y;
    (*phase) = LIBCORDIC_M_PI * 0.5;
    return;
  }
  else if((x == 0) && (y < 0))
  {
    (*rms) = -y;
    (*phase) = -LIBCORDIC_M_PI * 0.5;
    return;
  }
  else if((y == 0) && (x < 0))
  {
    (*rms) = -x;
    (*phase) = LIBCORDIC_M_PI;
    return; 
  }
  else if((y == 0) && (x > 0))
  {
    (*rms) = x;
    (*phase) = 0;
    return; 
  }

  // Pre rotation if needed
  if((x < 0.0) && (y < 0.0))
  {
    int32_t x_ = -x;
    int32_t y_ = -y;

    x = x_;
    y = y_;
    total_rad = -LIBCORDIC_M_PI;
  }
  else if((x < 0.0) && (y > 0.0))
  {
    int32_t x_ = -x;
    int32_t y_ = -y;

    x = x_;
    y = y_;
    total_rad = LIBCORDIC_M_PI;
  }

  // Run the rotation loop
  for(int j=0;j<LIBCORDIC_ITERATION;j++)
  {
    int32_t rot_rad = libcordic_angleTable[j];

    if(y < 0)
    {
      int32_t x_ = x - (y >> j);
      int32_t y_ = y + (x >> j);

      x = x_;
      y = y_;
      total_rad -= rot_rad;
    }
    else
    {
      int32_t x_ = x + (y >> j);
      int32_t y_ = y - (x >> j);

      x = x_;
      y = y_;
      total_rad += rot_rad; 
    }
  }

  // ...
  (*rms) = x;
  (*phase) = total_rad;
}
