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
act_led_init()
{
	GPIO_set_function(act, GPIO_FOUT);

#if (MODEL == 2)
	write_mmio(GPIO_BASE_ADDR+GPIO_GPFSEL4, _BIT(21));
#else
	write_mmio(GPIO_BASE_ADDR+GPIO_GPFSEL1, _BIT(18));
#endif
}


void
act_led_on()
{
#if (MODEL == 2)
	write_mmio(GPIO_BASE_ADDR+GPIO_GPSET1, _BIT(15));
#else
	write_mmio(GPIO_BASE_ADDR+GPIO_GPCLR0, _BIT(16));
#endif
}


void
act_led_off()
{
#if (MODEL == 2)
	write_mmio(GPIO_BASE_ADDR+GPIO_GPCLR1, _BIT(15));
#else
	write_mmio(GPIO_BASE_ADDR+GPIO_GPSET0, _BIT(16));
#endif
}
