#ifndef DMA_H_
#define DMA_H_

#include <stdint.h> 

void DMA2_Init(char* buffer);
void DMA2_Stream2_IRQHandler(void);
void DMA2_Receive_Callback(int recv_byte);

#endif /* DMA_H_ */