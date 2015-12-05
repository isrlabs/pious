#include <kern/gpio/gpio.h>



volatile unsigned int	*gpio = (unsigned int *)GPIO_BASE_ADDR;


/*!
 * \brief Set the function for a GPIO pin (R/W/ALT[0-5]).
 * \param pin The pin number, in the range 0-53.
 * \param f The function to set the pin to.
 */
void
GPIO_set_function(unsigned int pin, unsigned char f)
{
	unsigned char	shift = 0;
	unsigned int	val = 0;

	if (pin > 53)
		return;
	if (f > 7)
		return;

	while (pin > 9) {
		pin -= 10;
		shift++;
	};

	pin += (pin << 1);
	val = f << pin;
	gpio[shift] |= val;
	return;
}


/*!
 * \brief Set the pin to on.
 */
void
GPIO_set(unsigned char pin)
{
	unsigned int	bank = GPIO_GPSET0;

	if (pin > 53) {
		return;
	} else if (pin > 31) {
		bank = GPIO_GPSET1;
		pin -= 32;
	}

	gpio[bank] |= (1 << pin);
}


/*!
 * \brief Set the pin to on.
 */
void
GPIO_clear(unsigned char pin)
{
	unsigned int	bank = GPIO_GPCLR0;

	if (pin > 53) {
		return;
	} else if (pin > 31) {
		bank = GPIO_GPCLR1;
		pin -= 32;
	}

	gpio[bank] |= (1 << pin);
}
