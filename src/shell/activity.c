#include <kern/gpio/gpio.h>
#include <kern/mmio/mmio.h>
#include <kern/util.h>


#include <shell/activity.h>


#if (MODEL == 2)
const unsigned int	act = 47;
#elif (MODEL == 1)
const unsigned int	act = 16;
#endif


void
act_led_initialise()
{
	GPIO_set_function(act, GPIO_FOUT);
}


void
act_led_on()
{
#if (MODEL == 2)
	GPIO_set(act);
#else
	GPIO_clear(act);
#endif
}


void
act_led_off()
{
#if (MODEL == 2)
	GPIO_clear(act);
#else
	GPIO_set(act);
#endif
}
