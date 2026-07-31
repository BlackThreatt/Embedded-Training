#include "RingBuffer.h"

uint8_t is_rb_empty(RingBuffer_t *rb) {
  if (rb->head == rb->tail) {
    return True; // list is empty
  }
  return False;
}
uint8_t is_rb_full(RingBuffer_t *rb) {
  uint32_t next = (rb->head + 1U) & RING_BUF_MASK;
  if (next == rb->tail) {
    return True;
  }
  return False;
}
uint8_t rb_push(RingBuffer_t *rb, uint8_t element) {
  if (is_rb_full(rb)) {
    return False;
  }
  int32_t next = (rb->head + 1U) & RING_BUF_MASK;
  rb->buf[rb->head] = element;
  rb->head = next;
  return True;
}
uint8_t rb_pop(RingBuffer_t *rb, uint8_t *element) {
  if (is_rb_empty(rb)) {
    return False;
  }
  *element = rb->buf[rb->tail];
  rb->tail = (rb->tail + 1U) & RING_BUF_MASK;
  return True;
}
uint8_t rb_count(const RingBuffer_t *rb) {
  return ((rb->head - rb->tail) & RING_BUF_MASK);
}
