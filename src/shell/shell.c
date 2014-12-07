#include <gpio/gpio.h>
#include <gpio/timer.h>


static void
blink(unsigned int act)
{
#if (MODEL == 2)
		GPIO_set(act);
#elif (MODEL == 1)
		GPIO_clear(act);
#endif
		timer_wait(100000);

#if (MODEL == 2)
		GPIO_clear(act);
#elif (MODEL == 1)
		GPIO_set(act);
#endif
		timer_wait(300000);

}

int
main(void)
{
	/*
	 * Is anybody out there?
	 */

#if (MODEL == 2)
	const unsigned int	act = 47;
#elif (MODEL == 1)
	const unsigned int	act = 16;
#endif

	GPIO_set_function(act, GPIO_FOUT);

	while (1) {
		blink(act);
	}
}

