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
 * @file list.c
 * @brief Common linked list.
 */

#include <common.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

nesla_error_e nesla_list_clear(nesla_list_t *list)
{
    nesla_error_e result = NESLA_SUCCESS;

    while(list->size) {

        if((result = nesla_list_remove(list, list->tail)) == NESLA_FAILURE) {
            goto exit;
        }
    }

    memset(list, 0, sizeof(*list));

exit:
    return result;
}

nesla_error_e nesla_list_get(const nesla_list_t *list, size_t index, nesla_list_entry_t **entry)
{
    nesla_error_e result = NESLA_SUCCESS;

    if(index >= list->size) {
        result = SET_ERROR("Invalid index: %zu", index);
        goto exit;
    }

    *entry = list->head;

    for(size_t offset = 0; offset < index; ++offset) {
        *entry = (*entry)->next;
    }

exit:
    return result;
}

nesla_list_entry_t *nesla_list_get_head(const nesla_list_t *list)
{
    return list->head;
}

size_t nesla_list_get_size(const nesla_list_t *list)
{
    return list->size;
}

nesla_list_entry_t *nesla_list_get_tail(const nesla_list_t *list)
{
    return list->tail;
}

nesla_error_e nesla_list_insert(nesla_list_t *list, nesla_list_entry_t *entry, const void *context)
{
    nesla_list_entry_t *new_entry;
    nesla_error_e result = NESLA_SUCCESS;

    if(!(new_entry = calloc(1, sizeof(*new_entry)))) {
        result = SET_ERROR("Failed to allocate list entry: %p", new_entry);
        goto exit;
    }

    new_entry->context = context;

    if(!entry) {

        if(list->head) {
            new_entry->next = list->head;
            list->head->previous = new_entry;
        }

        list->head = new_entry;

        if(!list->tail) {
            list->tail = list->head;
        }
    } else if(entry == list->tail) {
        new_entry->previous = entry;
        entry->next = new_entry;
        list->tail = new_entry;

        if(!list->head) {
            list->head = list->tail;
        }
    } else {
        new_entry->next = entry->next;
        new_entry->previous = entry;
        entry->next->previous = new_entry;
        entry->next = new_entry;
    }

    ++list->size;

exit:

    if((result == NESLA_FAILURE) && new_entry) {
        free(new_entry);
    }

    return result;
}

nesla_error_e nesla_list_remove(nesla_list_t *list, nesla_list_entry_t *entry)
{
    nesla_error_e result = NESLA_SUCCESS;

    if(!list->size) {
        result = SET_ERROR("Empty list: %zu", list->size);
        goto exit;
    }

    if(entry == list->head) {

        if((list->head = entry->next)) {
            entry->next->previous = NULL;
        } else {
            list->tail = NULL;
        }
    } else if(entry == list->tail) {

        if((list->tail = entry->previous)) {
            entry->previous->next = NULL;
        } else {
            list->head = NULL;
        }
    } else {
        entry->previous->next = entry->next;
        entry->next->previous = entry->previous;
    }

    free(entry);
    --list->size;

exit:
    return result;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
