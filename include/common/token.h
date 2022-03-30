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
 * @brief Common token.
 */

#ifndef NESLA_TOKEN_H_
#define NESLA_TOKEN_H_

#include <literal.h>

/*!
 * @enum nesla_token_e
 * @brief Token type.
 */
typedef enum {
    TOKEN_DIRECTIVE = 0,        /*!< Directive token */
    TOKEN_IDENTIFIER,           /*!< Identifier token */
    TOKEN_INSTRUCTION,          /*!< Instruction token */
    TOKEN_LABEL,                /*!< Label token */
    TOKEN_LITERAL,              /*!< Literal token */
    TOKEN_OPERAND,              /*!< Operand token */
    TOKEN_SCALAR,               /*!< Scalar token */
    TOKEN_SYMBOL,               /*!< Symbol token */
} nesla_token_e;

/*!
 * @struct nesla_token_t
 * @brief Token context.
 */
typedef struct {
    nesla_token_e type;         /*!< Token type */
    int subtype;                /*!< Token subtype */
    const char *path;           /*!< Token file path */
    size_t line;                /*!< Token file line */
    nesla_literal_t literal;    /*!< Token literal context */
    uint16_t scalar;            /*!< Token scalar value */
} nesla_token_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*!
 * @brief Free token context.
 * @param[in,out] token Pointer to token context
 */
void nesla_token_free(nesla_token_t *token);

/*!
 * @brief Get token context file line.
 * @param[in] token Constant pointer to token context
 * @return File line
 */
size_t nesla_token_get_line(const nesla_token_t *token);

/*!
 * @brief Get token context literal value.
 * @param[in] token Constant pointer to token context
 * @return Constant pointer to literal value
 */
const uint8_t *nesla_token_get_literal(const nesla_token_t *token);

/*!
 * @brief Get token context literal length.
 * @param[in] token Constant pointer to token context
 * @return Literal length
 */
size_t nesla_token_get_literal_length(const nesla_token_t *token);

/*!
 * @brief Get token context file path.
 * @param[in] token Constant pointer to token context
 * @return Constant pointer to file path
 */
const char *nesla_token_get_path(const nesla_token_t *token);

/*!
 * @brief Get token context scalar value.
 * @param[in] token Constant pointer to token context
 * @return Scalar value
 */
uint16_t nesla_token_get_scalar(const nesla_token_t *token);

/*!
 * @brief Get token context subtype.
 * @param[in] token Constant pointer to token context
 * @return Token subtype
 */
int nesla_token_get_subtype(const nesla_token_t *token);

/*!
 * @brief Get token context type.
 * @param[in] token Constant pointer to token context
 * @return Token type
 */
nesla_token_e nesla_token_get_type(const nesla_token_t *token);

/*!
 * @brief Set token context.
 * @param[in,out] token Pointer to token context
 * @param[in] type Token type
 * @param[in] subtype Token subtype
 * @param[in] path Constant pointer to token file path
 * @param[in] line Token file line
 */
void nesla_token_set(nesla_token_t *token, nesla_token_e type, int subtype, const char *path, size_t line);

/*!
 * @brief Set token context literal value.
 * @param[in,out] token Pointer to token context
 * @param[in] literal Constant pointer to literal context
 * @return NESLA_ERROR on failure, NESLA_SUCCESS otherwise
 */
nesla_error_e nesla_token_set_literal(nesla_token_t *token, const nesla_literal_t *literal);

/*!
 * @brief Set token context scalar value.
 * @param[in,out] token Pointer to token context
 * @param[in] scalar Scalar value
 */
void nesla_token_set_scalar(nesla_token_t *token, uint16_t scalar);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* NESLA_TOKEN_H_ */
