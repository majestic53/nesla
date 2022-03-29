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
 * @file token.c
 * @brief Common token.
 */

#include <common.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

nesla_error_e nesla_token_allocate(nesla_token_t *token, nesla_token_e type, int subtype, const char *path, size_t column, size_t row)
{
    nesla_error_e result = NESLA_SUCCESS;

    switch(type) {
        case TOKEN_LABEL:
        case TOKEN_LITERAL:
            token->literal.capacity = 16;
            token->literal.length = 0;

            if(!(token->literal.data = calloc(token->literal.capacity, sizeof(char)))) {
                result = SET_ERROR("Failed to allocate token literal: %p", token->literal.data);
                goto exit;
            }
            break;
        default:
            token->scalar = 0;
            break;
    }

    token->type = type;
    token->subtype = subtype;
    token->path = path;
    token->column = column;
    token->row = row;

exit:
    return result;
}

nesla_error_e nesla_token_append_literal(nesla_token_t *token, char value)
{
    nesla_error_e result = NESLA_SUCCESS;

    if(token->literal.length + 1 >= token->literal.capacity) {
        token->literal.capacity *= 2;

        if(!(token->literal.data = realloc(token->literal.data, token->literal.capacity))) {
            result = SET_ERROR("Failed to allocate token literal: %p", token->literal.data);
            goto exit;
        }
    }

    token->literal.data[token->literal.length++] = value;

exit:
    return result;
}

void nesla_token_free(nesla_token_t *token)
{

    if(token->literal.data) {
        free(token->literal.data);
    }

    memset(token, 0, sizeof(*token));
}

size_t nesla_token_get_column(const nesla_token_t *token)
{
    return token->column;
}

const char *nesla_token_get_literal(const nesla_token_t *token, size_t *length)
{

    if(length) {
        *length = token->literal.length;
    }

    return token->literal.data;
}

const char *nesla_token_get_path(const nesla_token_t *token)
{
    return token->path;
}

size_t nesla_token_get_row(const nesla_token_t *token)
{
    return token->row;
}

uint16_t nesla_token_get_scalar(const nesla_token_t *token)
{
    return token->scalar;
}

int nesla_token_get_subtype(const nesla_token_t *token)
{
    return token->subtype;
}

nesla_token_e nesla_token_get_type(const nesla_token_t *token)
{
    return token->type;
}

void nesla_token_set_scalar(nesla_token_t *token, uint16_t value)
{
    token->scalar = value;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
