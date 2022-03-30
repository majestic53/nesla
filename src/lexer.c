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
 * @file lexer.c
 * @brief Token lexer.
 */

#include <lexer.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static nesla_error_e nesla_lexer_parse(nesla_lexer_t *lexer)
{
    nesla_error_e result = NESLA_SUCCESS;

    do {

        /* TODO: DEBUGGING */
        /* TODO: ADD STATIC FUNCTION TO ALLOCATE/FREE TOKENS */
        /* TODO: PARSE COMMENT */
        /* TODO: PARSE TOKEN */
        const char *TYPE_STR[] = { "ALPHA", "DIGIT", "SYMBOL", "SPACE", "???" };
        uint8_t value = nesla_stream_get(&lexer->stream);
        nesla_character_e type = nesla_stream_get_type(&lexer->stream);

        fprintf(stdout, "[%s] \'%c\' (%02X) (%s@%zu)\n",
            TYPE_STR[type], isprint(value) && !isspace(value) ? (char)value : ' ', value,
            nesla_stream_get_path(&lexer->stream), nesla_stream_get_line(&lexer->stream));

        nesla_literal_t lit = {};
        nesla_token_t *tok = NULL;

        if((result = nesla_literal_allocate(&lit)) == NESLA_FAILURE) {
            goto exit;
        }

        if((result = nesla_literal_append(&lit, value)) == NESLA_FAILURE) {
            goto exit;
        }

        if(!(tok = calloc(1, sizeof(*tok)))) {
            result = SET_ERROR("Failed to allocate token: %p", tok);
            goto exit;
        }

        nesla_token_set(tok, TOKEN_LITERAL, 0, nesla_stream_get_path(&lexer->stream), nesla_stream_get_line(&lexer->stream));

        if((result = nesla_token_set_literal(tok, &lit)) == NESLA_FAILURE) {
            goto exit;
        }

        nesla_literal_free(&lit);
        value = tok->literal.buffer[0];

        fprintf(stdout, "LIST[%zu] -> [%i;%i] \'%c\' (%02X) (%s@%zu)\n\n", nesla_list_get_size(&lexer->token),
            tok->type, tok->subtype, isprint(value) && !isspace(value) ? (char)value : ' ', value,
            tok->path, tok->line);

        if((result = nesla_list_insert(&lexer->token, nesla_list_get_tail(&lexer->token), tok)) == NESLA_FAILURE) {
            goto exit;
        }
        /* --- */

    } while(nesla_stream_next(&lexer->stream) == NESLA_SUCCESS);

    nesla_lexer_reset(lexer);

exit:
    return result;
}

nesla_error_e nesla_lexer_get(const nesla_lexer_t *lexer, const nesla_token_t **token)
{
    nesla_error_e result;
    nesla_list_entry_t *entry;

    if((result = nesla_list_get(&lexer->token, lexer->index, &entry)) == NESLA_FAILURE) {
        goto exit;
    }

    *token = entry->context;

exit:
    return result;
}

nesla_error_e nesla_lexer_initialize(nesla_lexer_t *lexer, const char *path)
{
    nesla_error_e result;

    if((result = nesla_stream_initialize(&lexer->stream, path)) == NESLA_FAILURE) {
        goto exit;
    }

    if((result = nesla_lexer_parse(lexer)) == NESLA_FAILURE) {
        goto exit;
    }

exit:
    return result;
}

nesla_error_e nesla_lexer_next(nesla_lexer_t *lexer)
{
    nesla_error_e result = NESLA_SUCCESS;

    if(lexer->index + 1 >= nesla_list_get_size(&lexer->token)) {
        result = SET_ERROR("No next token: %zu", lexer->index);
        goto exit;
    }

    ++lexer->index;

exit:
    return result;
}

nesla_error_e nesla_lexer_reset(nesla_lexer_t *lexer)
{
    nesla_error_e result;

    if((result = nesla_stream_reset(&lexer->stream)) == NESLA_FAILURE) {
        goto exit;
    }

    lexer->index = 0;

exit:
    return result;
}

void nesla_lexer_uninitialize(nesla_lexer_t *lexer)
{

    while(nesla_list_get_size(&lexer->token)) {
        nesla_list_entry_t *entry = nesla_list_get_head(&lexer->token);

        if(entry->context) {
            nesla_token_free(entry->context);
            free(entry->context);
        }

        nesla_list_remove(&lexer->token, entry);
    }

    nesla_stream_uninitialize(&lexer->stream);
    memset(lexer, 0, sizeof(*lexer));
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
