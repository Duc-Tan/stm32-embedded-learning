#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>

void SPI1_Init(void);
void SPI1_Read_Data(uint16_t reg, uint8_t* val);
void SPI1_Write_Data(uint16_t reg, uint16_t data);

#endif /* SPI_H_ */