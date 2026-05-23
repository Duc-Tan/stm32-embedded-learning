#include"dma.h"
#define DMA2_BASE_ADDR            0x40026400
#define RCC_BASE_ADDR       	  0x40023800
#define BUFFER_SIZE 			  8

void DMA2_Init(char* buffer){
	uint32_t* DMA2_S2CR   = (uint32_t*)(DMA2_BASE_ADDR +  0x10 + 0x18 * 2);
	uint32_t* DMA2_S2PAR  = (uint32_t*)(DMA2_BASE_ADDR +  0x18 + 0x18 * 2);
	uint32_t* DMA2_S2M0AR = (uint32_t*)(DMA2_BASE_ADDR +  0x1C + 0x18 * 2);
	uint32_t* DMA2_S2NDTR = (uint32_t*)(DMA2_BASE_ADDR +  0x14 + 0x18 * 2);
    uint32_t* RCC_AHB1ENR = (uint32_t*)(RCC_BASE_ADDR + 0x30);
	
    *RCC_AHB1ENR |= 1 << 22; 			//Enable DMA2 clock 
	*DMA2_S2PAR  = 0x40011004;          //Peripherial addr
	*DMA2_S2M0AR = (uint32_t)buffer;    //Memory addr
	*DMA2_S2NDTR = BUFFER_SIZE;         //Number of data

	*DMA2_S2CR &= ~(0b111 << 25);
	*DMA2_S2CR |= 4 << 25;              //Select channel 4
	*DMA2_S2CR |= 1 << 10;				//Enable memory increment mode
	*DMA2_S2CR |= 1 << 8;				//Enable Circular mode
	*DMA2_S2CR |= 1 << 0;               //Enable DMA
    *DMA2_S2CR |= 1 << 4;               //Enable DMA interrupt
	uint32_t* ISER1 = (uint32_t*)0xE000E104;
	*ISER1 |= 1 << (58 - 32);
}

int recv_complete = 0;
void DMA2_Stream2_IRQHandler(){
	uint32_t* DMA_LIFCR = (uint32_t*)(DMA2_BASE_ADDR + 0x08);
	*DMA_LIFCR = 1 << 21;
	recv_complete = 1;
    DMA2_Receive_Callback(recv_complete);
}

__attribute__((weak)) void DMA2_Receive_Callback(int recv_byte){
    
}