#include <gpio.h>

int
main(void)
{
	/*
	 * Is anybody out there?
	 */
	const unsigned int	act = 47;

	GPIO_set_function(act, GPIO_FOUT);
	GPIO_set(act);

	while (1) ;
}

