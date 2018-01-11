#ifndef __MODBUS_TYPE_H__
#define __MODBUS_TYPE_H__

#ifdef STM32F10X_HD
#include "stm32f10x.h"
#else
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
#endif


#define false	0
#define	true	1
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
#ifndef __cplusplus
typedef unsigned int   bool;
#endif//cplusplus

#endif//__MODBUS_TYPE_H__
