#include "lexer.h"

TType _get_token_type(char *token, int token_size)
{
    /*
    gets the token type
    */
    return 1;
}

Token *_find_next_token(int *line_number)
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

    TType token_type = _get_token_type(current_token, current_token_size);
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

TokenArray lex()
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
    while ((current_token = _find_next_token(&line_number)) != NULL)
    {
        tokenArray.tokens[tokenArray.size] = *current_token;
        tokenArray.size++;
    }
    
    return tokenArray;
}
