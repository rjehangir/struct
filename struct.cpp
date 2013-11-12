#include "Struct.h"

namespace Struct {

#ifdef ARDUINO
template <>
double unpack<double>(uint8_t* packed, bool littleEndian) {
  union {
	float f;
	uint8_t b[4];
  } fn;    
  if ( littleEndian ) {
    int16_t expd = ((packed[7] & 127) << 4) + ((packed[6] & 240) >> 4);
    int16_t expf = expd ? (expd - 1024) + 128 : 0;
    fn.b[3] = (packed[7] & 128) + (expf >> 1);
    fn.b[2] = ((expf & 1) << 7) + ((packed[6] & 15) << 3) + ((packed[5] & 0xe0) >> 5);
    fn.b[1] = ((packed[5] & 0x1f) << 3) + ((packed[4] & 0xe0) >> 5);
    fn.b[0] = ((packed[4] & 0x1f) << 3) + ((packed[3] & 0xe0) >> 5);
  } else {
    int16_t expd = ((packed[0] & 127) << 4) + ((packed[1] & 240) >> 4);
    int16_t expf = expd ? (expd - 1024) + 128 : 0;
    fn.b[3] = (packed[0] & 128) + (expf >> 1);
    fn.b[2] = ((expf & 1) << 7) + ((packed[1] & 15) << 3) + ((packed[2] & 0xe0) >> 5);
    fn.b[1] = ((packed[2] & 0x1f) << 3) + ((packed[3] & 0xe0) >> 5);
    fn.b[0] = ((packed[3] & 0x1f) << 3) + ((packed[4] & 0xe0) >> 5);
  }  
  return fn.f;
} 
#endif
 
}