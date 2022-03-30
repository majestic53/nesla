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
 * @file list.h
 * @brief Common linked list.
 */

#ifndef NESLA_LIST_H_
#define NESLA_LIST_H_

#include <error.h>

/*!
 * @struct nesla_list_entry_s
 * @brief List entry context.
 */
typedef struct nesla_list_entry_s {
    struct nesla_list_entry_s *next;        /*!< Next entry */
    struct nesla_list_entry_s *previous;    /*!< Previous entry */
    void *context;                          /*!< Entry context */
} nesla_list_entry_t;

/*!
 * @struct nesla_list_t
 * @brief List context.
 */
typedef struct {
    nesla_list_entry_t *head;               /*!< Head entry */
    nesla_list_entry_t *tail;               /*!< Tail entry */
    size_t size;                            /*!< Entries */
} nesla_list_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*!
 * @brief Get list entry context at index.
 * @param[in] list Pointer to list context
 * @param[in] index Entry index
 * @param[in,out] entry Pointer to list entry context, or NULL
 * @return NESLA_ERROR on failure, NESLA_SUCCESS otherwise
 */
nesla_error_e nesla_list_get(const nesla_list_t *list, size_t index, nesla_list_entry_t **entry);

/*!
 * @brief Get list entry context at head.
 * @param[in] list Pointer to list context
 * @return Pointer to list entry head context, or NULL
 */
nesla_list_entry_t *nesla_list_get_head(const nesla_list_t *list);

/*!
 * @brief Get list size.
 * @param[in] list Pointer to list context
 * @return List size
 */
size_t nesla_list_get_size(const nesla_list_t *list);

/*!
 * @brief Get list entry context at tail.
 * @param[in] list Pointer to list context
 * @return Pointer to list entry tail context, or NULL
 */
nesla_list_entry_t *nesla_list_get_tail(const nesla_list_t *list);

/*!
 * @brief Insert context into list context after list entry context.
 * @param[in,out] list Pointer to list context
 * @param[in,out] entry Pointer to list entry context to insert after, or NULL
 * @param[in] context Pointer to context
 * @return NESLA_ERROR on failure, NESLA_SUCCESS otherwise
 */
nesla_error_e nesla_list_insert(nesla_list_t *list, nesla_list_entry_t *entry, void *context);

/*!
 * @brief Remove list entry context from list context.
 * @param[in,out] list Pointer to list context
 * @param[in,out] entry Pointer to list entry context
 */
void nesla_list_remove(nesla_list_t *list, nesla_list_entry_t *entry);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* NESLA_LIST_H_ */
