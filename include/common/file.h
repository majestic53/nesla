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
 * @file file.h
 * @brief Read/write files.
 */

#ifndef NESLA_FILE_H_
#define NESLA_FILE_H_

/*!
 * @struct nesla_file_t
 * @brief NESLA file context.
 */
typedef struct {
    const char *path;   /*!< File path */
    FILE *base;         /*!< File base */
    FILE *offset;       /*!< File offset */
} nesla_file_t;

#include <define.h>

/*!
 * @brief Close file.
 * @param[in,out] file Pointer to file context
 */
void nesla_file_close(nesla_file_t *file);

/*!
 * @brief Get file size in bytes..
 * @param[in] file Pointer to file context
 * @return File size in bytes
 */
size_t nesla_file_get_size(const nesla_file_t *file);

/*!
 * @brief Open file at path.
 * @param[in,out] file Pointer to file context
 * @param[in] path Constant pointer to path string
 * @param[in] create Create file if not found
 * @return NESLA_FAILURE on failure, NESLA_SUCCESS otherwise
 */
nesla_error_e nesla_file_open(nesla_file_t *file, const char *path, bool create);

/*!
 * @brief Read data from file.
 * @param[in,out] file Pointer to file context
 * @param[in,out] data Pointer to data buffer
 * @param[in,out] length Length of data buffer in bytes
 * @return NESLA_FAILURE on failure, NESLA_SUCCESS otherwise
 */
nesla_error_e nesla_file_read(nesla_file_t *file, uint8_t *data, size_t *length);

/*!
 * @brief Seek to byte within file.
 * @param[in,out] file Pointer to file context
 * @param[in] offset Byte offset
 * @param[in] relative Byte offset relative or absolute
 * @return NESLA_FAILURE on failure, NESLA_SUCCESS otherwise
 */
nesla_error_e nesla_file_seek(nesla_file_t *file, size_t offset, bool relative);

/*!
 * @brief Write data to file.
 * @param[in,out] file Pointer to file context
 * @param[in,out] data Pointer to data buffer
 * @param[in,out] length Length of data buffer in bytes
 * @return NESLA_FAILURE on failure, NESLA_SUCCESS otherwise
 */
nesla_error_e nesla_file_write(nesla_file_t *file, const uint8_t *data, size_t *length);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* NESLA_FILE_H_ */
