#ifndef __RINGBUFFER_H_
#define __RINGBUFFER_H_

#include <stdint.h>

#define True (1U)
#define False (0U)

#define RING_BUF_SIZE (256U)
#define RING_BUF_MASK ((RING_BUF_SIZE) - 1U)

typedef struct {
  uint8_t buf[RING_BUF_SIZE];
  volatile uint32_t head;
  volatile uint32_t tail;
} RingBuffer_t;

uint8_t is_rb_empty(RingBuffer_t *rb);
uint8_t is_rb_full(RingBuffer_t *rb);
uint8_t rb_push(RingBuffer_t *rb, uint8_t element);
uint8_t rb_pop(RingBuffer_t *rb, uint8_t *element);
uint8_t rb_count(const RingBuffer_t *rb);

#endif // !__RINGBUFFER_H_
