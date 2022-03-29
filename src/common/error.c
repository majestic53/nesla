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
 * @file error.c
 * @brief Common error.
 */

#include <common.h>

/*!
 * @struct nesla_error_t
 * @brief Error context.
 */
typedef struct {
    char buffer[256];               /*!< Error string */
} nesla_error_t;

static nesla_error_t g_error = {};  /*!< Error context */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

const char *nesla_get_error(void)
{
    return g_error.buffer;
}

nesla_error_e nesla_set_error(const char *file, const char *function, int line, const char *format, ...)
{
    va_list arguments;

    va_start(arguments, format);
    vsnprintf(g_error.buffer, sizeof(g_error.buffer), format, arguments);
    snprintf(g_error.buffer + strlen(g_error.buffer), sizeof(g_error.buffer) - strlen(g_error.buffer), " (%s:%s@%i)", function, file, line);
    va_end(arguments);

    return NESLA_FAILURE;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
