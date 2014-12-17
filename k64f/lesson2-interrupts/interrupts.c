#include <MK64F12.h>

#define IRQn_OFFSET				16
#define MAX_ISR_VECTORS			(IRQn_OFFSET+85)
#define ISR_SET(irqn, handler)	g_isr_vector[IRQn_OFFSET + irqn] = handler;

/* declared in minimal.ld */
extern const uint32_t StackTop;

/* actual vector table in RAM */
typedef void (*TIsrVector)(void);
__attribute__ ((aligned(128)))
TIsrVector g_isr_vector[MAX_ISR_VECTORS];

void DefaultHandler(void)
{
	while(1);
}

void MainLoop(void)
{
	volatile int i;

	/* enable clock for PORTB */
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	/* set PORTB pin 22 to ALT1 function (GPIO) */
	PORTB->PCR[22] = PORT_PCR_MUX(1)|PORT_PCR_DSE_MASK;
	/* enable output for PORTB pin 22 */
	PTB->PDDR |= (1UL << 22);

	/* blink red & blue LED alternating */
	while(1)
	{
		/* toggle PORTB 22 ... */
		PTB->PTOR = (1UL << 22);
		/* ... and wait */
		for(i=0; i<1000000; i++);
	}
}

/* reset function */
void OnReset(void)
{
	int i;

	for(i=0; i<MAX_ISR_VECTORS; i++)
		g_isr_vector[i] = DefaultHandler;

	MainLoop();
}

/* declare vector table */
__attribute__ ((section(".vtor")))
const void* VectorTable[] = {
	&StackTop,
	OnReset
};
