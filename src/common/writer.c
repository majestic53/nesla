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
 * @file writer.c
 * @brief Common file writer.
 */

#include <common.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void nesla_writer_close(nesla_writer_t *writer)
{

    if(writer->offset) {
        fclose(writer->offset);
    }

    if(writer->base && (writer->base != writer->offset)) {
        fclose(writer->base);
    }

    memset(writer, 0, sizeof(*writer));
}

const char *nesla_writer_get_path(const nesla_writer_t *writer)
{
    return writer->path;
}

nesla_error_e nesla_writer_get_size(nesla_writer_t *writer, size_t *size)
{
    nesla_error_e result = NESLA_SUCCESS;

    if(fseek(writer->base, 0, SEEK_END)) {
        result = SET_ERROR("Failed to seek file end: %s", writer->path);
        goto exit;
    }

    *size = ftell(writer->base);

    if(fseek(writer->base, 0, SEEK_SET)) {
        result = SET_ERROR("Failed to seek file end: %s", writer->path);
        goto exit;
    }

exit:
    return result;
}

nesla_error_e nesla_writer_open(nesla_writer_t *writer, const char *path, bool create)
{
    nesla_error_e result = NESLA_SUCCESS;

    if(!(writer->base = fopen(path, create ? "wb" : "wbx"))
            || !(writer->offset = freopen(path, create ? "wb" : "wbx", writer->base))) {
        result = SET_ERROR("Failed to open file: %s", path);
        goto exit;
    }

    writer->path = path;

exit:
    return result;
}

nesla_error_e nesla_writer_put(nesla_writer_t *writer, const uint8_t *data, size_t length)
{
    nesla_error_e result = NESLA_SUCCESS;

    if(fwrite(data, sizeof(*data), length, writer->offset) != length) {
        result = SET_ERROR("Failed to write file: %s", writer->path);
        goto exit;
    }

exit:
    return result;
}

nesla_error_e nesla_writer_reset(nesla_writer_t *writer)
{
    nesla_error_e result = NESLA_SUCCESS;

    if(fseek(writer->base, 0, SEEK_SET)
            || fseek(writer->offset, 0, SEEK_SET)) {
        result = SET_ERROR("Failed to seek file set: %s", writer->path);
        goto exit;
    }

exit:
    return result;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
