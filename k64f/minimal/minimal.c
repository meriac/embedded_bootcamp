#include <MK64F12.h>

/* declared in minimal.ld */
extern const uint32_t StackTop;

/* reset function */
void OnReset(void)
{
	volatile uint32_t i;

	/* enable clock for PORTB */
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	/* set PORTB pin 21 to ALT1 function (GPIO) */
	PORTB->PCR[21] = PORT_PCR_MUX(1);

	/* blink forever */
	while(1)
	{
		/* toggle PORTB pin 21 ... */
		PTB->PTOR = 1UL << 21;
		/* ... and wait */
		for(i=0; i<10000000; i++);
	}
}

/* declare vector table */
__attribute__ ((section(".vtor")))
const void* VectorTable[] = {
	&StackTop,
	OnReset
};
