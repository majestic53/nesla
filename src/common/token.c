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

void nesla_token_free(nesla_token_t *token)
{
    nesla_literal_free(&token->literal);
    memset(token, 0, sizeof(*token));
}

size_t nesla_token_get_line(const nesla_token_t *token)
{
    return token->line;
}

const uint8_t *nesla_token_get_literal(const nesla_token_t *token)
{
    return nesla_literal_get(&token->literal);
}

size_t nesla_token_get_literal_length(const nesla_token_t *token)
{
    return nesla_literal_get_length(&token->literal);
}

const char *nesla_token_get_path(const nesla_token_t *token)
{
    return token->path;
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

void nesla_token_set(nesla_token_t *token, nesla_token_e type, int subtype, const char *path, size_t line)
{
    token->type = type;
    token->subtype = subtype;
    token->path = path;
    token->line = line;
}

nesla_error_e nesla_token_set_literal(nesla_token_t *token, const nesla_literal_t *literal)
{
    nesla_error_e result;

    if((result = nesla_literal_allocate(&token->literal)) == NESLA_FAILURE) {
        goto exit;
    }

    if((result = nesla_literal_copy(&token->literal, literal)) == NESLA_FAILURE) {
        goto exit;
    }

exit:
    return result;
}

void nesla_token_set_scalar(nesla_token_t *token, uint16_t scalar)
{
    token->scalar = scalar;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
