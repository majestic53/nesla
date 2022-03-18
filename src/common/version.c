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
 * @file version.c
 * @brief Global version.
 */

#include <common.h>

#define VERSION_MAJOR 0     /*!< Major version */
#define VERSION_MINOR 1     /*!< Minor version */
#define VERSION_PATCH 1     /*!< Patch version */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

const nesla_version_t *nesla_get_version(void)
{
    static const nesla_version_t g_version = { .major = VERSION_MAJOR, .minor = VERSION_MINOR, .patch = VERSION_PATCH, };

    return &g_version;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
