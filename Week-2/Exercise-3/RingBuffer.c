#include <stdint.h>
#include <stdio.h>

#define RING_BUF_SIZE (4U)
#define RING_BUF_MASK ((RING_BUF_SIZE) - 1U)

#define True (1U)
#define False (0U)
typedef struct {
  uint8_t buf[RING_BUF_SIZE];
  volatile uint32_t head;
  volatile uint32_t tail;
} RingBuffer_t;

static inline uint8_t is_rb_empty(RingBuffer_t *rb) {
  if (rb->head == rb->tail) {
    return True; // list is empty
  }
  return False;
}
static inline uint8_t is_rb_full(RingBuffer_t *rb) {
  uint32_t next = (rb->head + 1U) & RING_BUF_MASK;
  if (next == rb->tail) {
    return True;
  }
  return False;
}
static inline uint32_t rb_push(RingBuffer_t *rb, uint8_t element) {
  if (is_rb_full(rb)) {
    return False;
  }
  int32_t next = (rb->head + 1U) & RING_BUF_MASK;
  rb->buf[rb->head] = element;
  rb->head = next;
  return True;
}
static inline uint32_t rb_pop(RingBuffer_t *rb, uint8_t *element) {
  if (is_rb_empty(rb)) {
    return False;
  }
  *element = rb->buf[rb->tail];
  rb->tail = (rb->tail + 1U) & RING_BUF_MASK;
  return True;
}
static inline uint32_t rb_count(const RingBuffer_t *rb) {
  return ((rb->head - rb->tail) & RING_BUF_MASK);
}

int main() {
  RingBuffer_t rb;
  printf("%d\n%d\n", rb.head + 1, rb.tail);
  rb_push(&rb, 'A');
  rb_push(&rb, 'B');
  uint8_t ch;
  rb_pop(&rb, &ch);
  printf("%d\n", ch);
  rb_pop(&rb, &ch);
  printf("%d\n", ch);
  return 0;
}
