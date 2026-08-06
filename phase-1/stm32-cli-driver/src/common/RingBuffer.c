#include "RingBuffer.h"

void RingBuf_Init(RingBuffer_t *rb) {
  rb->head = 0;
  rb->tail = 0;
}

bool RingBuf_Push(RingBuffer_t *rb, uint8_t element) {
  uint32_t head = rb->head;
  if ((head - rb->tail) >= RING_BUF_SIZE) {
    return false; /* full */
  }
  rb->buf[head & RING_BUF_MASK] = element;
  rb->head = head + 1U;
  return true;
}

bool RingBuf_Pop(RingBuffer_t *rb, uint8_t *element) {
  uint32_t tail = rb->tail;
  if (rb->head == tail) {
    return false; /* empty */
  }
  *element = rb->buf[tail & RING_BUF_MASK];
  rb->tail = tail + 1U;
  return true;
}
uint32_t RingBuf_Count(const RingBuffer_t *rb) {
  return rb->head - rb->tail; 
}

bool RingBuf_IsEmpty(const RingBuffer_t *rb) {
  return rb->head == rb->tail; 
}

bool RingBuf_IsFull(const RingBuffer_t *rb) {
  return (rb->head - rb->tail) >= RING_BUF_SIZE;
}
