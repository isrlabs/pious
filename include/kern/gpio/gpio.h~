#ifndef __KERN_GPIO_H
#define __KERN_GPIO_H


#define GPIO_BASE_ADDR	0x20200000UL

/* Set pull up/down on all GPIO pins. */
#define GPIO_GPPUD	(GPIO_BASE_ADDR + 0x94)

/* Set pull up/down on specific pins. */
#define GPIO_GPPUDCLK0	(GPIO_BASE_ADDR + 0x98)

/*
 * GPIO function selects: each pin has three bits associated with it
 * that select the function to be used:
 *	000	Input
 *	001	Output
 *	100	ALT0
 *	101	ALT1
 *	110	ALT2
 *	111	ALT3
 *	011	ALT4
 *	010	ALT5
 * Each register handles 10 pins; the top two bits are reserved.
 * Therefore, GPFSEL0 handles pins 0-9, GPFSELF1 handles pins 10-19,
 * etc...
 */
#define GPIO_GPFSEL0	0
#define GPIO_GPFSEL1	1
#define GPIO_GPFSEL2	2
#define GPIO_GPFSEL3	3
#define GPIO_GPFSEL4	4
#define GPIO_GPFSEL5	5

/*
 * A bit written here turns a pin on. SET0 handles pins 0-31, SET1
 * pins 32-53.
 */
#define GPIO_GPSET0	7
#define GPIO_GPSET1	8

/*
 * A bit written here turns a pin off. CLR0 handles pins 0-31, CLR1
 * pins 32-53.
 */
#define GPIO_GPCLR0	10
#define GPIO_GPCLR1	11


#define GPIO_FIN	0
#define GPIO_FOUT	1
#define GPIO_ALT0	4
#define GPIO_ALT1	5
#define GPIO_ALT2	6
#define GPIO_ALT3	7
#define GPIO_ALT4	3
#define GPIO_ALT5	2


void	GPIO_set_function(unsigned int, unsigned char);
void	GPIO_set(unsigned char);
void	GPIO_clear(unsigned char);


#endif
