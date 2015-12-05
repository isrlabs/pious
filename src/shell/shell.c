#include <stdint.h>

#include <kern/uart/uart.h>
#include <shell/activity.h>

int
main(uint32_t r0, uint32_t r1, uint32_t atags)
{
	uart_initialise();
	uart_puts("BOOT OK\r\n");
	act_led_on();
	while (1) ;
}

