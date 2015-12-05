#ifndef __KERN_UART_H
#define __KERN_UART_H


void		uart_initialise(void);
void		uart_putch(unsigned char);
unsigned char	uart_getch(void);
void		uart_puts(const char *);
void		write_uart(const unsigned char *, uint32_t);


#define UART0_BASE_ADDR	0x20201000UL

/* Pin definitions cribbed from OSDev wiki. */
#define UART0_DR	(UART0_BASE_ADDR + 0x00)
#define UART0_RSRECR	(UART0_BASE_ADDR + 0x04)
#define UART0_FR	(UART0_BASE_ADDR + 0x18)
#define UART0_ILPR	(UART0_BASE_ADDR + 0x20)
#define UART0_IBRD	(UART0_BASE_ADDR + 0x24)
#define UART0_FBRD	(UART0_BASE_ADDR + 0x28)
#define UART0_LCRH	(UART0_BASE_ADDR + 0x2C)
#define UART0_CR	(UART0_BASE_ADDR + 0x30)
#define UART0_IFLS	(UART0_BASE_ADDR + 0x34)
#define UART0_IMSC	(UART0_BASE_ADDR + 0x38)
#define UART0_RIS	(UART0_BASE_ADDR + 0x3C)
#define UART0_MIS	(UART0_BASE_ADDR + 0x40)
#define UART0_ICR	(UART0_BASE_ADDR + 0x44)
#define UART0_DMACR	(UART0_BASE_ADDR + 0x48)
#define UART0_ITCR	(UART0_BASE_ADDR + 0x80)
#define UART0_ITIP	(UART0_BASE_ADDR + 0x84)
#define UART0_ITOP	(UART0_BASE_ADDR + 0x88)
#define UART0_TDR	(UART0_BASE_ADDR + 0x8C)


#endif
