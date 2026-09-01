/**
 ******************************************************************************
 * @file           : RingBuffer.h
 * @brief          : Header file for RingBuffer.c
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
#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "error.h"
#include <stdbool.h>
#include <stdint.h>

/* Exported constants --------------------------------------------------------*/
#define RING_BUF_SIZE (256U) /* must be power of 2 */
#define RING_BUF_MASK (RING_BUF_SIZE - 1U)

_Static_assert((RING_BUF_SIZE & RING_BUF_MASK) == 0u,
               "RING_BUF_SIZE must be a power of two");

/* Exported macros -----------------------------------------------------------*/

#if defined(__GNUC__) || defined(__clang__)
#define ERR_CHECK __attribute__((warn_unused_result))
#else
#define ERR_CHECK
#endif

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
 * @brief  Initializes a ring buffer to the empty state.
 * @param[in] rb Pointer to RingBuffer_t configuration structure.
 * @retval ERR_OK on success, ERR_NULL_PTR if rb is NULL.
 */
ERR_CHECK error_t RingBuf_Init(RingBuffer_t *rb);

/**
 * @brief  Writes a byte element to a given ring buffer.
 * @param[in]  rb        Pointer to RingBuffer_t configuration structure.
 * @param[in]  element   Byte to be pushed to the ring buffer.
 * @param[out] out_ok    Pointer to where the push result is written: true
 *                       if the byte was stored, false if the buffer was
 *                       full.
 * @retval ERR_OK on success, ERR_NULL_PTR if rb or out_ok is NULL.
 */
ERR_CHECK error_t RingBuf_Push(RingBuffer_t *rb, uint8_t element, bool *out_ok);

/**
 * @brief  Reads a byte element from a given ring buffer.
 * @param[in]  rb      Pointer to RingBuffer_t configuration structure.
 * @param[out] element Pointer to byte that will store the popped value.
 * @param[out] out_ok  Pointer to where the pop result is written: true if
 *                     a byte was read, false if the buffer was empty.
 * @retval ERR_OK on success, ERR_NULL_PTR if rb, element, or out_ok is
 *         NULL.
 */
ERR_CHECK error_t RingBuf_Pop(RingBuffer_t *rb, uint8_t *element, bool *out_ok);

/**
 * @brief  Reads the current occupied count of a given ring buffer.
 * @param[in]  rb        Pointer to RingBuffer_t configuration structure.
 * @param[out] out_count Pointer to where the occupied count is written.
 * @retval ERR_OK on success, ERR_NULL_PTR if rb or out_count is NULL.
 */
ERR_CHECK error_t RingBuf_Count(const RingBuffer_t *rb, uint32_t *out_count);

/**
 * @brief  Checks whether a given ring buffer is empty.
 * @param[in]  rb        Pointer to RingBuffer_t configuration structure.
 * @param[out] out_empty Pointer to where the result is written.
 * @retval ERR_OK on success, ERR_NULL_PTR if rb or out_empty is NULL.
 */
ERR_CHECK error_t RingBuf_IsEmpty(const RingBuffer_t *rb, bool *out_empty);

/**
 * @brief  Checks whether a given ring buffer is full.
 * @param[in]  rb       Pointer to RingBuffer_t configuration structure.
 * @param[out] out_full Pointer to where the result is written.
 * @retval ERR_OK on success, ERR_NULL_PTR if rb or out_full is NULL.
 */
ERR_CHECK error_t RingBuf_IsFull(const RingBuffer_t *rb, bool *out_full);

#ifdef __cplusplus
}
#endif

#endif /* RINGBUFFER_H */
