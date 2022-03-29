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
 * @file stream.h
 * @brief Character stream.
 */

#ifndef NESLA_STREAM_H_
#define NESLA_STREAM_H_

#include <common.h>

/*!
 * @enum nesla_character_e
 * @brief Character type.
 */
typedef enum {
    CHARACTER_END = 0,      /*!< End-of-file character */
    CHARACTER_ALPHA,        /*!< Alpha character */
    CHARACTER_DIGIT,        /*!< Digit character */
    CHARACTER_SYMBOL,       /*!< Symbol character */
    CHARACTER_WHITESPACE,   /*!< Whitespace character */
} nesla_character_e;

/*!
 * @struct nesla_stream_t
 * @brief Stream context.
 */
typedef struct {
    nesla_reader_t reader;  /*!< Reader context */
    uint8_t character;      /*!< Current character */
    size_t column;          /*!< Current column */
    size_t row;             /*!< Current row */
} nesla_stream_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*!
 * @brief Get stream context character.
 * @param[in,out] stream Constant pointer to stream context
 * @return Stream character
 */
char nesla_stream_get(const nesla_stream_t *stream);

/*!
 * @brief Get stream context column.
 * @param[in,out] stream Constant pointer to stream context
 * @return Stream column
 */
size_t nesla_stream_get_column(const nesla_stream_t *stream);

/*!
 * @brief Get stream context file path.
 * @param[in,out] stream Constant pointer to stream context
 * @return File path
 */
const char *nesla_stream_get_path(const nesla_stream_t *stream);

/*!
 * @brief Get stream context row.
 * @param[in,out] stream Constant pointer to stream context
 * @return Stream row
 */
size_t nesla_stream_get_row(const nesla_stream_t *stream);

/*!
 * @brief Get stream context character type.
 * @param[in,out] stream Constant pointer to stream context
 * @return Stream character type
 */
nesla_character_e nesla_stream_get_type(const nesla_stream_t *stream);

/*!
 * @brief Initialize stream context.
 * @param[in,out] stream Pointer to stream context
 * @param[in] path Constant pointer to file path
 * @return NESLA_ERROR on failure, NESLA_SUCCESS otherwise
 */
nesla_error_e nesla_stream_initialize(nesla_stream_t *stream, const char *path);

/*!
 * @brief Move stream context to next character.
 * @param[in,out] stream Pointer to stream context
 * @return NESLA_ERROR on failure, NESLA_SUCCESS otherwise
 */
nesla_error_e nesla_stream_next(nesla_stream_t *stream);

/*!
 * @brief Reset stream context.
 * @param[in,out] stream Pointer to stream context
 * @return NESLA_ERROR on failure, NESLA_SUCCESS otherwise
 */
nesla_error_e nesla_stream_reset(nesla_stream_t *stream);

/*!
 * @brief Uninitialize stream context.
 * @param[in,out] stream Pointer to stream context
 */
void nesla_stream_uninitialize(nesla_stream_t *stream);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* NESLA_STREAM_H_ */
