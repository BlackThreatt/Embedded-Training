/**
 ******************************************************************************
 * @file           : RingBuffer.c
 * @brief          : Lock-free single-producer/single-consumer ring buffer
 * @author         : Mohamed Ali BESSAIDI
 * @date           : 1 Sept 2026
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 MOHAMED ALI BESSAIDI.
 * All rights reserved.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "RingBuffer.h"
#include <stddef.h>

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes
 * ------------------------------------------------*/

/* Exported functions
 * ----------------------------------------------------------*/

error_t RingBuf_Init(RingBuffer_t *rb) {
  if (rb == NULL) {
    return ERR_NULL_PTR;
  }
  rb->head = 0;
  rb->tail = 0;
  return ERR_OK;
}

error_t RingBuf_Push(RingBuffer_t *rb, uint8_t element, bool *out_ok) {
  uint32_t head;

  if (rb == NULL || out_ok == NULL) {
    return ERR_NULL_PTR;
  }

  head = rb->head;
  if ((head - rb->tail) >= RING_BUF_SIZE) {
    *out_ok = false; /* full */
    return ERR_OK;
  }
  rb->buf[head & RING_BUF_MASK] = element;
  rb->head = head + 1U;
  *out_ok = true;
  return ERR_OK;
}

error_t RingBuf_Pop(RingBuffer_t *rb, uint8_t *element, bool *out_ok) {
  uint32_t tail;

  if (rb == NULL || element == NULL || out_ok == NULL) {
    return ERR_NULL_PTR;
  }

  tail = rb->tail;
  if (rb->head == tail) {
    *out_ok = false; /* empty */
    return ERR_OK;
  }
  *element = rb->buf[tail & RING_BUF_MASK];
  rb->tail = tail + 1U;
  *out_ok = true;
  return ERR_OK;
}

error_t RingBuf_Count(const RingBuffer_t *rb, uint32_t *out_count) {
  if (rb == NULL || out_count == NULL) {
    return ERR_NULL_PTR;
  }
  *out_count = rb->head - rb->tail;
  return ERR_OK;
}

error_t RingBuf_IsEmpty(const RingBuffer_t *rb, bool *out_empty) {
  if (rb == NULL || out_empty == NULL) {
    return ERR_NULL_PTR;
  }
  *out_empty = (rb->head == rb->tail);
  return ERR_OK;
}

error_t RingBuf_IsFull(const RingBuffer_t *rb, bool *out_full) {
  if (rb == NULL || out_full == NULL) {
    return ERR_NULL_PTR;
  }
  *out_full = ((rb->head - rb->tail) >= RING_BUF_SIZE);
  return ERR_OK;
}

/* Private functions
 * -------------------------------------------------------------*/
