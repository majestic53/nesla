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
 * @file nesla.c
 * @brief Public interface.
 */

#include <common.h>

/* TODO: DEBUGGING */
#include <lexer.h>
/* --- */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

nesla_error_e nesla(const nesla_t *context)
{
    nesla_error_e result = NESLA_SUCCESS;

    /* TODO: DEBUGGING */
    nesla_lexer_t lexer = {};

    if((result = nesla_lexer_initialize(&lexer, context->input)) == NESLA_FAILURE) {
        goto exit;
    }

    do {
        nesla_token_t *token;

        if((result = nesla_lexer_get(&lexer, &token)) == NESLA_FAILURE) {
            goto exit;
        }

        switch(token->type) {
            case TOKEN_END:
                fprintf(stdout, "[%i:%i] END\n", nesla_token_get_type(token), nesla_token_get_subtype(token));
                break;
            case TOKEN_IDENTIFIER:
            case TOKEN_LABEL:
            case TOKEN_LITERAL:
                fprintf(stdout, "[%i:%i] \"%s\" (%s@%zu)\n", nesla_token_get_type(token), nesla_token_get_subtype(token),
                    nesla_literal_get(nesla_token_get_literal(token)), nesla_token_get_path(token), nesla_token_get_line(token));
                break;
            case TOKEN_SCALAR:
                fprintf(stdout, "[%i:%i] %04X (%u) (%s@%zu)\n", nesla_token_get_type(token), nesla_token_get_subtype(token),
                    nesla_token_get_scalar(token), nesla_token_get_scalar(token), nesla_token_get_path(token), nesla_token_get_line(token));
                break;
            default:
                fprintf(stdout, "[%i:%i] (%s@%zu)\n", nesla_token_get_type(token), nesla_token_get_subtype(token),
                    nesla_token_get_path(token), nesla_token_get_line(token));
                break;
        }
    } while(nesla_lexer_next(&lexer) == NESLA_SUCCESS);

exit:
    nesla_lexer_uninitialize(&lexer);
    /* --- */

    return result;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
