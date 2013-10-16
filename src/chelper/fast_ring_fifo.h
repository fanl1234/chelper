
#ifndef FAST_RING_FIFO_H_
#define FAST_RING_FIFO_H_

#include <chelper/helper_types.h>

typedef struct s_fast_ring_fifo_private {
	uint32_t mask;
	uint32_t wrIdx;
	uint32_t rdIdx;
} fast_ring_fifo_t;

/*
 * num_of_slots must be base of two, i.e. 2, 4, 8, 16, 32, 64, ...
 */
inline void fast_ring_fifo_init(fast_ring_fifo_t * obj, uint32_t num_of_slots)
{
	uint32_t pre_mask = 0x80000000;
	while (pre_mask)
	{
		if (num_of_slots & pre_mask) {
			break;
		}

		pre_mask >>= 1;
	}

	if (!pre_mask) {
		obj->mask = 0;
		return;
	}

	obj->mask = pre_mask - 1;
	obj->rdIdx = 0;
	obj->wrIdx = 0;
}

inline uint32_t fast_ring_fifo_num_of_slots(fast_ring_fifo_t * obj)
{
	return obj->mask + 1;
}

inline uint32_t fast_ring_fifo_write_index(fast_ring_fifo_t * obj)
{
	return obj->mask & obj->wrIdx;
}

inline uint32_t fast_ring_fifo_read_index(fast_ring_fifo_t * obj)
{
	return obj->mask & obj->rdIdx;
}

inline void fast_ring_fifo_write_increment(fast_ring_fifo_t * obj)
{
	obj->wrIdx++;
}

inline void fast_ring_fifo_read_increment(fast_ring_fifo_t * obj)
{
	obj->rdIdx++;
}

inline void fast_ring_fifo_read_reset(fast_ring_fifo_t * obj)
{
	obj->rdIdx = 0;
	obj->wrIdx = 0;
}

inline BOOL fast_ring_fifo_empty(fast_ring_fifo_t * obj)
{
	return obj->rdIdx == obj->wrIdx;
}

inline BOOL fast_ring_fifo_full(fast_ring_fifo_t * obj)
{
	return (obj->mask & obj->rdIdx) == (obj->mask & (obj->wrIdx+1));
}

inline uint32_t fast_ring_fifo_count(fast_ring_fifo_t * obj)
{
	return obj->mask & (obj->wrIdx - obj->rdIdx);
}

#endif /* FAST_RING_FIFO_H_ */
