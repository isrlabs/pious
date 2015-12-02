#include <stdint.h>

#include <util.h>
#include <gpio.h>
#include <uart.h>


void
uart_initialise()
{
	/* Implementation cribbed from OSDev wiki. */

	/* Disable UART0. */
	write_mmio(UART0_CR, 0x00000000);
	/* Setup the GPIO pin 14 && 15. */

	/* Disable pull up/down for all GPIO pins & delay for 150 cycles. */
	write_mmio(GPIO_GPPUD, 0x00000000);
	__delay(150);

	/* Disable pull up/down for pin 14/15 & delay for 150 cycles. */
	write_mmio(GPIO_GPPUDCLK0, _BIT(14) | _BIT(15));
	__delay(150);

	/* Write 0 to GPPUDCLK0 to make it take effect. */
	write_mmio(GPIO_GPPUDCLK0, 0x00000000);

	/* Clear pending interrupts. */
	write_mmio(UART0_ICR, 0x7FF);

	/* Set integer & fractional part of baud rate.

	   Divider = UART_CLOCK/(16 * Baud)
	   Fraction part register = (Fractional part * 64) + 0.5
	   UART_CLOCK = 3000000; Baud = 115200.

	   Divider = 3000000 / (16 * 115200) = 1.627 = ~1.
	   Fractional part register = (.627 * 64) + 0.5 = 40.6 = ~40.
	*/
	write_mmio(UART0_IBRD, 1);
	write_mmio(UART0_FBRD, 40);

	/* Enable FIFO & 8 bit data transmissio (1 stop bit, no parity). */
	write_mmio(UART0_LCRH, _BIT(4) | _BIT(5) | _BIT(6));

	/* Mask all interrupts. */
	write_mmio(UART0_IMSC, _BIT(1) | _BIT(4) | _BIT(5) | _BIT(6) |
	    _BIT(7) | _BIT(8) | _BIT(9) | _BIT(10));

	/* Enable UART0, receive & transfer part of UART. */
	write_mmio(UART0_CR, _BIT(0) | _BIT(8) | _BIT(9));
}


void
uart_putch(unsigned char data)
{
	/* Wait until UART is ready to transmit. */
	while (read_mmio(UART0_FR) & _BIT(5)) ;
	write_mmio(UART0_DR, data);
}


unsigned char
uart_getch()
{
	/* Wait until UART has data. */
	while (read_mmio(UART0_FR) & _BIT(4)) ;
	return read_mmio(UART0_DR);
}


void
uart_puts(const char *data)
{
	uint32_t	dlen = 0;

	dlen = strlen(data);
	write_uart((const unsigned char *)data, dlen);
}


void
write_uart(const unsigned char *data, uint32_t dlen)
{
	uint32_t	i;

	for (i = 0; i < dlen; i++) {
		uart_putch(data[i]);
	}
}
