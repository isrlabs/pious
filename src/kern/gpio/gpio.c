#include <gpio.h>


void
GPIO_set_function(unsigned char pin, unsigned char f)
{
	volatile unsigned int	*gpio = (unsigned int *)GPIO_BASE_ADDR;

	if (pin > 53)
		return;
	if (f > 7)
		return;

}
