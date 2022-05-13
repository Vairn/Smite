#pragma once
#include <stdint.h>
#include <stdlib.h>
#define IS_EVEN(x) (x%2?false:true)
#define IS_ODD(x) (x%2?true:false)

uint16_t swap_uint16(uint16_t val);

//! Byte swap short
int16_t swap_int16(int16_t val);

//! Byte swap unsigned int
uint32_t swap_uint32(uint32_t val);

//! Byte swap int
int32_t swap_int32(int32_t val);
#define BYTE4_TO_BINARY_PATTERN "%c%c%c%c"
#define BYTE4_TO_BINARY(byte)  \
   (byte & 0x08 ? '1' : '0'), \
   (byte & 0x04 ? '1' : '0'), \
   (byte & 0x02 ? '1' : '0'), \
   (byte & 0x01 ? '1' : '0')

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
   (byte & 0x80 ? '1' : '0'), \
   (byte & 0x40 ? '1' : '0'), \
   (byte & 0x20 ? '1' : '0'), \
   (byte & 0x10 ? '1' : '0'), \
   (byte & 0x08 ? '1' : '0'), \
   (byte & 0x04 ? '1' : '0'), \
   (byte & 0x02 ? '1' : '0'), \
   (byte & 0x01 ? '1' : '0')

