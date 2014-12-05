#ifndef __KERN_GPIO_H
#define __KERN_GPIO_H


#define GPIO_BASE_ADDR	0x20200000UL


void	GPIO_set_function(unsigned char, unsigned char);

#endif
