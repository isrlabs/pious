#ifndef __KERN_TIMER_H
#define __KERN_TIMER_H


#define TIMER_BASE_ADDRESS	0x20003000

#define TIMER_CLO		1
#define TIMER_CHI		2


unsigned long	timer_get_timestamp(void);
void		timer_wait(unsigned int);


#endif
