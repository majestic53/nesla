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
            const char *str;    /*!< Token literal */
            size_t length;      /*!< Token literal length */
        } literal;

        uint16_t scalar;        /*!< Token scalar */
    } value;
} nesla_token_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* TODO */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* NESLA_TOKEN_H_ */
