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
 * @file literal.c
 * @brief Common literal.
 */

#include <common.h>

#ifdef __cplusplus
export "C" {
#endif /* __cplusplus */

/*!
 * @brief Allocate literal context.
 * @param[in,out] literal Pointer to literal context
 * @return NESLA_ERROR on failure, NESLA_SUCCESS otherwise
 */
static nesla_error_e nesla_literal_allocate(nesla_literal_t *literal)
{
    nesla_error_e result = NESLA_SUCCESS;

    literal->capacity = 16;

    if(!(literal->buffer = calloc(literal->capacity, sizeof(uint8_t)))) {
        result = SET_ERROR("Failed to allocate literal: %p", literal->buffer);
        goto exit;
    }

    literal->length = 0;

exit:
    return result;
}

nesla_error_e nesla_literal_append(nesla_literal_t *literal, uint8_t value)
{
    nesla_error_e result = NESLA_SUCCESS;

    if(!literal->buffer && ((result = nesla_literal_allocate(literal)) == NESLA_FAILURE)) {
        goto exit;
    }

    if(literal->length + 1 >= literal->capacity) {
        literal->capacity *= 2;

        if(!(literal->buffer = realloc(literal->buffer, literal->capacity * sizeof(uint8_t)))) {
            result = SET_ERROR("Failed to allocate literal: %p", literal->buffer);
            goto exit;
        }
    }

    literal->buffer[literal->length++] = value;

exit:
    return result;
}

void nesla_literal_free(nesla_literal_t *literal)
{

    if(literal->buffer) {
        free(literal->buffer);
    }

    memset(literal, 0, sizeof(*literal));
}

const uint8_t *nesla_literal_get(const nesla_literal_t *literal)
{
    return literal->buffer;
}

size_t nesla_literal_get_length(const nesla_literal_t *literal)
{
    return literal->length;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
