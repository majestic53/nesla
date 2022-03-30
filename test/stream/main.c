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
 * @brief Stream tests.
 */

#include <stream.h>
#include <test.h>

#define TEST_DATA "abc\n012\n.,;\n   "
#define TEST_PATH "test.asm"

/*!
 * @struct nesla_test_t
 * @brief Test contexts.
 */
typedef struct {
    nesla_stream_t stream;          /*!< Stream context */

    struct {
        const char *data;           /*!< Reader data */
        const char *path;           /*!< Reader path */
        size_t index;               /*!< Reader index */
        bool open;                  /*!< Reader open */
        bool reset;                 /*!< Reader reset */
    } reader;
} nesla_test_t;

static nesla_test_t g_test = {};    /*!< Test context */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void nesla_reader_close(nesla_reader_t *reader)
{

    if(reader == &g_test.stream.reader) {
        memset(&g_test.reader, 0, sizeof(g_test.reader));
    }
}

nesla_error_e nesla_reader_get(nesla_reader_t *reader, uint8_t *data, size_t length)
{
    nesla_error_e result = NESLA_SUCCESS;

    if((reader != &g_test.stream.reader)
            || (length != 1)
            || (g_test.reader.index >= strlen(g_test.reader.data))) {
        result = NESLA_FAILURE;
        goto exit;
    }

    *data = g_test.reader.data[g_test.reader.index++];

exit:
    return result;
}

const char *nesla_reader_get_path(const nesla_reader_t *reader)
{

    if(reader != &g_test.stream.reader) {
        return NULL;
    }

    return g_test.reader.path;
}

nesla_error_e nesla_reader_get_size(nesla_reader_t *reader, size_t *size)
{
    nesla_error_e result = NESLA_SUCCESS;

    if(reader != &g_test.stream.reader) {
        result = NESLA_FAILURE;
        goto exit;
    }

    *size = strlen(g_test.reader.data);

exit:
    return result;
}

nesla_error_e nesla_reader_open(nesla_reader_t *reader, const char *path)
{
    nesla_error_e result = NESLA_SUCCESS;

    if((reader != &g_test.stream.reader)
            || (path == NULL)
            || (strlen(path) == 0)) {
        result = NESLA_FAILURE;
        goto exit;
    }

    g_test.reader.path = path;
    g_test.reader.open = true;

exit:
    return result;
}

nesla_error_e nesla_reader_reset(nesla_reader_t *reader)
{
    nesla_error_e result = NESLA_SUCCESS;

    if(reader != &g_test.stream.reader) {
        result = NESLA_FAILURE;
        goto exit;
    }

    g_test.reader.index = 0;
    g_test.reader.reset = true;

exit:
    return result;
}

nesla_error_e nesla_set_error(const char *file, const char *function, int line, const char *format, ...)
{
    return NESLA_FAILURE;
}

/*!
 * @brief Initialize test.
 * @return NESLA_FAILURE on failure, NESLA_SUCCESS otherwise
 */
static nesla_error_e nesla_test_initialize(const char *path, const char *data)
{
    nesla_error_e result;

    memset(&g_test, 0, sizeof(g_test));
    g_test.reader.data = data;

    if((result = nesla_stream_initialize(&g_test.stream, path)) == NESLA_FAILURE) {
        goto exit;
    }

exit:
    return result;
}

/*!
 * @brief Test character type.
 * @param character Character
 * @return Character type
 */
static nesla_character_e nesla_test_type(uint8_t character)
{
    nesla_character_e result = CHARACTER_SYMBOL;

    if(isalpha(character)) {
        result = CHARACTER_ALPHA;
    } else if(isdigit(character)) {
        result = CHARACTER_DIGIT;
    } else if(isspace(character)) {
        result = CHARACTER_WHITESPACE;
    }

    return result;
}

/*!
 * @brief Test stream get character.
 * @return NESLA_FAILURE on failure, NESLA_SUCCESS otherwise
 */
static nesla_error_e nesla_test_stream_get(void)
{
    nesla_error_e result = NESLA_SUCCESS;

    if(ASSERT(nesla_test_initialize(TEST_PATH, TEST_DATA) == NESLA_SUCCESS)) {
        result = NESLA_FAILURE;
        goto exit;
    }

    for(size_t index = 0; index < strlen(TEST_DATA); ++index) {

        if(ASSERT(nesla_stream_get(&g_test.stream) == TEST_DATA[index])) {
            result = NESLA_FAILURE;
            goto exit;
        }

        nesla_stream_next(&g_test.stream);
    }

exit:
    TEST_RESULT(result);

    return result;
}

/*!
 * @brief Test stream get line.
 * @return NESLA_FAILURE on failure, NESLA_SUCCESS otherwise
 */
static nesla_error_e nesla_test_stream_get_line(void)
{
    size_t line = 1;
    nesla_error_e result = NESLA_SUCCESS;

    if(ASSERT(nesla_test_initialize(TEST_PATH, TEST_DATA) == NESLA_SUCCESS)) {
        result = NESLA_FAILURE;
        goto exit;
    }

    for(size_t index = 0; index < strlen(TEST_DATA); ++index) {

        if(ASSERT(nesla_stream_get_line(&g_test.stream) == line)) {
            result = NESLA_FAILURE;
            goto exit;
        }

        nesla_stream_next(&g_test.stream);

       if(TEST_DATA[index] == '\n') {
            ++line;
        }
    }

exit:
    TEST_RESULT(result);

    return result;
}

/*!
 * @brief Test stream get path.
 * @return NESLA_FAILURE on failure, NESLA_SUCCESS otherwise
 */
static nesla_error_e nesla_test_stream_get_path(void)
{
    nesla_error_e result = NESLA_SUCCESS;

    if(ASSERT(nesla_test_initialize(TEST_PATH, TEST_DATA) == NESLA_SUCCESS)) {
        result = NESLA_FAILURE;
        goto exit;
    }

    if(ASSERT(strcmp(nesla_stream_get_path(&g_test.stream), TEST_PATH) == 0)) {
        result = NESLA_FAILURE;
        goto exit;
    }

exit:
    TEST_RESULT(result);

    return result;
}

/*!
 * @brief Test stream get character type.
 * @return NESLA_FAILURE on failure, NESLA_SUCCESS otherwise
 */
static nesla_error_e nesla_test_stream_get_type(void)
{
    nesla_error_e result = NESLA_SUCCESS;

    if(ASSERT(nesla_test_initialize(TEST_PATH, TEST_DATA) == NESLA_SUCCESS)) {
        result = NESLA_FAILURE;
        goto exit;
    }

    for(size_t index = 0; index < strlen(TEST_DATA); ++index) {

        if(ASSERT(nesla_stream_get_type(&g_test.stream) == nesla_test_type(TEST_DATA[index]))) {
            result = NESLA_FAILURE;
            goto exit;
        }

        nesla_stream_next(&g_test.stream);
    }

exit:
    TEST_RESULT(result);

    return result;
}

/*!
 * @brief Test stream initialization.
 * @return NESLA_FAILURE on failure, NESLA_SUCCESS otherwise
 */
static nesla_error_e nesla_test_stream_initialize(void)
{
    nesla_error_e result = NESLA_SUCCESS;

    if(ASSERT(nesla_test_initialize(TEST_PATH, "") == NESLA_FAILURE)) {
        result = NESLA_FAILURE;
        goto exit;
    }

    if(ASSERT(nesla_test_initialize(TEST_PATH, TEST_DATA) == NESLA_SUCCESS)) {
        result = NESLA_FAILURE;
        goto exit;
    }

    if(ASSERT((g_test.stream.character == TEST_DATA[0])
            && (g_test.stream.line == 1)
            && (strcmp(g_test.reader.data, TEST_DATA) == 0)
            && (strcmp(g_test.reader.path, TEST_PATH) == 0)
            && (g_test.reader.index == 1)
            && (g_test.reader.open == true)
            && (g_test.reader.reset == true))) {
        result = NESLA_FAILURE;
        goto exit;
    }

exit:
    TEST_RESULT(result);

    return result;
}

/*!
 * @brief Test stream next.
 * @return NESLA_FAILURE on failure, NESLA_SUCCESS otherwise
 */
static nesla_error_e nesla_test_stream_next(void)
{
    size_t index;
    nesla_error_e result = NESLA_SUCCESS;

    if(ASSERT(nesla_test_initialize(TEST_PATH, TEST_DATA) == NESLA_SUCCESS)) {
        result = NESLA_FAILURE;
        goto exit;
    }

    for(index = 0; index < strlen(TEST_DATA) - 1; ++index) {

        if(ASSERT(g_test.reader.index == index + 1)) {
            result = NESLA_FAILURE;
            goto exit;
        }

        if(ASSERT(nesla_stream_next(&g_test.stream) == NESLA_SUCCESS)) {
            result = NESLA_FAILURE;
            goto exit;
        }
    }

    if(ASSERT((g_test.reader.index == index + 1)
            && (nesla_stream_next(&g_test.stream) == NESLA_FAILURE))) {
        result = NESLA_FAILURE;
        goto exit;
    }

    if(ASSERT(nesla_stream_next(&g_test.stream) == NESLA_FAILURE)) {
        result = NESLA_FAILURE;
        goto exit;
    }

exit:
    TEST_RESULT(result);

    return result;
}

/*!
 * @brief Test stream reset.
 * @return NESLA_FAILURE on failure, NESLA_SUCCESS otherwise
 */
static nesla_error_e nesla_test_stream_reset(void)
{
    nesla_error_e result = NESLA_SUCCESS;

    if(ASSERT(nesla_test_initialize(TEST_PATH, TEST_DATA) == NESLA_SUCCESS)) {
        result = NESLA_FAILURE;
        goto exit;
    }

    for(size_t index = 0; index < strlen(TEST_DATA) - 1; ++index) {
        nesla_stream_next(&g_test.stream);
    }

    g_test.reader.reset = false;
    nesla_stream_reset(&g_test.stream);

    if(ASSERT((g_test.stream.character == TEST_DATA[0])
            && (g_test.stream.line == 1)
            && (strcmp(g_test.reader.data, TEST_DATA) == 0)
            && (strcmp(g_test.reader.path, TEST_PATH) == 0)
            && (g_test.reader.index == 1)
            && (g_test.reader.open == true)
            && (g_test.reader.reset == true))) {
        result = NESLA_FAILURE;
        goto exit;
    }

exit:
    TEST_RESULT(result);

    return result;
}

/*!
 * @brief Test stream uninitialization.
 * @return NESLA_FAILURE on failure, NESLA_SUCCESS otherwise
 */
static nesla_error_e nesla_test_stream_uninitialize(void)
{
    nesla_error_e result = NESLA_SUCCESS;

    if(ASSERT(nesla_test_initialize(TEST_PATH, TEST_DATA) == NESLA_SUCCESS)) {
        result = NESLA_FAILURE;
        goto exit;
    }

    nesla_stream_uninitialize(&g_test.stream);

    if(ASSERT((g_test.stream.character == '\0')
            && (g_test.stream.line == 0)
            && (g_test.reader.data == NULL)
            && (g_test.reader.path == NULL)
            && (g_test.reader.index == 0)
            && (g_test.reader.open == false)
            && (g_test.reader.reset == false))) {
        result = NESLA_FAILURE;
        goto exit;
    }

exit:
    TEST_RESULT(result);

    return result;
}

int main(void)
{
    static const test TEST[] = {
        nesla_test_stream_get,
        nesla_test_stream_get_line,
        nesla_test_stream_get_path,
        nesla_test_stream_get_type,
        nesla_test_stream_initialize,
        nesla_test_stream_next,
        nesla_test_stream_reset,
        nesla_test_stream_uninitialize,
        };

    nesla_error_e result = NESLA_SUCCESS;

    for(int index = 0; index < TEST_COUNT(TEST); ++index) {

        if(TEST[index]() == NESLA_FAILURE) {
            result = NESLA_FAILURE;
        }
    }

    return (int)result;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
