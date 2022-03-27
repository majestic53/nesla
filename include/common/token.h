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
 * @file token.h
 * @brief Token.
 */

#ifndef NESLA_TOKEN_H_
#define NESLA_TOKEN_H_

#include <define.h>

/*!
 * @enum nesla_token_e
 * @brief Token type.
 */
typedef enum {
    TOKEN_END = 0,              /*!< End token */
    TOKEN_DIRECTIVE,            /*!< Directive token */
    TOKEN_IDENTIFIER,           /*!< Identifier token */
    TOKEN_INSTRUCTION,          /*!< Instruction token */
    TOKEN_LABEL,                /*!< Label token */
    TOKEN_LITERAL,              /*!< Literal token */
    TOKEN_OPERAND,              /*!< Operand token */
    TOKEN_SCALAR,               /*!< Scalar token */
    TOKEN_SYMBOL,               /*!< Symbol token */
    TOKEN_MAX,                  /*!< Max token */
} nesla_token_e;

/*!
 * @struct nesla_token_t
 * @brief Token context.
 */
typedef struct {
    nesla_token_e type;         /*!< Token type */
    int subtype;                /*!< Token Subtype */
    const char *path;           /*!< Token file path */
    size_t column;              /*!< Token file column */
    size_t row;                 /*!< Token file row */

    union {

        struct {
            const char *data;   /*!< Token literal */
            size_t capacity;    /*!< Token literal capacity */
            size_t length;      /*!< Token literal length */
        } literal;

        uint16_t scalar;        /*!< Token scalar */
    } value;
} nesla_token_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*!
 * @brief Allocate token context.
 * @param token Pointer to token context
 * @param type Token type
 * @param subtype Token subtype
 * @param path Constant pointer to token path
 * @param column Token column
 * @param row Token row
 * @return NESLA_ERROR on failure, NESLA_SUCCESS otherwise
 */
nesla_error_e nesla_token_allocate(nesla_token_t *token, nesla_token_e type, int subtype, const char *path, size_t column, size_t row);

/*!
 * @brief Append character to literal in token context.
 * @param token Pointer to token context
 * @param value Token literal character
 * @return NESLA_ERROR on failure, NESLA_SUCCESS otherwise
 */
nesla_error_e nesla_token_append_literal(nesla_token_t *token, char value);

/*!
 * @brief Free token context.
 * @param token Pointer to token context
 */
void nesla_token_free(nesla_token_t *token);

/*!
 * @brief Get token context column.
 * @param token Pointer to token context
 * @return Token context column
 */
size_t nesla_token_column(nesla_token_t *token);

/*!
 * @brief Get token context literal value.
 * @param token Pointer to token context
 * @param length Pointer to token literal length buffer
 * @return Constant pointer to token context literal value
 */
const char *nesla_token_get_literal(nesla_token_t *token, size_t *length);

/*!
 * @brief Get token context path.
 * @param token Pointer to token context
 * @return Constant pointer to token context path
 */
const char *nesla_token_get_path(nesla_token_t *token);

/*!
 * @brief Get token context row.
 * @param token Pointer to token context
 * @return Token context row
 */
size_t nesla_token_row(nesla_token_t *token);

/*!
 * @brief Get token context scalar value.
 * @param token Pointer to token context
 * @return Token context scalar value
 */
uint16_t nesla_token_get_scalar(nesla_token_t *token);

/*!
 * @brief Set token context scalar value.
 * @param token Pointer to token context
 * @param value Token context scalar value
 */
void nesla_token_set_scalar(nesla_token_t *token, uint16_t value);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* NESLA_TOKEN_H_ */
