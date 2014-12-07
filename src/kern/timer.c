#include <gpio/timer.h>


unsigned int	*timer = (unsigned int *)TIMER_BASE_ADDRESS;


unsigned long
timer_get_timestamp(void)
{
	unsigned long	tstmp;

	tstmp = timer[TIMER_CHI];
	tstmp <<= 31;
	tstmp +=  timer[TIMER_CLO];

	return tstmp;
}


void
timer_wait(unsigned int delay)
{
	unsigned long	tstmp = 0;
	unsigned long	stop = 0;

	stop = timer_get_timestamp() + delay;

	while (tstmp < stop) {
		tstmp = timer_get_timestamp();
	}

	return;
}
