#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdbool.h>
#include <stdint.h>

#define RING_BUF_SIZE (256U) /* must be power of 2 */
#define RING_BUF_MASK (RING_BUF_SIZE - 1U)

_Static_assert((RING_BUF_SIZE & RING_BUF_MASK) == 0u,
               "RING_BUF_SIZE must be a power of two");

typedef struct {
  volatile uint8_t buf[RING_BUF_SIZE];
  volatile uint32_t head;
  volatile uint32_t tail;
} RingBuffer_t;

void RingBuf_Init(RingBuffer_t *rb);
bool RingBuf_Push(RingBuffer_t *rb, uint8_t element);
bool RingBuf_Pop(RingBuffer_t *rb, uint8_t *element);
uint32_t RingBuf_Count(const RingBuffer_t *rb);
bool RingBuf_IsEmpty(const RingBuffer_t *rb);
bool RingBuf_IsFull(const RingBuffer_t *rb);

#endif /* RING_BUFFER_H */
