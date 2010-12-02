#ifndef _SPI_H
#define _SPI_H
#include "stm32f10x.h"
void SpiInit(void);  //SPI初始化函数
void SpiSendByte(uint8_t byte);  //SPI数据发送函数

#endif
