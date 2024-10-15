#ifndef TOKEN_H
#define TOKEN_H

typedef enum
{
    INST,
    OP,
    IMM,
    LABEL,
    INVALID
} TType;

typedef struct
{
    char *lexemes;
    int size;
    TType ttype;
} Token;

typedef struct
{
    Token *tokens;
    int size;
} TokenArray;

#endif
