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
 * @file reader.c
 * @brief Common file reader.
 */

#include <common.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void nesla_reader_close(nesla_reader_t *reader)
{

    if(reader->offset) {
        fclose(reader->offset);
    }

    if(reader->base && (reader->base != reader->offset)) {
        fclose(reader->base);
    }

    memset(reader, 0, sizeof(*reader));
}

nesla_error_e nesla_reader_get(nesla_reader_t *reader, uint8_t *data, size_t length)
{
    nesla_error_e result = NESLA_SUCCESS;

    if(fread(data, sizeof(*data), length, reader->offset) != length) {
        result = SET_ERROR("Failed to read file: %s", reader->path);
        goto exit;
    }

exit:
    return result;
}

nesla_error_e nesla_reader_get_length(nesla_reader_t *reader, size_t *length)
{
    nesla_error_e result = NESLA_SUCCESS;

    if(fseek(reader->base, 0, SEEK_END)) {
        result = SET_ERROR("Failed to seek file end: %s", reader->path);
        goto exit;
    }

    *length = ftell(reader->base);

    if(fseek(reader->base, 0, SEEK_SET)) {
        result = SET_ERROR("Failed to seek file end: %s", reader->path);
        goto exit;
    }

exit:
    return result;
}

const char *nesla_reader_get_path(const nesla_reader_t *reader)
{
    return reader->path;
}

nesla_error_e nesla_reader_open(nesla_reader_t *reader, const char *path)
{
    nesla_error_e result = NESLA_SUCCESS;

    if(!(reader->base = fopen(path, "rb"))
            || !(reader->offset = freopen(path, "rb", reader->base))) {
        result = SET_ERROR("Failed to open file: %s", path);
        goto exit;
    }

    reader->path = path;

exit:
    return result;
}

nesla_error_e nesla_reader_reset(nesla_reader_t *reader)
{
    nesla_error_e result = NESLA_SUCCESS;

    if(fseek(reader->base, 0, SEEK_SET)
            || fseek(reader->offset, 0, SEEK_SET)) {
        result = SET_ERROR("Failed to seek file set: %s", reader->path);
        goto exit;
    }

exit:
    return result;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
