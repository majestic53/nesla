# NESLA (NESL-Assembler) Grammar

## Lexer Grammar

```
COMMENT             ::= ;.*\n

DIRECTIVE           ::= .[BANK|BIN|BYTE|CHR|DEF|INC|MAP|MIR|ORG|PRG|RESV|UNDEF|WORD]

IDENTIFIER          ::= [_A-Z][_A-Z0-9]

INSTRUCTION         ::= ADC | AND | ASL | BCC | BCS | BEQ | BIT | BMI | BNE | BPL | BRK | BVC | BVS | CLC | CLD | CLI
                        | CLV | CMP | CPX | CPY | DEC | DEX | DEY | EOR | INC | INX | INY | JMP | JSR | LDA | LDX | LDY
                        | LSR | NOP | ORA | PHA | PHP | PLA | PLP | ROL | ROR | RTI | RTS | SBC | SEC | SED | SEI | STA
                        | STX | STY | TAX | TAY | TSX | TXA | TXS | TYA

LABEL               ::= <IDENTIFIER>:

LITERAL             ::= "[<LITERAL_ESCAPE>|.]"

LITERAL_CHARACTER   ::= '<LITERAL_ESCAPE>|.'

LITERAL_ESCAPE      ::= \[&[0-1]{8}|[0-9]{3}|$[A-F0-9]{2}]

OPERAND             ::= A|X|Y

SCALAR              ::= &[0-1]{1-8}|[0-9]{1-5}|$[A-F0-9]{1-2}

SYMBOL              ::= ,#()
```

## Parser Grammar

```
TBD
```
