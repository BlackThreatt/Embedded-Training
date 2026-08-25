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
#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>

/* Exported constants --------------------------------------------------------*/
#define RING_BUF_SIZE (256U) /* must be power of 2 */
#define RING_BUF_MASK (RING_BUF_SIZE - 1U)

_Static_assert((RING_BUF_SIZE & RING_BUF_MASK) == 0u,
               "RING_BUF_SIZE must be a power of two");

/* Exported macros -----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/**
 * @brief  RingBuffer configuration structure
 */
typedef struct {
  volatile uint8_t
      buf[RING_BUF_SIZE]; /*!< Buffer array that stores ring buffer data */
  volatile uint32_t head; /*!< Ringbuffer head index */
  volatile uint32_t tail; /*!< Ring buffer tail index */
} RingBuffer_t;

/* Exported functions prototypes ---------------------------------------------*/

/**
 * @brief Initalizes ring buffer structure to null.
 * @param[in] rb Pointer to RingBuffer_t configuration structure.
 * @retval None
 */
void RingBuf_Init(RingBuffer_t *rb);

/**
 * @brief Writes byte element to a given ring buffer.
 * @param[in] rb Pointer to RingBuffer_t configuration structure.
 * @param[in] element Byte to be pushed to ring buffer.
 * @retval true of success, false otherwise
 */
bool RingBuf_Push(RingBuffer_t *rb, uint8_t element);

/**
 * @brief Reads byte element from a given ring buffer.
 * @param[in] rb Pointer to RingBuffer_t configuration structure.
 * @param[out] element Pointer to byte that will store popped value.
 * @retval true if success, false otherwise
 */
bool RingBuf_Pop(RingBuffer_t *rb, uint8_t *element);

/**
 * @brief Reads the size of a given ring buffer.
 * @param[in] rb Pointer to RingBuffer_t configuration structure.
 * @retval size of ring buffer
 */
uint32_t RingBuf_Count(const RingBuffer_t *rb);

/**
 * @brief Checks whether ring buffer is empty.
 * @param[in] rb Pointer to RingBuffer_t configuration structure.
 * @retval true if empty, false otherwise
 */
bool RingBuf_IsEmpty(const RingBuffer_t *rb);

/**
 * @brief Checks whether ring buffer is full.
 * @param[in] rb Pointer to RingBuffer_t configuration structure.
 * @retval true if full, false otherwise
 */
bool RingBuf_IsFull(const RingBuffer_t *rb);

#ifdef __cplusplus
}
#endif

#endif /* RINGBUFFER_H */
