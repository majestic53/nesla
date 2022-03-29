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
 * @file reader.h
 * @brief Common file reader.
 */

#ifndef NESLA_READER_H_
#define NESLA_READER_H_

#include <error.h>

/*!
 * @struct nesla_reader_t
 * @brief Reader context.
 */
typedef struct {
    FILE *base;         /*!< File handle base */
    FILE *offset;       /*!< File handle offset */
    const char *path;   /*!< File path */
} nesla_reader_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*!
 * @brief Close reader context.
 * @param[in,out] reader Pointer to reader context
 */
void nesla_reader_close(nesla_reader_t *reader);

/*!
 * @brief Get string from reader context.
 * @param[in,out] reader Pointer to reader context
 * @param[in,out] data String from reader context
 * @param[in] length String length in bytes
 * @return NESLA_ERROR on failure, NESLA_SUCCESS otherwise
 */
nesla_error_e nesla_reader_get(nesla_reader_t *reader, uint8_t *data, size_t length);

/*!
 * @brief Get reader context file path.
 * @param[in] reader Pointer to reader context
 * @return File path
 */
const char *nesla_reader_get_path(const nesla_reader_t *reader);

/*!
 * @brief Get reader context file size.
 * @param[in,out] reader Pointer to reader context
 * @param[in,out] size File size in bytes
 * @return NESLA_ERROR on failure, NESLA_SUCCESS otherwise
 */
nesla_error_e nesla_reader_get_size(nesla_reader_t *reader, size_t *size);

/*!
 * @brief Open reader context with a path.
 * @param[in,out] reader Pointer to reader context
 * @param[in] path Constant pointer to file path
 * @return NESLA_ERROR on failure, NESLA_SUCCESS otherwise
 */
nesla_error_e nesla_reader_open(nesla_reader_t *reader, const char *path);

/*!
 * @brief Reset reader context.
 * @param[in,out] reader Pointer to reader context
 * @return NESLA_ERROR on failure, NESLA_SUCCESS otherwise
 */
nesla_error_e nesla_reader_reset(nesla_reader_t *reader);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* NESLA_READER_H_ */
