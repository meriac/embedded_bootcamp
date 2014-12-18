#include <MK64F12.h>

#define CHANNEL_DEBUG 0

/* declared in minimal.ld */
extern const uint32_t StackTop;

/* print single character over SWO debug interface */
static void PrintChr(char data)
{
	/* wait for TX */
	while (ITM->PORT[CHANNEL_DEBUG].u32 == 0);
	/* TX debug character */
	ITM->PORT[CHANNEL_DEBUG].u8 = (uint8_t)data;
}

/* convert number to hex character */
static char HexChar(uint8_t data)
{
	return (data<0xA) ? (data+'0') : (data+'A'-0xA);
}

static void PrintHexByte(uint8_t num)
{
	PrintChr(HexChar(num >>  4));
	PrintChr(HexChar(num & 0xF));
}

void PrintHex(uint32_t num)
{
	PrintHexByte((uint8_t)(num >> 24));
	PrintHexByte((uint8_t)(num >> 16));
	PrintHexByte((uint8_t)(num >>  8));
	PrintHexByte((uint8_t)(num >>  0));
}

void PrintStr(const char* str)
{
	char c;
	while((c = *str++)!=0)
		PrintChr(c);
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
	{
		PrintHex(n);
		PrintStr(": Hello World!\n\r");
	}
}

/* declare vector table */
__attribute__ ((section(".vtor")))
const void* VectorTable[] = {
	&StackTop,
	OnReset
};
