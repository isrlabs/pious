#include <stdint.h>

#include <kern/gpio/timer.h>
#include <syslib.h>


#define	MICROSEC_TO_SEC		100000
#define MICROSEC_TO_MILLSEC	1000


const unsigned int	MAX_SLEEP = 4294;


uint32_t
strlen(const char *s)
{
	uint32_t	ret = 0;

	while (s[ret++] != 0) ;
	return ret;
}


void
sleep(unsigned int n)
{
	timer_wait(n * MICROSEC_TO_SEC);
}


void
sleep_ms(unsigned int n)
{
	timer_wait(n * MICROSEC_TO_MILLSEC);
}
