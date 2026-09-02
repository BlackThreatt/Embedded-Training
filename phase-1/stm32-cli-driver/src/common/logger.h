/**
 ******************************************************************************
 * @file           : logger.h
 * @brief          : Header file for logger.c
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
#ifndef LOGGER_H
#define LOGGER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "error.h"
#include "printf.h"
#include <stddef.h>
/* Exported constants --------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
/**
 * @brief  Initializes the debug UART used for logging.
 * @retval ERR_OK on success, or the first UART_DRV_Init failure encountered.
 */
error_t Logger_Init(void);

/**
 * @brief  Prints str contents over the debug UART channel.
 * @param[in] str String containing message to be printed.
 * @retval ERR_OK on success, ERR_NULL_PTR if str is NULL, or the first
 *         UART_DRV_Transmit failure encountered.
 */
error_t Logger_PrintString(const char *str);

/* Exported macros -----------------------------------------------------------*/
#ifndef RELEASE
#define LOGGER(level, msg, ...)                                                \
  do {                                                                         \
    char log_buf[128];                                                         \
    snprintf(log_buf, sizeof(log_buf), "[%s] %s \r\n", level,                  \
             msg __VA_ARGS__);                                                 \
    Logger_PrintString(log_buf);                                               \
  } while (0)

#define LOG_DEBUG(...) LOGGER("DEBUG", __VA_ARGS__)
#define LOG_INFO(...) LOGGER("INFO", __VA_ARGS__)
#define LOG_ERROR(...) LOGGER("ERROR", __VA_ARGS__)

#else
#define LOG_DEBUG(...) ((void)0)
#define LOG_INFO(...) ((void)0)
#define LOG_ERROR(...) ((void)0)

#endif

#ifdef __cplusplus
}
#endif

#endif /* LOGGER_H */
