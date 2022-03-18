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
 * @file file.c
 * @brief Read/write files.
 */

#include <common.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void nesla_file_close(nesla_file_t *file)
{
    /* TODO */
}

size_t nesla_file_get_size(const nesla_file_t *file)
{
    size_t result;

    /* TODO */
    result = 0;
    /* --- */

    return result;
}

nesla_error_e nesla_file_open(nesla_file_t *file, const char *path, bool create)
{
    nesla_error_e result;

    /* TODO */
    result = NESLA_SUCCESS;
    /* --- */

    return result;
}

nesla_error_e nesla_file_read(nesla_file_t *file, uint8_t *data, size_t *length)
{
    nesla_error_e result;

    /* TODO */
    result = NESLA_SUCCESS;
    /* --- */

    return result;
}

nesla_error_e nesla_file_seek(nesla_file_t *file, size_t offset, bool relative)
{
    nesla_error_e result;

    /* TODO */
    result = NESLA_SUCCESS;
    /* --- */

    return result;
}

nesla_error_e nesla_file_write(nesla_file_t *file, const uint8_t *data, size_t *length)
{
    nesla_error_e result;

    /* TODO */
    result = NESLA_SUCCESS;
    /* --- */

    return result;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
