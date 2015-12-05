#include <stdint.h>

#include <kern/util.h>
#include <kern/gpio/gpio.h>
#include <kern/mmio/mmio.h>
#include <kern/uart/uart.h>


#define UART_CLOCK	(3000000)
#define UART_BAUD	(115200)

const unsigned int	UART_TXD = 14;
const unsigned int	UART_RXD = 15;


static inline void
uart_clear_interrupts(void)
{
	write_mmio(UART0_ICR, 0x7FF);
}


void
uart_initialise()
{
	/*
	 * The UART uses GPIO 14 as TXD0 when in ALT0 mode, and GPIO 15 as RXD0
	 * when in ALT0 mode. Pull needs to be low.
	 */
	GPIO_set_function(UART_TXD, GPIO_ALT0);
	GPIO_set_function(UART_RXD, GPIO_ALT1);

	/*
	 * From the data sheet, p185:
	 *
	 * Program the control registers as follows:
	 * 1. Disable the UART.
	 * 2. Wait for the end of transmission or reception of the current
	 * character.
	 * 3. Flush the transmit FIFO by setting the FEN bit to 0 in the Line
	 * Control Register, UART_LCRH.
	 * 4. Reprogram the Control Register, UART_CR.
	 * 5. Enable the UART
	 */

	/* Disable the UART. */
	write_mmio(UART0_CR, 0x00000000);
	write_mmio(GPIO_GPPUD, 0x00000000);
	__delay(150); /* Wait for any transmissions to finish. */

	/* Set the pull for TXD0 and RXD0 to low. */
	write_mmio(GPIO_GPPUDCLK0, _BIT(14) | _BIT(15));
	__delay(150);
	write_mmio(GPIO_GPPUDCLK0, 0x00000000);

	uart_clear_interrupts();

	/* Baud rate: 115200 */
	write_mmio(UART0_IBRD, 1);
	write_mmio(UART0_FBRD, 40);

	/* Enable the FIFO and data transmit (8N1). */
	write_mmio(UART0_LCRH,  _BIT(4) | _BIT(5) | _BIT(6));

	/* Mask interrupts. */
	write_mmio(UART0_IMSC, _BIT(1) | _BIT(4) | _BIT(5) | _BIT(6) |
	    _BIT(7) | _BIT(8) | _BIT(9) | _BIT(10));

	/* Enable UART0: turn on UARTEN, TXE, and RXE. */
	write_mmio(UART0_CR, _BIT(0) | _BIT(8) | _BIT(9));
}


int
uart_ready()
{

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

	dlen = __strlen(data);
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
