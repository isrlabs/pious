#include <stdint.h>


static inline void
write_mmio(uint32_t reg, uint32_t data)
{
	*(volatile uint32_t *)reg = data;
}


static inline uint32_t
read_mmio(uint32_t reg)
{
	return *(volatile uint32_t *)reg;
}


