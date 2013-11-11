struct
======

C++ namespace for converting binary data in byte arrays to typed values mimicking the functionality of the Python "struct" class. The namespace was made primarily for embedded (Arduino) projects where binary data is sent through the serial port, however, the namespace can be used with any C++ code.

The namespace provides two functions:

```c++
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
T unpack(uint8_t* packed, bool littleEndian=true);

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
void pack(T* unpacked, uint8_t* packed, bool littleEndian=true);
```
These functions perform similarly to "pack" and "unpack" in the Python struct class, however they are implemented with templates instead of string identifiers. The following blocks show examples of how to use the functions to read and write binary data from and to the Arduino serial port.

```
void setup() {
  Serial.begin(115200);
}

void loop() {
  float a = 123.45;
  uint32_t b = 987654321;
  
  // Both float and uint32_t data types require 4 bytes, so the size of "data" is 8.
  uint8_t data[8];
  
  // Pack variables "a" and "b" into byte array and send.
  Struct::pack<float>(&a,&data[0]);
  Struct::pack<uint32_t>(&b,&data[4]);
  
  Serial.write(data);
  
  // Now, read in a byte array that contain new values for "a" and "b".
  while ( Serial.available() < 8 ) {} // Make sure that at least 8 bytes are available
  for ( uint8_t i = 0 ; i < 8 ; i++ ) {
    data[i] = Serial.read();
  }
  
  // Unpack binary data to values using "unpack"
  a = Struct::unpack<float>(&data[0]);
  b = Struct::unpack<uint32_t>&data[4]);
}
```

Note: The Arduino platform stores an 8-byte double as a 4-byte float (single). A specialized implementation of "unpack" is used for double to return it as a 4-byte float. There is no implementation of "pack" for a double yet. If someone knows how to convert a single float to a double byte array, please let me know.
  
  
