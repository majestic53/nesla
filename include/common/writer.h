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
 * @file writer.h
 * @brief Common file writer.
 */

#ifndef NESLA_WRITER_H_
#define NESLA_WRITER_H_

#include <error.h>

/*!
 * @struct nesla_writer_t
 * @brief Writer context.
 */
typedef struct {
    FILE *base;         /*!< File handle base */
    FILE *offset;       /*!< File handle offset */
    const char *path;   /*!< File path */
} nesla_writer_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*!
 * @brief Close writer context.
 * @param[in,out] writer Pointer to writer context
 */
void nesla_writer_close(nesla_writer_t *writer);

/*!
 * @brief Get writer context file path.
 * @param[in] writer Pointer to writer context
 * @return File path
 */
const char *nesla_writer_get_path(const nesla_writer_t *writer);

/*!
 * @brief Get writer context file size.
 * @param[in,out] writer Pointer to writer context
 * @param[in,out] size File size in bytes
 * @return NESLA_ERROR on failure, NESLA_SUCCESS otherwise
 */
nesla_error_e nesla_writer_get_size(nesla_writer_t *writer, size_t *size);

/*!
 * @brief Open writer context with a path.
 * @param[in,out] writer Pointer to writer context
 * @param[in] path Constant pointer to file path
 * @param[in] create Create file if none exists
 * @return NESLA_ERROR on failure, NESLA_SUCCESS otherwise
 */
nesla_error_e nesla_writer_open(nesla_writer_t *writer, const char *path, bool create);

/*!
 * @brief Put string into writer context.
 * @param[in,out] writer Pointer to writer context
 * @param[in] data String into writer context
 * @param[in] length String length in bytes
 * @return NESLA_ERROR on failure, NESLA_SUCCESS otherwise
 */
nesla_error_e nesla_writer_put(nesla_writer_t *writer, const uint8_t *data, size_t length);

/*!
 * @brief Reset writer context.
 * @param[in,out] writer Pointer to writer context
 * @return NESLA_ERROR on failure, NESLA_SUCCESS otherwise
 */
nesla_error_e nesla_writer_reset(nesla_writer_t *writer);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* NESLA_WRITER_H_ */
