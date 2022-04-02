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
 * @file lexer.h
 * @brief Token lexer.
 */

#ifndef NESLA_LEXER_H_
#define NESLA_LEXER_H_

#include <stream.h>

/*!
 * @struct nesla_lexer_t
 * @brief Lexer context.
 */
typedef struct {
    nesla_stream_t stream;  /*!< Stream context */
    nesla_list_t token;     /*!< Token list context */
    size_t index;           /*!< Token list index */
} nesla_lexer_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*!
 * @brief Get lexer context token.
 * @param[in,out] lexer Constant pointer to lexer context
 * @param[in,out] token Pointer to token context
 * @return NESLA_ERROR on failure, NESLA_SUCCESS otherwise
 */
nesla_error_e nesla_lexer_get(const nesla_lexer_t *lexer, nesla_token_t **token);

/*!
 * @brief Initialize lexer context.
 * @param[in,out] lexer Pointer to lexer context
 * @param[in] path Constant pointer to file path
 * @return NESLA_ERROR on failure, NESLA_SUCCESS otherwise
 */
nesla_error_e nesla_lexer_initialize(nesla_lexer_t *lexer, const char *path);

/*!
 * @brief Move lexer context to next character.
 * @param[in,out] lexer Pointer to lexer context
 * @return NESLA_ERROR on failure, NESLA_SUCCESS otherwise
 */
nesla_error_e nesla_lexer_next(nesla_lexer_t *lexer);

/*!
 * @brief Reset lexer context.
 * @param[in,out] lexer Pointer to lexer context
 * @return NESLA_ERROR on failure, NESLA_SUCCESS otherwise
 */
nesla_error_e nesla_lexer_reset(nesla_lexer_t *lexer);

/*!
 * @brief Uninitialize lexer context.
 * @param[in,out] lexer Pointer to lexer context
 */
void nesla_lexer_uninitialize(nesla_lexer_t *lexer);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* NESLA_LEXER_H_ */
