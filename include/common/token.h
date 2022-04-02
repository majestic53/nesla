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
 * @file token.h
 * @brief Common token.
 */

#ifndef NESLA_TOKEN_H_
#define NESLA_TOKEN_H_

#include <literal.h>

/*!
 * @enum nesla_directive_e
 * @brief Token directive type.
 */
typedef enum {
    DIRECTIVE_BANK = 0,         /*!< Bank directive */
    DIRECTIVE_BYTE,             /*!< Byte directive */
    DIRECTIVE_CHARACTER,        /*!< Character directive */
    DIRECTIVE_DEFINE,           /*!< Define directive */
    DIRECTIVE_INCLUDE,          /*!< Include directive */
    DIRECTIVE_INCLUDE_BINARY,   /*!< Include binary directive */
    DIRECTIVE_MAPPER,           /*!< Mapper directive */
    DIRECTIVE_MIRROR,           /*!< Mirror directive */
    DIRECTIVE_ORIGIN,           /*!< Origin directive */
    DIRECTIVE_PROGRAM,          /*!< Program directive */
    DIRECTIVE_RESERVE,          /*!< Reserve directive */
    DIRECTIVE_UNDEFINE,         /*!< Undefine directive */
    DIRECTIVE_WORD,             /*!< Word directive */
    DIRECTIVE_MAX,              /*!< Max directive */
} nesla_directive_e;

/*!
 * @enum nesla_instruction_e
 * @brief Token instruction type.
 */
typedef enum {
    INSTRUCTION_ADC,            /*!< Add carry instruction */
    INSTRUCTION_AND,            /*!< Logical and instruction */
    INSTRUCTION_ASL,            /*!< Arithmetic shift left instruction */
    INSTRUCTION_BCC,            /*!< Branch carry clear instruction */
    INSTRUCTION_BCS,            /*!< Branch carry set instruction */
    INSTRUCTION_BEQ,            /*!< Branch equal instruction */
    INSTRUCTION_BIT,            /*!< Bit compare instruction */
    INSTRUCTION_BMI,            /*!< Branch negative instruction */
    INSTRUCTION_BNE,            /*!< Branch not-equals instruction */
    INSTRUCTION_BPL,            /*!< Branch positive instruction */
    INSTRUCTION_BRK,            /*!< Break instruction */
    INSTRUCTION_BVC,            /*!< Branch overflow clear instruction */
    INSTRUCTION_BVS,            /*!< Branch overflow set instruction */
    INSTRUCTION_CLC,            /*!< Clear carry instruction */
    INSTRUCTION_CLD,            /*!< Clear decimal instruction */
    INSTRUCTION_CLI,            /*!< Clear interrupt disable instruction */
    INSTRUCTION_CLV,            /*!< Clear overflow instruction */
    INSTRUCTION_CMP,            /*!< Compare instruction */
    INSTRUCTION_CPX,            /*!< Compare index-x instruction */
    INSTRUCTION_CPY,            /*!< Compare index-y instruction */
    INSTRUCTION_DEC,            /*!< Decrement instruction */
    INSTRUCTION_DEX,            /*!< Decrement index-x instruction */
    INSTRUCTION_DEY,            /*!< Decrement index-y instruction */
    INSTRUCTION_EOR,            /*!< Logical xor instruction */
    INSTRUCTION_INC,            /*!< Increment instruction */
    INSTRUCTION_INX,            /*!< Increment index-x instruction */
    INSTRUCTION_INY,            /*!< Increment index-y instruction */
    INSTRUCTION_JMP,            /*!< Jump instruction */
    INSTRUCTION_JSR,            /*!< Jump subroutine instruction */
    INSTRUCTION_LDA,            /*!< Load accumulator instruction */
    INSTRUCTION_LDX,            /*!< Load index-x instruction */
    INSTRUCTION_LDY,            /*!< Load index-y instruction */
    INSTRUCTION_LSR,            /*!< Logical shift right instruction */
    INSTRUCTION_NOP,            /*!< No operation instruction */
    INSTRUCTION_ORA,            /*!< Logical or instruction */
    INSTRUCTION_PHA,            /*!< Push accumulator instruction */
    INSTRUCTION_PHP,            /*!< Push status instruction */
    INSTRUCTION_PLA,            /*!< Pull accumulator instruction */
    INSTRUCTION_PLP,            /*!< Pull status instruction */
    INSTRUCTION_ROL,            /*!< Rotate left instruction */
    INSTRUCTION_ROR,            /*!< Rotate right instruction */
    INSTRUCTION_RTI,            /*!< Return interrupt instruction */
    INSTRUCTION_RTS,            /*!< Return subroutine instruction */
    INSTRUCTION_SBC,            /*!< Subtract carry instruction */
    INSTRUCTION_SEC,            /*!< Set carry instruction */
    INSTRUCTION_SED,            /*!< Set decimal instruction */
    INSTRUCTION_SEI,            /*!< Set interrupt disable instruction */
    INSTRUCTION_STA,            /*!< Store accumulator instruction */
    INSTRUCTION_STX,            /*!< Store index-x instruction */
    INSTRUCTION_STY,            /*!< Store index-y instruction */
    INSTRUCTION_TAX,            /*!< Transfer accumulator to index-x instruction */
    INSTRUCTION_TAY,            /*!< Transfer accumulator to index-y instruction */
    INSTRUCTION_TSX,            /*!< Transfer stack pointer to index-x instruction */
    INSTRUCTION_TXA,            /*!< Transfer index-x to accumulator instruction */
    INSTRUCTION_TXS,            /*!< Transfer index-x to stack pointer instruction */
    INSTRUCTION_TYA,            /*!< Transfer index-y to accumulator instruction */
    INSTRUCTION_MAX,            /*!< Max instruction */
} nesla_instruction_e;

/*!
 * @enum nesla_operand_e
 * @brief Token operand type.
 */
typedef enum {
    OPERAND_ACCUMULATOR = 0,    /*!< Accumulator operand */
    OPERAND_INDEX_X,            /*!< Index-X operand */
    OPERAND_INDEX_Y,            /*!< Index-Y operand */
    OPERAND_MAX,                /*!< Max operand */
} nesla_operand_e;

/*!
 * @enum nesla_symbol_e
 * @brief Token symbol type.
 */
typedef enum {
    SYMBOL_SEPERATOR = 0,   /*!< Seperator symbol */
    SYMBOL_IMMEDIATE,       /*!< Immediate symbol */
    SYMBOL_INDIRECT_CLOSE,  /*!< Close indirection symbol */
    SYMBOL_INDIRECT_OPEN,   /*!< Open indirection symbol */
    SYMBOL_MAX,             /*!< Max symbol */
} nesla_symbol_e;

/*!
 * @enum nesla_token_e
 * @brief Token type.
 */
typedef enum {
    TOKEN_END = 0,              /*!< End token */
    TOKEN_DIRECTIVE,            /*!< Directive token */
    TOKEN_IDENTIFIER,           /*!< Identifier token */
    TOKEN_INSTRUCTION,          /*!< Instruction token */
    TOKEN_LABEL,                /*!< Label token */
    TOKEN_LITERAL,              /*!< Literal token */
    TOKEN_OPERAND,              /*!< Operand token */
    TOKEN_SCALAR,               /*!< Scalar token */
    TOKEN_SYMBOL,               /*!< Symbol token */
} nesla_token_e;

/*!
 * @struct nesla_token_t
 * @brief Token context.
 */
typedef struct {
    nesla_token_e type;         /*!< Token type */
    int subtype;                /*!< Token subtype */
    const char *path;           /*!< Token file path */
    size_t line;                /*!< Token file line */
    nesla_literal_t literal;    /*!< Token literal context */
    uint16_t scalar;            /*!< Token scalar value */
} nesla_token_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*!
 * @brief Free token context.
 * @param[in,out] token Pointer to token context
 */
void nesla_token_free(nesla_token_t *token);

/*!
 * @brief Get token context file line.
 * @param[in] token Constant pointer to token context
 * @return File line
 */
size_t nesla_token_get_line(const nesla_token_t *token);

/*!
 * @brief Get token context literal value.
 * @param[in] token Constant pointer to token context
 * @return Constant pointer to literal context
 */
const nesla_literal_t *nesla_token_get_literal(const nesla_token_t *token);

/*!
 * @brief Get token context file path.
 * @param[in] token Constant pointer to token context
 * @return Constant pointer to file path
 */
const char *nesla_token_get_path(const nesla_token_t *token);

/*!
 * @brief Get token context scalar value.
 * @param[in] token Constant pointer to token context
 * @return Scalar value
 */
uint16_t nesla_token_get_scalar(const nesla_token_t *token);

/*!
 * @brief Get token context subtype.
 * @param[in] token Constant pointer to token context
 * @return Token subtype
 */
int nesla_token_get_subtype(const nesla_token_t *token);

/*!
 * @brief Get token context type.
 * @param[in] token Constant pointer to token context
 * @return Token type
 */
nesla_token_e nesla_token_get_type(const nesla_token_t *token);

/*!
 * @brief Set token context.
 * @param[in,out] token Pointer to token context
 * @param[in] type Token type
 * @param[in] subtype Token subtype
 * @param[in] path Constant pointer to token file path
 * @param[in] line Token file line
 */
void nesla_token_set(nesla_token_t *token, nesla_token_e type, int subtype, const char *path, size_t line);

/*!
 * @brief Set token context literal value.
 * @param[in,out] token Pointer to token context
 * @param[in] literal Constant pointer to literal context
 * @return NESLA_ERROR on failure, NESLA_SUCCESS otherwise
 */
nesla_error_e nesla_token_set_literal(nesla_token_t *token, const nesla_literal_t *literal);

/*!
 * @brief Set token context scalar value.
 * @param[in,out] token Pointer to token context
 * @param[in] scalar Scalar value
 */
void nesla_token_set_scalar(nesla_token_t *token, uint16_t scalar);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* NESLA_TOKEN_H_ */
