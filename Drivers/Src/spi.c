#include "spi.h"

#define SPI1_BASE_ADDR            0x40013000
#define GPIOA_BASE_ADDR           0x40020000
#define GPIOE_BASE_ADDR           0x40021000
#define RCC_BASE_ADDR       	  0x40023800

void SPI1_Init(){
	uint32_t* GPIOA_MODER = (uint32_t*)(GPIOA_BASE_ADDR + 0x00);
	uint32_t* GPIOA_AFRL = (uint32_t*)(GPIOA_BASE_ADDR + 0x20);
	uint32_t* GPIOE_MODER = (uint32_t*)(GPIOE_BASE_ADDR + 0x00);
    uint32_t* SPI_CR1 = (uint32_t*)SPI1_BASE_ADDR;
    uint32_t* RCC_APB2ENR = (uint32_t*)(RCC_BASE_ADDR +  0x44);
    uint32_t* RCC_AHB1ENR = (uint32_t*)(RCC_BASE_ADDR +   0x30);
	
    *RCC_AHB1ENR |= 1 << 0; // Enable IO port A clock
	*GPIOA_MODER &= ~(0b111111 << 10);
	*GPIOA_MODER |= 0b101010 << 10;
	*GPIOA_AFRL |= 0b101 << 20; // Set PA5 is SPI1_SCK
	*GPIOA_AFRL |= 0b101 << 24; // Set PA6 is SPI1_MISO
	*GPIOA_AFRL |= 0b101 << 28; // Set PA7 is SPI1_MOSI
	/*Set PE3 is SS*/
	*RCC_AHB1ENR |= 1 << 4;  // Enable IO port E clock
	*GPIOE_MODER &= ~(0b11 << 6);
	*GPIOE_MODER |= (0b01 << 6);

	*RCC_APB2ENR |= 1 << 12;
	*SPI_CR1 |= 1 << 2; // Master selection
	/*Baud rate control*/
	*SPI_CR1 &= ~(0b111 << 3);
	*SPI_CR1 |= 0b011 << 3;

	*SPI_CR1 |= 1 << 9; // Enable software slave management
	*SPI_CR1 |= 1 << 8; // Select internal slave 
	*SPI_CR1 |= 1 << 6; // Enable SPI 
}

void SPI1_Read_Data(uint16_t reg, uint8_t* val){
	uint16_t* SPI1_DR = (uint16_t*)(SPI1_BASE_ADDR + 0x0C);
	uint16_t* SPI1_SR = (uint16_t*)(SPI1_BASE_ADDR + 0x08);
	uint32_t* GPIOE_ODR = (uint32_t*)(GPIOE_BASE_ADDR + 0x14);
	volatile uint16_t tmp;

	*GPIOE_ODR &= ~(1 << 3);//select slave

	while(((*SPI1_SR >> 1) & 1) == 0);//wait until the TX buffer is empty
	*SPI1_DR = reg | (1 << 7); //write data into DR reg
	while(((*SPI1_SR >> 7) & 1) == 1); // wait until the data has been transmitted

	while(((*SPI1_SR >> 0) & 1) == 0); // wait until the Rx buffer is not empty
	tmp = *SPI1_DR;//read dummy data to clear the RX buffer

	while(((*SPI1_SR >> 1) & 1) == 0); // wait until the TX buffer is empty
	*SPI1_DR = 0x00;// write dummy data into DR register
	while(((*SPI1_SR >> 7) & 1) == 1); // wait until the data has been transmitted

	while(((*SPI1_SR >> 0) & 1) == 0);// wait until the Rx buffer is not empty
	*val = *SPI1_DR;// read data that is sent by slave

	*GPIOE_ODR |= 1 << 3; // un-active slave
}

void SPI1_Write_Data(uint16_t reg, uint16_t data){
	uint16_t* SPI1_DR = (uint16_t*)(SPI1_BASE_ADDR + 0x0C);
	uint16_t* SPI1_SR = (uint16_t*)(SPI1_BASE_ADDR + 0x08);
	uint32_t* GPIOE_ODR = (uint32_t*)(GPIOE_BASE_ADDR + 0x14);
	volatile uint16_t tmp;

	*GPIOE_ODR &= ~(1 << 3);//select slave

	while(((*SPI1_SR >> 1) & 1) == 0);//wait until the TX buffer is empty
	*SPI1_DR = reg; //write data into DR reg
	while(((*SPI1_SR >> 7) & 1) == 1); // wait until the data has been transmitted

	while(((*SPI1_SR >> 0) & 1) == 0); // wait until the Rx buffer is not empty
	tmp = *SPI1_DR;//read dummy data to clear the RX buffer

	while(((*SPI1_SR >> 1) & 1) == 0); // wait until the TX buffer is empty
	*SPI1_DR = data;// write data into DR register
	while(((*SPI1_SR >> 7) & 1) == 1); // wait until the data has been transmitted

	while(((*SPI1_SR >> 0) & 1) == 0);// wait until the Rx buffer is not empty
	tmp = *SPI1_DR;// read dummy data to clear the RX buffer

	*GPIOE_ODR |= 1 << 3; // un-active slave
}

