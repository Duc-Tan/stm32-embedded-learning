#include "i2c.h"

#define I2C1_BASE_ADDR            0x40005400
#define GPIOB_BASE_ADDR           0x40020400
#define RCC_BASE_ADDR       	  0x40023800

void I2C1_Init(){
	uint32_t* GPIOB_MODER = (uint32_t*)(GPIOB_BASE_ADDR + 0x00);
	uint32_t* GPIOB_AFRL = (uint32_t*)(GPIOB_BASE_ADDR + 0x20);
	uint32_t* GPIOB_AFRH = (uint32_t*)(GPIOB_BASE_ADDR + 0x24);
    uint32_t* RCC_AHB1ENR = (uint32_t*)(RCC_BASE_ADDR + 0x30);


    *RCC_AHB1ENR |= 1 << 1;
	*GPIOB_MODER &= ~(0b11 << 12);
	*GPIOB_MODER &= ~(0b11 << 18);
	*GPIOB_MODER |= 0b10 << 12;
	*GPIOB_MODER |= 0b10 << 18;

	*GPIOB_AFRL &= ~(0xf << 24);
	*GPIOB_AFRH &= ~(0xf << 4);
	*GPIOB_AFRL |= 4 << 24; // set PB6 is SCL
	*GPIOB_AFRH |= 4 << 4;  // set PB9 is SDA

	uint32_t* I2C1_CR2 = (uint32_t*)(I2C1_BASE_ADDR + 0x04);
	uint32_t* I2C1_CCR = (uint32_t*)(I2C1_BASE_ADDR + 0x1C);
	uint32_t* I2C1_CR1 = (uint32_t*)(I2C1_BASE_ADDR + 0x00);
    uint32_t* RCC_APB1ENR = (uint32_t*)(RCC_BASE_ADDR + 0x40);

	*RCC_APB1ENR |= 1 << 21; // Enable I2C1 clock
	/*Set clock is 200kHz*/
	*I2C1_CR2 = 16;
	*I2C1_CCR = 80;
	*I2C1_CR1 |= 1 << 0; // enable I2C
}

void I2C1_Write_Data(uint8_t addr, uint8_t reg, uint8_t data){
    uint32_t* I2C1_CR1 = (uint32_t*)(I2C1_BASE_ADDR + 0x00);
	uint32_t* I2C1_SR1 = (uint32_t*)(I2C1_BASE_ADDR + 0x14);
	uint32_t* I2C1_DR = (uint32_t*)(I2C1_BASE_ADDR + 0x10);
	uint32_t* I2C1_SR2 = (uint32_t*)(I2C1_BASE_ADDR + 0x18);
    volatile uint32_t tmp;

    /*send a start bit*/
    *I2C1_CR1 |= 1 << 8;
    while(((*I2C1_SR1 >> 0) & 1) == 0);
    /*send sensor address and write bit*/
    *I2C1_DR = (addr << 1) | 0;
    while(((*I2C1_SR1 >> 1) & 1) == 0);
    /* Clear addr bit*/
    tmp = *I2C1_SR1;
    tmp = *I2C1_SR2;
    /*check ACK*/
    while(((*I2C1_SR1 >> 10) & 1) == 1);
    /*send register address*/
    *I2C1_DR = reg;
    while(((*I2C1_SR1 >> 7) & 1) == 0);
    /* check ACK */
    while(((*I2C1_SR1 >> 10) & 1) == 1);
    /*send data into register address*/
    *I2C1_DR = data;
    while(((*I2C1_SR1 >> 7) & 1) == 0);
    /* check ACK */
    while(((*I2C1_SR1 >> 10) & 1) == 1);
    /*send a stop bit*/
    *I2C1_CR1 |= 1 << 9;
}

void I2C1_Read_Data(uint8_t addr,uint8_t reg , uint8_t* val){
	uint32_t* I2C1_CR1 = (uint32_t*)(I2C1_BASE_ADDR + 0x00);
	uint32_t* I2C1_SR1 = (uint32_t*)(I2C1_BASE_ADDR + 0x14);
	uint32_t* I2C1_DR = (uint32_t*)(I2C1_BASE_ADDR + 0x10);
	uint32_t* I2C1_SR2 = (uint32_t*)(I2C1_BASE_ADDR + 0x18);
	volatile uint32_t tmp;

	/*send a start bit*/
	*I2C1_CR1 |= 1 << 8;
	while(((*I2C1_SR1 >> 0) & 1) == 0);
    *I2C1_DR =  (addr << 1) | 0;
    while (((*I2C1_SR1 >> 1) & 1) == 0);
    /*clear address bit*/
    tmp = *I2C1_SR1;
    tmp = *I2C1_SR2;
    /* check ACK */
    while (((*I2C1_SR1 >> 10) & 1) == 1);
    /*send register address*/
    *I2C1_DR = reg;
    while(((*I2C1_SR1 >> 7) & 1) == 0);
    /* check ACK */
    while (((*I2C1_SR1 >> 10) & 1) == 1);
    /* re-send start bit */
    *I2C1_CR1 |= 1 << 8;
    while(((*I2C1_SR1 >> 0) & 1) == 0);
	/*send sensor address and read bit*/
	*I2C1_DR =  (addr << 1) | 1;
	while (((*I2C1_SR1 >> 1) & 1) == 0);
	/*clear address bit*/
	tmp = *I2C1_SR1;
	tmp = *I2C1_SR2;
	/*check ACK*/
	while (((*I2C1_SR1 >> 10) & 1) == 1);
	/*send a stop bit*/
	*I2C1_CR1 |= 1 << 9;
	/*read data output from sensor*/
	while(((*I2C1_SR1 >> 6) & 1) == 0);
	*val = *I2C1_DR;
}

