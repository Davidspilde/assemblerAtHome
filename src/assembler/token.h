#ifndef TOKEN_H
#define TOKEN_H

typedef enum
{
    INST,
    OP,
    IMM,
    LABEL,
    UNKNOWN
} TType;

typedef struct
{
    char *lexemes;
    int size;
    int line_number;
    TType ttype;
} Token;

typedef struct
{
    Token *tokens;
    int size;
} TokenArray;

#endif
