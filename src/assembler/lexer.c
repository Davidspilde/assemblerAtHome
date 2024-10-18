#include "lexer.h"

TType _get_token_type(char *token, int token_size, Config *asm_config)
{
    /*
    gets the token type
    */
    for (int i = 0; i < asm_config->mnemonics_count; i++)
    {
        if (strcmp(token, asm_config->mnemonics[i].name) == 0)
        {
            return INST;
        }
    }

    for (int i = 0; i < asm_config->registers_count; i++)
    {
        if (strcmp(token, asm_config->registers[i].name) == 0)
        {
            return OP;
        }
    }

    // check if token is a label
    if (token[token_size - 1] == ':')
    {
        if (token_size == 1)
        {
            return INVALID;
        }
        for (int i = 0; i < token_size - 1; i++)
        {
            // check if label contains only alphabets, digits and underscores
            if (!isalpha(token[i]) && !isdigit(token[i]) && token[i] != '_')
            {
                return INVALID;
            }
        }
        return LABEL;
    }

    // check if token is an immediate value
    if (isdigit(token[0]))
    {
        int hex_char_count = 0;
        for (int i = 0; i < token_size - 1; i++)
        {
            if (token[i] == 'x')
                hex_char_count++;
            if (!isdigit(token[i]) && token[i] != 'x')
                return INVALID;
        }

        if (hex_char_count > 1)
            return INVALID;
        return IMM;
    }

    return INVALID;
}

Token *_find_next_token(int *line_number, Config *asm_config)
{
    /*
    finds the next token in the assembly code
    */
    char *current_token = (char *)malloc(1000 * sizeof(char));
    int current_token_size = 0;

    char lexeme;
    int end_of_token_reached = 0;
    while ((lexeme = (char)getchar()) != EOF && !end_of_token_reached)
    {
        switch (lexeme)
        {
        case '#':
        case '/':
            lexeme = getchar();
            while (lexeme != '\n' && lexeme != EOF && lexeme != '/')
            {
            }
            break;
        case '\n':
            (*line_number)++;
        case ' ':
        case '\t':
            if (current_token_size > 0)
            {
                end_of_token_reached = 1;
            }
            break;
        default:
            current_token[current_token_size] = lexeme;
            current_token_size++;
            break;
        }
    }

    if (current_token_size == 0)
    {
        return NULL;
    }

    TType token_type = _get_token_type(current_token, current_token_size, asm_config);
    if (token_type != INVALID)
    {
        Token *t = (Token *)malloc(sizeof(Token));
        t->lexemes = (char *)malloc((current_token_size + 1) * sizeof(char));
        strcpy(t->lexemes, current_token);
        t->lexemes[current_token_size] = '\0';
        t->size = current_token_size;
        t->ttype = token_type;
        return t;
    }
    else
    {
        printf("Invalid token: %s at line: (%d)\n", current_token, *line_number);
        exit(1);
    }
}

TokenArray lex(Config *asm_config)
{
    /*
    Finds and validates all tokens in given code
    */

    TokenArray tokenArray;
    tokenArray.size = 0;
    tokenArray.tokens = (Token *)malloc(1000 * sizeof(Token));

    // find next token
    Token *current_token;
    int line_number = 0;
    while ((current_token = _find_next_token(&line_number, asm_config)) != NULL)
    {
        tokenArray.tokens[tokenArray.size] = *current_token;
        tokenArray.size++;
    }

    return tokenArray;
}
