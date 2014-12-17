#include <MK64F12.h>

#define IRQn_OFFSET				16
#define MAX_ISR_VECTORS			(IRQn_OFFSET+85)
#define ISR_SET(irqn, handler)	g_isr_vector[IRQn_OFFSET + irqn] = handler;

/* declared in minimal.ld */
extern const uint32_t StackTop;

/* actual vector table in RAM */
typedef void (*TIsrVector)(void);
__attribute__ ((aligned(128)))
volatile TIsrVector g_isr_vector[MAX_ISR_VECTORS];

static void TimerInterrupt(void)
{
	/* toggle PORTB 22 ... */
	PTB->PTOR = (1UL << 22);

	/* acknowledge IRQ and wait for TCF to vanish */
	LPTMR0->CSR |= LPTMR_CSR_TCF_MASK;
	while(LPTMR0->CSR & LPTMR_CSR_TCF_MASK);
}

static void InitHardware(void)
{
	/* enable clock for PORTB & LPTMR */
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_LPTMR_MASK;

	/* set PORTB pin 22 to ALT1 function (GPIO) */
	PORTB->PCR[22] = PORT_PCR_MUX(1)|PORT_PCR_DSE_MASK;
	/* enable output for PORTB pin 22 */
	PTB->PDDR |= (1UL << 22);
	/* clear PORTB pin 22 */
	PTB->PCOR = 1UL << 22;

	/* reset pending interrupts & enable timer IRQ, disable timer */
	LPTMR0->CSR = LPTMR_CSR_TCF_MASK | LPTMR_CSR_TIE_MASK;
	LPTMR0->PSR = LPTMR_PSR_PBYP_MASK | LPTMR_PSR_PCS(1);
	/* trigger interrupt every 500ms */
	LPTMR0->CMR = 500;
	/* update interrupt vector & enable NVIC entry */
	ISR_SET(LPTimer_IRQn, TimerInterrupt);
	NVIC_EnableIRQ(LPTimer_IRQn);
	/* run timer */
	LPTMR0->CSR|= LPTMR_CSR_TEN_MASK;

	/* sleep forever */
	while(1)
		__WFI();
}

static void DefaultHandler(void)
{
	while(1);
}

/* reset function */
void OnReset(void)
{
	int i;

	/* setup new vector table in SRAM */
	for(i=0; i<MAX_ISR_VECTORS; i++)
		g_isr_vector[i] = DefaultHandler;
	/* update vector table pointer to new table */
	SCB->VTOR = (uint32_t)&g_isr_vector;

	InitHardware();
}

/* declare vector table */
__attribute__ ((section(".vtor")))
const void* VectorTable[] = {
	&StackTop,
	OnReset
};
