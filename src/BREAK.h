#include "LPC11xx.h"                    // Device header

void BreakInit();
void PIOINT3_IRQHandler(void);
void SEGinit();
void KEYinit();
void Delayb(uint32_t ulTime);
