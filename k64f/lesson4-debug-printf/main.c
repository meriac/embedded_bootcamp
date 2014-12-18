#include <MK64F12.h>
#include "tfp_printf.h"

#define CHANNEL_DEBUG 0

/* declared in minimal.ld */
extern const uint32_t StackTop;

/* print single character over SWO debug interface */
void PrintChr(char data)
{
	/* wait for TX */
	while (ITM->PORT[CHANNEL_DEBUG].u32 == 0);
	/* TX debug character */
	ITM->PORT[CHANNEL_DEBUG].u8 = (uint8_t)data;
}

/* reset function */
void OnReset(void)
{
	uint32_t n;

	/* reset previous channel settings */
	ITM->LAR  = 0xC5ACCE55;
	ITM->TCR  = ITM->TER = 0x0;

	/* wait for debugger to connect */
	while(!((ITM->TCR & ITM_TCR_ITMENA_Msk) && (ITM->TER & (1<<CHANNEL_DEBUG))));

	/* print endless hello world */
	n = 0;
	while(1)
		tfp_printf("%08X: Hello %s!\n\r", n++, "World");
}

/* declare vector table */
__attribute__ ((section(".vtor")))
const void* VectorTable[] = {
	&StackTop,
	OnReset
};
