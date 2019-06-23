# -----------------------------------------------------------------------------
# 
# 
# -----------------------------------------------------------------------------
import math
import numpy as np

# ...
INPUT_RANGE_BITS = 30
PHASE_RESOLUTION_BITS = 32
CORDIC_ITERATION_AMOUNT = 24

# ...
def cordic_rad_toNormAngle(rad):
  scale = math.pi / (pow(2,(PHASE_RESOLUTION_BITS-1)) - 1)
  return (rad / scale)

# ...
if __name__ == '__main__':
    
  # ...
  norm_angle = np.zeros(CORDIC_ITERATION_AMOUNT)
  for x in range(0,CORDIC_ITERATION_AMOUNT):
    tan_val = pow(2.0, -x);
    norm_angle[x] = cordic_rad_toNormAngle(math.atan(tan_val));

  # ...
  cordic_gain = 1.0
  for x in range(0,CORDIC_ITERATION_AMOUNT):
    dgain = math.sqrt(1.0 + pow(2.0, -2 * x));
    cordic_gain = cordic_gain * dgain;

  # ...
  fp = open('libcordic_constants.h', 'w+')
  fp.write("// ----------------------------------------------------------------------------\n")
  fp.write("// \n")
  fp.write("// \n")
  fp.write("// ----------------------------------------------------------------------------\n")
  fp.write("#ifndef LIBCORDIC_CONSTANTS\n")
  fp.write("#define LIBCORDIC_CONSTANTS\n")
  fp.write("\n")
  fp.write("// ----------------------------------------------------------------------------\n")
  fp.write("#include <stdint.h>\n")
  fp.write("\n")
  fp.write("// ----------------------------------------------------------------------------\n")
  fp.write("#define LIBCORDIC_ITERATION %d\n" % CORDIC_ITERATION_AMOUNT)
  fp.write("#define LIBCORDIC_GAIN %f\n" % cordic_gain)
  fp.write("#define LIBCORDIC_M_PI %d\n" % int(pow(2,(PHASE_RESOLUTION_BITS-1)) - 1))
  fp.write("\n")
  fp.write("// ----------------------------------------------------------------------------\n")
  fp.write("#define LIBCORDIC_INP_MAX %d\n" % int(pow(2,(INPUT_RANGE_BITS-1)) - 1))
  fp.write("#define LIBCORDIC_INP_MIN %d\n" % -int(pow(2,(INPUT_RANGE_BITS-1)) - 1))
  fp.write("\n")
  fp.write("// ----------------------------------------------------------------------------\n")
  fp.write("const int32_t libcordic_angleTable[LIBCORDIC_ITERATION] = {\n  ");
  for x in range(0,CORDIC_ITERATION_AMOUNT-1):
    dat = int(norm_angle[x])
    fp.write('{:9d}'.format(dat) + ', ')
    if((x % 5) == 4):
      fp.write('\n  ')
  fp.write('{:9d}'.format(int(norm_angle[-1])))
  fp.write('\n};\n')
  fp.write("\n")
  fp.write("// ----------------------------------------------------------------------------\n")
  fp.write("#endif")
  fp.close()