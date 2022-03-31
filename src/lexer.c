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

/* TODO: DEBUGGING */
/* TODO: ADD DOXYGEN COMMENTS TO STATICS */
#if 0
static nesla_error_e nesla_lexer_allocate(nesla_lexer_t *lexer, nesla_token_e type, int subtype, const char *path, size_t line)
{
    nesla_token_t *token = NULL;
    nesla_error_e result = NESLA_SUCCESS;

    if(!(token = calloc(1, sizeof(*token)))) {
        result = SET_ERROR("Failed to allocate token: %p", token);
        goto exit;
    }

    nesla_token_set(token, type, subtype, path, line);

    if((result = nesla_list_insert(&lexer->token, nesla_list_get_tail(&lexer->token), token)) == NESLA_FAILURE) {
        goto exit;
    }

exit:
    return result;
}

static nesla_error_e nesla_lexer_allocate_literal(nesla_lexer_t *lexer, const nesla_literal_t *literal, nesla_token_e type, const char *path, size_t line)
{
    nesla_error_e result;

    if((result = nesla_lexer_allocate(lexer, TOKEN_LITERAL, 0, path, line)) == NESLA_FAILURE) {
        goto exit;
    }

    if((result = nesla_token_set_literal(nesla_list_get_tail(&lexer->token)->context, literal)) == NESLA_FAILURE) {
        goto exit;
    }

exit:
    return result;
}

static nesla_error_e nesla_lexer_allocate_scalar(nesla_lexer_t *lexer, uint16_t scalar, const char *path, size_t line)
{
    nesla_error_e result;

    if((result = nesla_lexer_allocate(lexer, TOKEN_LITERAL, 0, path, line)) == NESLA_FAILURE) {
        goto exit;
    }

    nesla_token_set_scalar(nesla_list_get_tail(&lexer->token)->context, scalar);

exit:
    return result;
}
#endif
/* --- */

static void nesla_lexer_free(nesla_lexer_t *lexer, nesla_list_entry_t *entry)
{
    nesla_token_free(entry->context);
    free(entry->context);
    nesla_list_remove(&lexer->token, entry);
    memset(entry, 0, sizeof(*entry));
}

static void nesla_lexer_free_all(nesla_lexer_t *lexer)
{

    while(nesla_list_get_length(&lexer->token)) {
        nesla_lexer_free(lexer, nesla_list_get_head(&lexer->token));
    }
}

static nesla_error_e nesla_lexer_parse_alpha(nesla_lexer_t *lexer, nesla_character_e type, uint8_t value)
{
    nesla_error_e result;

    /* TODO: PARSE ALPHA */
    result = NESLA_SUCCESS;
    /* --- */

    return result;
}

static nesla_error_e nesla_lexer_parse_digit(nesla_lexer_t *lexer, nesla_character_e type, uint8_t value)
{
    nesla_error_e result;

    /* TODO: PARSE DIGIT */
    result = NESLA_SUCCESS;
    /* --- */

    return result;
}

static nesla_error_e nesla_lexer_parse_symbol(nesla_lexer_t *lexer, nesla_character_e type, uint8_t value)
{
    nesla_error_e result;

    /* TODO: PARSE SYMBOL */
    result = NESLA_SUCCESS;
    /* --- */

    return result;
}

static nesla_error_e nesla_lexer_parse(nesla_lexer_t *lexer)
{
    nesla_error_e result;

    do {
        nesla_character_e type;
        uint8_t value = nesla_stream_get(&lexer->stream);

        switch(type = nesla_stream_get_type(&lexer->stream)) {
            case CHARACTER_ALPHA:

                if((result = nesla_lexer_parse_alpha(lexer, type, value)) == NESLA_FAILURE) {
                    goto exit;
                }
                break;
            case CHARACTER_DIGIT:

                if((result = nesla_lexer_parse_digit(lexer, type, value)) == NESLA_FAILURE) {
                    goto exit;
                }
                break;
            case CHARACTER_SYMBOL:

                if((result = nesla_lexer_parse_symbol(lexer, type, value)) == NESLA_FAILURE) {
                    goto exit;
                }
                break;
            default:
                result = SET_ERROR("Invalid character: [%i] \'%c\' (%02X) (%s@%i)", type, isprint(value) && !isspace(value) ? value : '.',
                    value, nesla_stream_get_path(&lexer->stream), nesla_stream_get_line(&lexer->stream));
                goto exit;
        }
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

    if(lexer->index + 1 >= nesla_list_get_length(&lexer->token)) {
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
    nesla_lexer_free_all(lexer);
    nesla_stream_uninitialize(&lexer->stream);
    memset(lexer, 0, sizeof(*lexer));
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
