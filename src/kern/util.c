#include <stdint.h>
#include <kern/util.h>


inline void
__delay(int32_t count)
{
	asm volatile("__delay_%=: subs %[count], %[count], #1; bne __delay_%=\n"
	    : : [count]"r"(count) : "cc");
}


uint32_t
strlen(const char *s)
{
	uint32_t	ret = 0;

	while (s[ret++] != 0) ;
	return ret;
}
