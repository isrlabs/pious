#include <stdint.h>

#include <shell/activity.h>
#include <io.h>


static void
echo(void)
{
	char	c;

	getch();
	println("echo");
	while (1) {
		c = getch();
		putch(c);
	}
}

int
main(uint32_t r0, uint32_t r1, uint32_t atags)
{
	uart_initialise();
	act_led_initialise();

	println("BOOT OK");

	echo();
}

