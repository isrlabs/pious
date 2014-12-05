#include <gpio.h>



volatile unsigned int	*gpio = (unsigned int *)GPIO_BASE_ADDR;


void
GPIO_set_function(unsigned char pin, unsigned char f)
{


	if (pin > 53)
		return;
	if (f > 7)
		return;

	return;
}
