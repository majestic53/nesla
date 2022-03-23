/*
 * NESLA
 * Copyright (C) 2022 David Jolly
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*!
 * @file nesla.h
 * @brief NESLA interface.
 */

#ifndef NESLA_H_
#define NESLA_H_

#define NESLA_API_VERSION_1 1                   /*!< Interface version 1 */
#define NESLA_API_VERSION NESLA_API_VERSION_1   /*!< Current interface version */

/*!
 * @enum nesla_error_e
 * @brief Error code.
 */
typedef enum {
    NESLA_FAILURE = -1,                         /*!< Operation failed, call nesla_get_error */
    NESLA_SUCCESS,                              /*!< Operation succeeded */
} nesla_error_e;

/*!
 * @struct nesla_t
 * @brief NESLA context.
 */
typedef struct {
    const char *input;                          /*!< Input path */
    const char *output;                         /*!< Output directory */
} nesla_t;

/*!
 * @struct nesla_version_t
 * @brief Version context.
 */
typedef struct {
    int major;                                  /*!< Major version */
    int minor;                                  /*!< Minor version */
    int patch;                                  /*!< Patch version */
} nesla_version_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*!
 * @brief Assemble source files defined in context.
 * @param[in] context Constant pointer to caller defined context
 * @return NESLA_FAILURE on failure, NESLA_SUCCESS otherwise
 */
nesla_error_e nesla(const nesla_t *context);

/*!
 * @brief Get error string.
 * @return Constant pointer to error string
 */
const char *nesla_get_error(void);

/*!
 * @brief Get version.
 * @return Constant pointer to version
 */
const nesla_version_t *nesla_get_version(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* NESLA_H_ */
