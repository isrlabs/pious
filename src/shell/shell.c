#include <stdint.h>

#include <gpio/gpio.h>

int
main(uint32_t r0, uint32_t r1, uint32_t atags)
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

#if (MODEL == 2)
	GPIO_set(act);
#elif (MODEL == 1)
	GPIO_clear(act);
#endif

	/*
	 * force check this madness
	 */
	unsigned int	*gpio = (unsigned int *)0x20200000;
#if (MODEL == 2)
	gpio[8] |= 1<<21;	/* pin #47 is GPFSEL4, group 7*3 = 21-24 */
	gpio[7] |= 1<<15;	/* pin #47 is GPSET1; 47-31 = 16 */
#elif (MODEL == 1)
	gpio[1] |= 1<<18;	/* pin #47 is GPFSEL1, group 6*3 = 18-21 */
	gpio[10] |= 1<<16;	/* pin #47 is GPCLR0 */
#endif

	uart_puts("BOOT OK\r\n");
	while (1) ;
}

