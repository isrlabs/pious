#include <stdint.h>

#include <kern/uart/uart.h>
#include <io.h>

void
print(const char *s)
{
	uart_puts(s);
}


void
println(const char *s)
{
	uart_puts(s);
	uart_putch(0x0d);
	uart_putch(0x0a);
}


void
putch(unsigned char c)
{
	uart_putch(c);
}


unsigned char
getch()
{
	return uart_getch();
}


static unsigned char
hexchar(c)
{
	switch (c) {
	case 1:
		return '1';
	case 2:
		return '2';
	case 3:
		return '3';
	case 4:
		return '4';
	case 5:
		return '5';
	case 6:
		return '6';
	case 7:
		return '7';
	case 8:
		return '8';
	case 9:
		return '9';
	case 10:
		return 'A';
	case 11:
		return 'B';
	case 12:
		return 'C';
	case 13:
		return 'D';
	case 14:
		return 'E';
	case 15:
		return 'F';
	case 0:
		return '0';
	}
}


static void
show_char(unsigned char c)
{
	unsigned char	h;
	unsigned char	l;

	h = hexchar(c >> 4);
	l = hexchar(c & 0xF);
	putch(h);
	putch(l);

}


uint32_t
getline(unsigned char *buf, uint32_t buflen)
{
	uint32_t	pos = 0;
	uint8_t		stop = 0; /* 1: CR */


	println("getline");
	while (pos < buflen) {
		buf[pos] = uart_getch();
		print("character received: ");
		show_char(buf[pos]);
		println(".");
		if (0x0d == buf[pos]) {
			stop = 1;
		} else if (0x0a == buf[pos] && stop) {
			break;
		}

		println("putch");
		putch(buf[pos]);
		pos++;
	}

	println("end getline");
	return pos;
}
