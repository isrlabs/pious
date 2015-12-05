#ifndef __PIOUS_IO_H
#define __PIOUS_IO_H


#include <stdint.h>


void		print(const char *);
void		println(const char *);
void		putch(unsigned char);
unsigned char	getch(void);
uint32_t	getline(unsigned char *, uint32_t);


#endif
