#include <MK64F12.h>

/* declared in minimal.ld */
extern const uint32_t StackTop;

/* reset function */
void OnReset(void)
{
	volatile uint32_t i;

	/* enable clock for PORTB */
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	/* set PORTB pin 21/22 to ALT1 function (GPIO) */
	PORTB->PCR[21] = PORT_PCR_MUX(1)|PORT_PCR_DSE_MASK;
	PORTB->PCR[22] = PORT_PCR_MUX(1)|PORT_PCR_DSE_MASK;
	/* enable output for PORTB pin 21/22 */
	PTB->PDDR |= (1UL << 21) | (1UL << 22);
	/* set PORTB pin 21 */
	PTB->PSOR = 1UL << 21;
	/* clear PORTB pin 22 */
	PTB->PCOR = 1UL << 22;

	/* blink red & blue LED alternating */
	while(1)
	{
		/* toggle PORTB pin 21 & 22 ... */
		PTB->PTOR = (1UL << 21)|(1UL << 22);
		/* ... and wait */
		for(i=0; i<1000000; i++);
	}
}

/* declare vector table */
__attribute__ ((section(".vtor")))
const void* VectorTable[] = {
	&StackTop,
	OnReset
};
