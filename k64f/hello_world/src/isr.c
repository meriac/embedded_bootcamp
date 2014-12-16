#include <bootcamp.h>
#include "config.h"
#include "isr.h"

/* actual vector table in RAM */
__attribute__ ((aligned(128)))
TIsrVector g_isr_vector[MAX_ISR_VECTORS];

void default_handler(void)
{
	while(1);
}

void reset_handler(void)
{
	int i;

	for(i=0; i<ARRAY_COUNT(g_isr_vector); i++)
		g_isr_vector[i] = default_handler;

	main_entry();
}

/* initial vector table - just needed for boot process */
__attribute__ ((section(".vtor")))
const TIsrVector g_isr_vector_tmp[] = {
	(void*)STACK_POINTER,
	reset_handler
};


