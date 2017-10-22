/*
    ChibiOS - Copyright (C) 2006..2016 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file    CRYPv1/hal_cry_lld.h
 * @brief   STM32 cryptographic subsystem low level driver header.
 *
 * @addtogroup CRYPTO
 * @{
 */

#ifndef HAL_CRYPTO_LLD_H
#define HAL_CRYPTO_LLD_H

#if (HAL_USE_CRY == TRUE) || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @name    Driver capability switches
 * @{
 */
#define CRY_LLD_SUPPORTS_AES_ECB            TRUE
#define CRY_LLD_SUPPORTS_AES_CBC            TRUE
#define CRY_LLD_SUPPORTS_AES_CFB            TRUE
#define CRY_LLD_SUPPORTS_AES_CTR            TRUE
/** @{ */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    PLATFORM configuration options
 * @{
 */
/**
 * @brief   CRY1 driver enable switch.
 * @details If set to @p TRUE the support for CRY1 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(PLATFORM_CRY_USE_CRY1) || defined(__DOXYGEN__)
#define PLATFORM_CRY_USE_CRY1                  FALSE
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   CRY key identifier type.
 */
typedef uint32_t crykey_t;

/**
 * @brief   Type of a structure representing an CRY driver.
 */
typedef struct CRYDriver CRYDriver;

/**
 * @brief   CRY notification callback type.
 *
 * @param[in] cryp      pointer to the @p CRYDriver object triggering the
 *                      callback
 */
typedef void (*crycallback_t)(CRYDriver *cryp);

/**
 * @brief   CRY error callback type.
 *
 * @param[in] cryp      pointer to the @p CRYDriver object triggering the
 *                      callback
 * @param[in] err       CRY error code
 */
typedef void (*cryerrorcallback_t)(CRYDriver *cryp, cryerror_t err);

/**
 * @brief   Driver configuration structure.
 * @note    It could be empty on some architectures.
 */
typedef struct {
  uint32_t                  dummy;
} CRYConfig;

/**
 * @brief   Structure representing an CRY driver.
 */
struct CRYDriver {
  /**
   * @brief Driver state.
   */
  crystate_t                state;
  /**
   * @brief Current configuration data.
   */
  const CRYConfig           *config;
  /**
   * @brief Waiting thread.
   */
  thread_reference_t        thread;
#if (CRY_USE_MUTUAL_EXCLUSION == TRUE) || defined(__DOXYGEN__)
  /**
   * @brief Mutex protecting the peripheral.
   */
  mutex_t                   mutex;
#endif
#if defined(CRY_DRIVER_EXT_FIELDS)
  CRY_DRIVER_EXT_FIELDS
#endif
  /* End of the mandatory fields.*/
};

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if (PLATFORM_CRY_USE_CRY1 == TRUE) && !defined(__DOXYGEN__)
extern CRYDriver CRYD1;
#endif

#ifdef __cplusplus
extern "C" {
#endif
  void cry_lld_init(void);
  void cry_lld_start(CRYDriver *cryp);
  void cry_lld_stop(CRYDriver *cryp);
#ifdef __cplusplus
}
#endif

#endif /* HAL_USE_CRY == TRUE */

#endif /* HAL_CRYPTO_LLD_H */

/** @} */