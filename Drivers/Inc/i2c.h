#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>

void I2C1_Init(void);
void I2C1_Write_Data(uint8_t addr, uint8_t reg, uint8_t data);
void I2C1_Read_Data(uint8_t addr,uint8_t reg , uint8_t* val);

#endif /* I2C_H_ */