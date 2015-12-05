#ifndef __KERN_UTIL_H
#define __KERN_UTIL_H


#include <stdint.h>


#define		_BIT(x)	(1 << (x))


inline void	__delay(int32_t);
uint32_t	__strlen(const char *);


#endif
