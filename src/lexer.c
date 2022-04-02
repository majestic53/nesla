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
 * @file lexer.c
 * @brief Token lexer.
 */

#include <lexer.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*!
 * @brief Allocate lexer token.
 * @param[in,out] lexer Pointer to lexer context
 * @param[in] type Token type
 * @param[in] subtype Token subtype
 * @param[in] path Token file path
 * @param[in] line Token flle line
 * @return NESLA_ERROR on failure, NESLA_SUCCESS otherwise
 */
static nesla_error_e nesla_lexer_append(nesla_lexer_t *lexer, nesla_token_e type, int subtype, const char *path, size_t line)
{
    nesla_token_t *token = NULL;
    nesla_error_e result = NESLA_SUCCESS;

    if(!(token = calloc(1, sizeof(*token)))) {
        result = SET_ERROR("Failed to allocate token: %p", token);
        goto exit;
    }

    nesla_token_set(token, type, subtype, path, line);

    if((result = nesla_list_insert(&lexer->token, nesla_list_get_tail(&lexer->token), token)) == NESLA_FAILURE) {
        goto exit;
    }

exit:
    return result;
}

/*!
 * @brief Allocate lexer literal token.
 * @param[in,out] lexer Pointer to lexer context
 * @param[in] literal Constant pointer to literal context
 * @param[in] type Token type
 * @param[in] path Token file path
 * @param[in] line Token flle line
 * @return NESLA_ERROR on failure, NESLA_SUCCESS otherwise
 */
static nesla_error_e nesla_lexer_append_literal(nesla_lexer_t *lexer, const nesla_literal_t *literal, nesla_token_e type, const char *path, size_t line)
{
    nesla_error_e result;

    if((result = nesla_lexer_append(lexer, type, 0, path, line)) == NESLA_FAILURE) {
        goto exit;
    }

    if((result = nesla_token_set_literal(nesla_list_get_tail(&lexer->token)->context, literal)) == NESLA_FAILURE) {
        goto exit;
    }

exit:
    return result;
}

#if 0 /* TODO: IMPLEMENT LEXER PARSE ROUTINES */

/*!
 * @brief Allocate lexer scalar token.
 * @param[in,out] lexer Pointer to lexer context
 * @param[in] scalar Scalar value
 * @param[in] path Token file path
 * @param[in] line Token flle line
 * @return NESLA_ERROR on failure, NESLA_SUCCESS otherwise
 */
static nesla_error_e nesla_lexer_append_scalar(nesla_lexer_t *lexer, uint16_t scalar, const char *path, size_t line)
{
    nesla_error_e result;

    if((result = nesla_lexer_append(lexer, TOKEN_SCALAR, 0, path, line)) == NESLA_FAILURE) {
        goto exit;
    }

    nesla_token_set_scalar(nesla_list_get_tail(&lexer->token)->context, scalar);

exit:
    return result;
}

#endif /* 0 */

/*!
 * @brief Free lexer token.
 * @param[in,out] lexer Pointer to lexer context
 * @param[in] entry Pointer to list entry context
 */
static void nesla_lexer_free(nesla_lexer_t *lexer, nesla_list_entry_t *entry)
{
    nesla_token_free(entry->context);
    free(entry->context);
    nesla_list_remove(&lexer->token, entry);
}

/*!
 * @brief Free all lexer tokens.
 * @param[in,out] lexer Pointer to lexer context
 */
static void nesla_lexer_free_all(nesla_lexer_t *lexer)
{

    while(nesla_list_get_length(&lexer->token)) {
        nesla_lexer_free(lexer, nesla_list_get_head(&lexer->token));
    }
}

/*!
 * @brief Match lexer token subtype.
 * @param[in] type Token type
 * @param[in,out] subtype Token subtype
 * @param[in] literal Token literal
 * @return true if match is found, false otherwise
 */
static bool nesla_lexer_match_type(nesla_token_e type, int *subtype, const nesla_literal_t *literal)
{
    static const char *DIRECTIVE[] = {
        ".BANK", ".BYTE", ".CHR", ".DEF", ".INC", ".INCB", ".MAP", ".MIR", ".ORG", ".PRG", ".RESV", ".UNDEF", ".WORD",
        };

    static const char *INSTRUCTION[] = {
        "ADC", "AND", "ASL", "BCC", "BCS", "BEQ", "BIT", "BMI", "BNE", "BPL", "BRK", "BVC", "BVS", "CLC", "CLD", "CLI",
        "CLV", "CMP", "CPX", "CPY", "DEC", "DEX", "DEY", "EOR", "INC", "INX", "INY", "JMP", "JSR", "LDA", "LDX", "LDY",
        "LSR", "NOP", "ORA", "PHA", "PHP", "PLA", "PLP", "ROL", "ROR", "RTI", "RTS", "SBC", "SEC", "SED", "SEI", "STA",
        "STX", "STY", "TAX", "TAY", "TSX", "TXA", "TXS", "TYA",
        };

    static const char *OPERAND[] = {
        "A", "X", "Y",
        };

    static const char *SYMBOL[] = {
        ",", "#", ")", "(",
        };

    size_t length = 0;
    bool result = false;
    const char **subtypes = NULL;

    switch(type) {
        case TOKEN_DIRECTIVE:
            subtypes = DIRECTIVE;
            length = DIRECTIVE_MAX;
            break;
        case TOKEN_INSTRUCTION:
            subtypes = INSTRUCTION;
            length = INSTRUCTION_MAX;
            break;
        case TOKEN_OPERAND:
            subtypes = OPERAND;
            length = OPERAND_MAX;
            break;
        case TOKEN_SYMBOL:
            subtypes = SYMBOL;
            length = SYMBOL_MAX;
            break;
        default:
            break;
    }

    *subtype = 0;

    if(subtypes) {

        for(; *subtype < length; ++*subtype) {

            if((result = (strcmp(subtypes[*subtype], (const char *)nesla_literal_get(literal)) == 0))) {
                break;
            }
        }

        if(*subtype == length) {
            *subtype = 0;
        }
    }

    return result;
}

/*!
 * @brief Parse lexer alpha token.
 * @param[in,out] lexer Pointer to lexer context
 * @param[in] value Current character value
 * @param[in] path Token file path
 * @param[in] line Token flle line
 * @return NESLA_ERROR on failure, NESLA_SUCCESS otherwise
 */
static nesla_error_e nesla_lexer_parse_alpha(nesla_lexer_t *lexer, uint8_t value, const char *path, size_t line)
{
    int subtype = 0;
    nesla_token_e type;
    nesla_error_e result;
    nesla_literal_t literal = {};

    if((result = nesla_literal_append(&literal, value)) == NESLA_FAILURE) {
        goto exit;
    }

    while(nesla_stream_next(&lexer->stream) == NESLA_SUCCESS) {
        nesla_character_e char_type = nesla_stream_get_type(&lexer->stream);

        value = nesla_stream_get(&lexer->stream);

        if((value != '_')
                && (char_type != CHARACTER_ALPHA)
                && (char_type != CHARACTER_DIGIT)) {
            break;
        }

        if((result = nesla_literal_append(&literal, value)) == NESLA_FAILURE) {
            goto exit;
        }
    }

    if(nesla_stream_get(&lexer->stream) == ':') {
        type = TOKEN_LABEL;
    } else if(nesla_lexer_match_type(TOKEN_INSTRUCTION, &subtype, &literal)) {
        type = TOKEN_INSTRUCTION;
    } else if(nesla_lexer_match_type(TOKEN_OPERAND, &subtype, &literal)) {
        type = TOKEN_OPERAND;
    } else {
        type = TOKEN_IDENTIFIER;
    }

    switch(type) {
        case TOKEN_INSTRUCTION:
        case TOKEN_OPERAND:

            if((result = nesla_lexer_append(lexer, type, subtype, path, line)) == NESLA_FAILURE) {
                goto exit;
            }
            break;
        case TOKEN_IDENTIFIER:
        case TOKEN_LABEL:

            if((result = nesla_lexer_append_literal(lexer, &literal, type, path, line)) == NESLA_FAILURE) {
                goto exit;
            }
            break;
        default:
            break;
    }

exit:
    nesla_literal_free(&literal);

    return result;
}

/*!
 * @brief Parse lexer digit token.
 * @param[in,out] lexer Pointer to lexer context
 * @param[in] value Current character value
 * @param[in] path Token file path
 * @param[in] line Token flle line
 * @return NESLA_ERROR on failure, NESLA_SUCCESS otherwise
 */
static nesla_error_e nesla_lexer_parse_digit(nesla_lexer_t *lexer, uint8_t value, const char *path, size_t line)
{
    nesla_error_e result;

    /* TODO: PARSE DIGIT */
    result = NESLA_SUCCESS;
    /* --- */

    return result;
}

/*!
 * @brief Parse lexer symbol token.
 * @param[in,out] lexer Pointer to lexer context
 * @param[in] value Current character value
 * @param[in] path Token file path
 * @param[in] line Token flle line
 * @return NESLA_ERROR on failure, NESLA_SUCCESS otherwise
 */
static nesla_error_e nesla_lexer_parse_symbol(nesla_lexer_t *lexer, uint8_t value, const char *path, size_t line)
{
    int subtype = 0;
    nesla_literal_t literal = {};
    nesla_error_e result = NESLA_SUCCESS;

    if(value == ';') {

        while(nesla_stream_next(&lexer->stream) == NESLA_SUCCESS) {

            if(nesla_stream_get(&lexer->stream) == '\n') {
                break;
            }
        }
    } else if(value == '.') {

        if((result = nesla_literal_append(&literal, value)) == NESLA_FAILURE) {
            goto exit;
        }

        while(nesla_stream_next(&lexer->stream) == NESLA_SUCCESS) {

            if(nesla_stream_get_type(&lexer->stream) != CHARACTER_ALPHA) {
                break;
            }

            if((result = nesla_literal_append(&literal, nesla_stream_get(&lexer->stream))) == NESLA_FAILURE) {
                goto exit;
            }
        }

        if(!nesla_lexer_match_type(TOKEN_DIRECTIVE, &subtype, &literal)) {
            result = SET_ERROR("Unsupported directive: \"%s\" (%s@%zu)", nesla_literal_get(&literal), path, line);
            goto exit;
        }

        if((result = nesla_lexer_append(lexer, TOKEN_DIRECTIVE, subtype, path, line)) == NESLA_FAILURE) {
            goto exit;
        }
    } else if(value == '_') {

        if((result = nesla_lexer_parse_alpha(lexer, value, path, line)) == NESLA_FAILURE) {
            goto exit;
        }
    } else {

        if((result = nesla_literal_append(&literal, value)) == NESLA_FAILURE) {
            goto exit;
        }

        if(!nesla_lexer_match_type(TOKEN_SYMBOL, &subtype, &literal)) {
            result = SET_ERROR("Unsupported symbol: \"%s\" (%s@%zu)", nesla_literal_get(&literal), path, line);
            goto exit;
        }

        if((result = nesla_lexer_append(lexer, TOKEN_SYMBOL, subtype, path, line)) == NESLA_FAILURE) {
            goto exit;
        }
    }

exit:
    nesla_literal_free(&literal);

    return result;
}

/*!
 * @brief Parse lexer token.
 * @param[in,out] lexer Pointer to lexer context
 * @return NESLA_ERROR on failure, NESLA_SUCCESS otherwise
 */
static nesla_error_e nesla_lexer_parse(nesla_lexer_t *lexer)
{
    nesla_error_e result;

    do {
        nesla_character_e type;
        uint8_t value = nesla_stream_get(&lexer->stream);
        size_t line = nesla_stream_get_line(&lexer->stream);
        const char *path = nesla_stream_get_path(&lexer->stream);

        switch(type = nesla_stream_get_type(&lexer->stream)) {
            case CHARACTER_ALPHA:

                if((result = nesla_lexer_parse_alpha(lexer, value, path, line)) == NESLA_FAILURE) {
                    goto exit;
                }
                break;
            case CHARACTER_DIGIT:

                if((result = nesla_lexer_parse_digit(lexer, value, path, line)) == NESLA_FAILURE) {
                    goto exit;
                }
                break;
            case CHARACTER_SYMBOL:

                if((result = nesla_lexer_parse_symbol(lexer, value, path, line)) == NESLA_FAILURE) {
                    goto exit;
                }
                break;
            default:
                break;
        }
    } while(nesla_stream_next(&lexer->stream) == NESLA_SUCCESS);

    if((result = nesla_lexer_append(lexer, TOKEN_END, 0, NULL, 0)) == NESLA_FAILURE) {
        goto exit;
    }

    nesla_lexer_reset(lexer);

exit:
    return result;
}

nesla_error_e nesla_lexer_get(const nesla_lexer_t *lexer, nesla_token_t **token)
{
    nesla_error_e result;
    nesla_list_entry_t *entry;

    if((result = nesla_list_get(&lexer->token, lexer->index, &entry)) == NESLA_FAILURE) {
        goto exit;
    }

    *token = entry->context;

exit:
    return result;
}

nesla_error_e nesla_lexer_initialize(nesla_lexer_t *lexer, const char *path)
{
    nesla_error_e result;

    if((result = nesla_stream_initialize(&lexer->stream, path)) == NESLA_FAILURE) {
        goto exit;
    }

    if((result = nesla_lexer_parse(lexer)) == NESLA_FAILURE) {
        goto exit;
    }

exit:
    return result;
}

nesla_error_e nesla_lexer_next(nesla_lexer_t *lexer)
{
    nesla_error_e result = NESLA_SUCCESS;

    if(lexer->index + 1 >= nesla_list_get_length(&lexer->token)) {
        result = SET_ERROR("No next token: %zu", lexer->index);
        goto exit;
    }

    ++lexer->index;

exit:
    return result;
}

nesla_error_e nesla_lexer_reset(nesla_lexer_t *lexer)
{
    nesla_error_e result;

    if((result = nesla_stream_reset(&lexer->stream)) == NESLA_FAILURE) {
        goto exit;
    }

    lexer->index = 0;

exit:
    return result;
}

void nesla_lexer_uninitialize(nesla_lexer_t *lexer)
{
    nesla_lexer_free_all(lexer);
    nesla_stream_uninitialize(&lexer->stream);
    memset(lexer, 0, sizeof(*lexer));
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
