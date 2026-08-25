/**
 ******************************************************************************
 * @file           : RingBuffer.h
 * @brief          : Header file for RingBuffer.c
 * @author         : Mohamed Ali BESSAIDI
 * @date           : 25 Aug 2026
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

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

/**
 * @brief Initalizes ring buffer structure to null.
 * @param[in] rb Pointer to RingBuffer_t configuration structure.
 * @retval None
 */
void RingBuf_Init(RingBuffer_t *rb) {
  rb->head = 0;
  rb->tail = 0;
}

/**
 * @brief Writes byte element to a given ring buffer.
 * @param[in] rb Pointer to RingBuffer_t configuration structure.
 * @param[in] element Byte to be pushed to ring buffer.
 * @retval true of success, false otherwise
 */
bool RingBuf_Push(RingBuffer_t *rb, uint8_t element) {
  uint32_t head = rb->head;
  if ((head - rb->tail) >= RING_BUF_SIZE) {
    return false; /* full */
  }
  rb->buf[head & RING_BUF_MASK] = element;
  rb->head = head + 1U;
  return true;
}

/**
 * @brief Reads byte element from a given ring buffer.
 * @param[in] rb Pointer to RingBuffer_t configuration structure.
 * @param[out] element Pointer to byte that will store popped value.
 * @retval true if success, false otherwise
 */
bool RingBuf_Pop(RingBuffer_t *rb, uint8_t *element) {
  uint32_t tail = rb->tail;
  if (rb->head == tail) {
    return false; /* empty */
  }
  *element = rb->buf[tail & RING_BUF_MASK];
  rb->tail = tail + 1U;
  return true;
}

/**
 * @brief Reads the size of a given ring buffer.
 * @param[in] rb Pointer to RingBuffer_t configuration structure.
 * @retval size of ring buffer
 */
uint32_t RingBuf_Count(const RingBuffer_t *rb) { return rb->head - rb->tail; }

/**
 * @brief Checks whether ring buffer is empty.
 * @param[in] rb Pointer to RingBuffer_t configuration structure.
 * @retval true if empty, false otherwise
 */
bool RingBuf_IsEmpty(const RingBuffer_t *rb) { return rb->head == rb->tail; }

/**
 * @brief Checks whether ring buffer is full.
 * @param[in] rb Pointer to RingBuffer_t configuration structure.
 * @retval true if full, false otherwise
 */
bool RingBuf_IsFull(const RingBuffer_t *rb) {
  return (rb->head - rb->tail) >= RING_BUF_SIZE;
}
