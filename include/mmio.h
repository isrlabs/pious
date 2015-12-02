#ifndef __KERN_MMIO_H


#include <stdint.h>


inline void	write_mmio(uint32_t, uint32_t);
inline uint32_t	read_mmio(uint32_t);


#endif
