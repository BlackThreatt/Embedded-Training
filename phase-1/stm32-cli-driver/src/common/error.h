/**
 ******************************************************************************
 * @file           : error.h
 * @brief          : Common error type and error code definitions
 * @author         : Mohamed Ali BESSAIDI
 * @date           : 1 Aug 2026
 *******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 MOHAMED ALI BESSAIDI.
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef ERROR_H
#define ERROR_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Common status/error type returned by driver and HAL functions.
 *        Zero (ERR_OK) always means success; any negative value is an
 *        error.
 */
typedef enum {
  ERR_OK = 0,             /*!< Success */
  ERR_NULL_PTR = -1,      /*!< A required pointer argument was NULL */
  ERR_INVALID_PARAM = -2, /*!< An argument was outside its valid range */
  ERR_TIMEOUT = -3,       /*!< Operation did not complete within budget */
  ERR_BUSY = -4,          /*!< Peripheral/resource busy, try again later */
  ERR_BUFFER_FULL = -5,   /*!< Ring buffer or FIFO had no room */
  ERR_BUFFER_EMPTY = -6,  /*!< Ring buffer had nothing to read */
  ERR_NOT_INIT = -7,      /*!< Called before the relevant Init() */
  ERR_HW_FAULT =
      -8, /*!< Peripheral reported an error flag (e.g. framing/overrun) */
} error_t;

#ifdef __cplusplus
}
#endif

#endif /* ERROR_H */
