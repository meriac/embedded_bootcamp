#include <stdint.h>

/* declared in minimal.ld */
extern const uint32_t StackTop;

/* reset function */
static void OnReset(void)
{
	volatile uint32_t i;

	i = 0;
	while(1)
	{
		i++;
	}
}

/* declare vector table */
__attribute__ ((section(".vtor")))
const void* VectorTable[] = {
	&StackTop,
	OnReset
};
