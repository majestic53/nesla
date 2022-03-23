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
 * @file nesla.h
 * @brief NESLA stream.
 */

#include <stream.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

uint8_t nesla_stream_get(const nesla_stream_t *stream)
{
    return stream->character;
}

size_t nesla_stream_get_column(const nesla_stream_t *stream)
{
    return stream->column;
}

const char *nesla_stream_get_path(const nesla_stream_t *stream)
{
    return nesla_reader_get_path(&stream->reader);
}

size_t nesla_stream_get_row(const nesla_stream_t *stream)
{
    return stream->row;
}

nesla_character_e nesla_stream_get_type(const nesla_stream_t *stream)
{
    nesla_character_e result = CHARACTER_SYMBOL;

    if(stream->character == '\0') {
        result = CHARACTER_END;
    } else if(isalpha(stream->character)) {
        result = CHARACTER_ALPHA;
    } else if(isdigit(stream->character)) {
        result = CHARACTER_DIGIT;
    } else if(isspace(stream->character)) {
        result = CHARACTER_WHITESPACE;
    }

    return result;
}

nesla_error_e nesla_stream_initialize(nesla_stream_t *stream, const char *path)
{
    size_t size = 0;
    nesla_error_e result;

    if((result = nesla_reader_open(&stream->reader, path)) == NESLA_FAILURE) {
        goto exit;
    }

    if((result = nesla_reader_get_size(&stream->reader, &size)) == NESLA_FAILURE) {
        goto exit;
    }

    if(!size) {
        result = SET_ERROR("Empty file: %s", path);
        goto exit;
    }

    result = nesla_stream_reset(stream);

exit:
    return result;
}

nesla_error_e nesla_stream_next(nesla_stream_t *stream)
{

    if(nesla_stream_get_type(stream) != CHARACTER_END) {

        if(stream->character == '\n') {
            stream->column = 0;
            ++stream->row;
        } else {
            ++stream->column;
        }
    } else {
        stream->column = 0;
        stream->row = 0;
    }

    return nesla_reader_get(&stream->reader, &stream->character);
}

nesla_error_e nesla_stream_reset(nesla_stream_t *stream)
{
    nesla_error_e result;

    if((result = nesla_reader_reset(&stream->reader)) == NESLA_FAILURE) {
        goto exit;
    }

    stream->character = '\0';
    result = nesla_stream_next(stream);

exit:
    return result;
}

void nesla_stream_uninitialize(nesla_stream_t *stream)
{
    nesla_reader_close(&stream->reader);
    memset(stream, 0, sizeof(*stream));
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
