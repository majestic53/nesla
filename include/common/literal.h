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
 * @file literal.h
 * @brief Common literal.
 */

#ifndef NESLA_LITERAL_H_
#define NESLA_LITERAL_H_

#include <define.h>

/*!
 * @struct nesla_literal_t
 * @brief Literal context.
 */
typedef struct {
    uint8_t *buffer;    /*!< Literal buffer */
    size_t capacity;    /*!< Literal capacity */
    size_t length;      /*!< Literal length */
} nesla_literal_t;

#ifdef __cplusplus
export "C" {
#endif /* __cplusplus */

/*!
 * @brief Allocate literal context.
 * @param[in,out] literal Pointer to literal context
 * @return NESLA_ERROR on failure, NESLA_SUCCESS otherwise
 */
nesla_error_e nesla_literal_allocate(nesla_literal_t *literal);

/*!
 * @brief Append character to literal context.
 * @param[in,out] literal Pointer to literal context
 * @param[in] value Character to append
 * @return NESLA_ERROR on failure, NESLA_SUCCESS otherwise
 */
nesla_error_e nesla_literal_append(nesla_literal_t *literal, uint8_t value);

/*!
 * @brief Copy literal context to literal context.
 * @param[in,out] literal Pointer to literal context
 * @param[in] value Constant pointer to literal context
 * @return NESLA_ERROR on failure, NESLA_SUCCESS otherwise
 */
nesla_error_e nesla_literal_copy(nesla_literal_t *literal, const nesla_literal_t *value);

/*!
 * @brief Free literal context.
 * @param[in,out] literal Pointer to literal context
 */
void nesla_literal_free(nesla_literal_t *literal);

/*!
 * @brief Get literal context character string.
 * @param[in,out] literal Pointer to literal context
 * @return Constant pointer to character string
 */
const uint8_t *nesla_literal_get(const nesla_literal_t *literal);

/*!
 * @brief Get literal context character string length.
 * @param[in,out] literal Pointer to literal context
 * @return Character string length
 */
size_t nesla_literal_get_length(const nesla_literal_t *literal);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* NESLA_LITERAL_H_ */
