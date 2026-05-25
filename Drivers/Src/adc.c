#include "adc.h"

#define ADC_BASE_ADDR             0x40012000
#define RCC_BASE_ADDR       	  0x40023800

void ADC_Init(){
    uint32_t* ADC_JSQR    = (uint32_t*)(ADC_BASE_ADDR + 0x38);
    uint32_t* ADC_CCR     = (uint32_t*)(ADC_BASE_ADDR + 0x304);
    uint32_t* ADC_SMPR1   = (uint32_t*)(ADC_BASE_ADDR + 0x0C);
    uint32_t* ADC_CR2     = (uint32_t*)(ADC_BASE_ADDR + 0x08);
    uint32_t* RCC_APB2ENR = (uint32_t*)(RCC_BASE_ADDR + 0x44);

    *RCC_APB2ENR |= 1 << 8;           // Enable ADC clock
    *ADC_JSQR    &= ~(0b11 << 20);    // Select the number of conversion
    *ADC_JSQR    &= ~(0b11111 << 15); // Select channel 16
    *ADC_JSQR    |= 0b10000 << 15;
    *ADC_CCR     |= 1 << 23;          // Enable temperature sensor
    *ADC_SMPR1   &= ~(0b111 << 18);   // Set sample time
    *ADC_SMPR1   |= 0b001 << 18;
    *ADC_CR2     |= 1 << 0;           // Enable ADC
}

float ADC_Read_Data_Sensor(){
    uint32_t* ADC_CR2   = (uint32_t*)(ADC_BASE_ADDR + 0x08);
    uint32_t* ADC_SR    = (uint32_t*)(ADC_BASE_ADDR + 0x00);
    uint32_t* ADC_JDR1  = (uint32_t*)(ADC_BASE_ADDR + 0x3C);

    /* Trigger to start ADC measurement */
    *ADC_CR2 |= (1 << 22); 
    /* Read the value of the Injected Data Register */
    while(((*ADC_SR >> 2) & 0b1) == 0); 
    uint32_t data = *ADC_JDR1;
    /* Calculate the measured value */
    float vin;
    vin = ((float)data * 3)/4095;
    float temp;
    temp = ((vin - 0.76)/(2.5*0.001)) + 25;
    *ADC_SR &= ~(1 << 2);
    return temp;
}

