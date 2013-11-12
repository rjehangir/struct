#ifndef STRUCT_H630903
#define STRUCT_H630903

#ifdef ARDUINO
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#endif

/** The struct namespace is named after the Python and Perl classes that
  * have similar functionality. Struct contains functions for packing and
  * unpacking binary data.
  */
namespace Struct {

/** This function converts packed binary data in a byte array to
  * templated type T. The function uses little endian by default but
  * an argument allows the use of big endian.
  *
  * @pre The size of the packed array must be equal to or greater than the 
  * sizeof(T) or incorrect results will be returned.
  *
  * @param packed Pointer to array of packed binary data.
  * @param littleEndian Set to true (default) if data is little endian format, false otherwise.
  * @return Copy of the unpacked value.
  */
template <class T>
T unpack(uint8_t* packed, bool littleEndian = true) {
  if ( littleEndian ) {
    return *reinterpret_cast<T*>(packed);
  } else {
    uint8_t backwards[sizeof(T)];
    for ( uint8_t i = 0 ; i < sizeof(T) ; i++ ) {
      backwards[i] = packed[sizeof(T)-i-1];
    }
    return *reinterpret_cast<T*>(backwards);
  }
}

#ifdef ARDUINO
/** Specialization of unpack for 8-byte double type which does not
  * exist on the AVR platform.
  *
  * @pre The size of the packed array must be equal to or greater than the 
  * sizeof(T) or incorrect results will be returned.
  *
  * @param packed Pointer to array of packed binary data.
  * @param littleEndian True for little endian format.
  * @return Copy of the unpacked value
  */
template <>
double unpack<double>(uint8_t* packed, bool littleEndian);
#endif

/** This function converts data of type T into a packed binary byte
  * array. The function uses little endian by default but an argument
  * allows the use of big endian.
  *
  * @pre The size of the packed array must be equal to or greater than 
  * sizeof(T) or data corruption may occur. Be careful.
  *
  * @param unpacked Pointer to data item to be packed into binary form.
  * @param packed Pointer to destination array for byte array.
  * @param littleEndian Set to true (default) to pack data in little endian format, false otherwise.
  */
template <class T>
void pack(T* unpacked, uint8_t* packed, bool littleEndian = true) {
  if ( littleEndian ) {
    for ( uint8_t i = 0 ; i < sizeof(T) ; i++ ) {
      packed[i] = reinterpret_cast<uint8_t*>(unpacked)[i];
    }
  } else {
    for ( uint8_t i = 0 ; i < sizeof(T) ; i++ ) {
      packed[i] = reinterpret_cast<uint8_t*>(unpacked)[sizeof(T)-i-1];
    }
  }
}

#ifdef ARDUINO
///todo Implement "pack" for double on the Arduino platform.
/** Specialization of pack for 8-byte double type which does not
  * exist on the AVR platform.
  *
  * @pre The size of the packed array must be equal to or greater than 
  * sizeof(T) or data corruption may occur. Be careful.
  *
  * @param unpacked Pointer to data item to be packed into binary form.
  * @param packed Pointer to destination array for byte array.
  * @param littleEndian Set to true (default) to pack data in little endian format, false otherwise.
  */
//template <>
//void pack<double>(double* unpacked, uint8_t* packed, bool littleEndian = true);
#endif
  
}

#endif
