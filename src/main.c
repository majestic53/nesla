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
 * @file main.c
 * @brief NESLA launcher application.
 */

#include <getopt.h>
#include <libgen.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <nesla.h>

/*!
 * @enum nesla_option_e
 * @brief Interface option.
 */
typedef enum {
    OPTION_HELP,    /*!< Show help information */
    OPTION_OUTPUT,  /*!< Set output directory */
    OPTION_VERSION, /*!< Show version information */
    OPTION_MAX,     /*!< Maximum option */
} nesla_option_e;

/*!
 * @brief Color tracing macro.
 * @param[in] _RESULT_ Error code
 * @param[in] _FORMAT_ Error string format, followed by some number of arguments
 */
#define TRACE(_RESULT_, _FORMAT_, ...) \
    fprintf(((_RESULT_) != NESLA_SUCCESS) ? stderr : stdout, "%s" _FORMAT_ "\x1b[0m", \
        ((_RESULT_) != NESLA_SUCCESS) ? "\x1b[91m" : "\x1b[0m", __VA_ARGS__)

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*!
 * @brief Show version string in stream.
 * @param[in,out] stream File stream
 * @param[in] verbose Verbose output
 */
static void show_version(FILE *stream, bool verbose)
{
    const nesla_version_t *version = nesla_get_version();

    if(verbose) {
        TRACE(NESLA_SUCCESS, "%s", "NESLA ");
    }

    TRACE(NESLA_SUCCESS, "%i.%i.%i\n", version->major, version->minor, version->patch);

    if(verbose) {
        TRACE(NESLA_SUCCESS, "%s", "Copyright (C) 2022 David Jolly\n");
    }
}

/*!
 * @brief Show help string in stream.
 * @param[in,out] stream File stream
 * @param[in] verbose Verbose output
 */
static void show_help(FILE *stream, bool verbose)
{

    if(verbose) {
        show_version(stream, true);
        TRACE(NESLA_SUCCESS, "%s", "\n");
    }

    TRACE(NESLA_SUCCESS, "%s", "nesla [options] file\n");

    if(verbose) {
        static const char *OPTION[] = { "-h", "-o", "-v", },
            *DESCRIPTION[] = { "Show help information", "Set output directory", "Show version information", };

        TRACE(NESLA_SUCCESS, "%s", "\n");

        for(int flag = 0; flag < OPTION_MAX; ++flag) {

            TRACE(NESLA_SUCCESS, "%s\t%s\n", OPTION[flag], DESCRIPTION[flag]);
        }
    }
}

int main(int argc, char *argv[])
{
    int option;
    nesla_t context = {};
    nesla_error_e result = NESLA_SUCCESS;

    opterr = 1;

    while((option = getopt(argc, argv, "ho:v")) != -1) {

        switch(option) {
            case 'h':
                show_help(stdout, true);
                goto exit;
            case 'o':
                context.output = optarg;
                break;
            case 'v':
                show_version(stdout, false);
                goto exit;
            case '?':
            default:
                result = NESLA_FAILURE;
                goto exit;
        }
    }

    for(option = optind; option < argc; ++option) {
        context.input = argv[option];
        break;
    }

    if(!context.input) {
        TRACE(NESLA_FAILURE, "%s: Undefined input path\n", argv[0]);
        goto exit;
    }

    if((result = nesla(&context)) == NESLA_FAILURE) {
        TRACE(NESLA_FAILURE, "%s: %s\n", argv[0], nesla_get_error());
        goto exit;
    }

exit:

    return (int)result;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
