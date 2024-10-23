#ifndef TOKEN_H
#define TOKEN_H

typedef enum
{
    INST,
    REG,
    IMM,
    DEC_LABEL,
    LABEL,
} TType;

typedef struct
{
    char *lexemes;
    int size;
    int line_number;
    int address;
    TType ttype;
    int is_last;
    int data;
} Token;

typedef struct
{
    Token *tokens;
    int size;
} TokenArray;

typedef struct
{
    char *name;
    char *address;
    int defined;
} LabelValidator;

#endif
