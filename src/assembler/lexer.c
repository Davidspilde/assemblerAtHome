#include "lexer.h"

TType _get_token_type(char *token, int token_size, int *line_number, Config *asm_config)
{
    /*
    gets the token type
    */

    // checkl if token is an instruction
    for (int i = 0; i < asm_config->mnemonics_count; i++)
    {
        if (strcmp(token, asm_config->mnemonics[i].name) == 0)
        {
            return INST;
        }
    }

    // check if token is an immediate value
    if (isdigit(token[0]))
    {
        int hex_char_count = 0;
        for (int i = 0; i < token_size; i++)
        {
            // if character is a digit then no error
            // if character is an x and we have seen only one x then no error
            if (token[i] == 'x' && hex_char_count > 0)
            {
                fprintf(stderr, "Error on line: %d, Invalid immediate (%s)", *line_number, token);
                exit(EXIT_FAILURE);
            }

            if (token[i] == 'x')
            {
                hex_char_count++;
                continue;
            }

            if (!isdigit(token[i]))
            {
                fprintf(stderr, "Error on line: %d, Invalid immediate (%s)", *line_number, token);
                exit(EXIT_FAILURE);
            }
        }
        return IMM;
    }

    // check if token is a register
    for (int i = 0; i < asm_config->registers_count; i++)
    {
        if (strcmp(token, asm_config->registers[i].name) == 0)
        {
            return REG;
        }
    }

    // check if token is of correct format
    for (int i = 0; i < token_size; i++)
    {
        if (!isalpha(token[i]) && !isdigit(token[i]) && token[i] != '_' && token[i] != ':')
        {
            fprintf(stderr, "error on line: %d, Not a valid token (must contain only character, number or underscore)", *line_number);
            exit(EXIT_FAILURE);
        }
    }

    // check if token is a declare label
    if (token[token_size - 1] == ':')
    {
        if (token_size == 1)
        {
            fprintf(stderr, "error on line: %d, Not valid label declaration", *line_number);
            exit(EXIT_FAILURE);
        }

        return DEC_LABEL;
    }

    // else token must be a label or invalid, we find out later in parser
    return LABEL;
}

Token *_find_next_token(int *line_number, Config *asm_config)
{
    /*
    finds the next token in the assembly code
    */
    char *current_token = (char *)malloc(1000 * sizeof(char));
    int current_token_size = 0;
    TType token_type;

    char lexeme;
    int end_of_token_reached = 0;
    int should_increment_line_number = 0;
    while (!end_of_token_reached && (lexeme = (char)getchar()) != EOF)
    {
        switch (lexeme)
        {
        case '#':
        case '/':
            lexeme = getchar();
            while (lexeme != '\n' && lexeme != EOF && lexeme != '/')
            {
                lexeme = getchar();
            }
            break;
        case '\n':
            if (should_increment_line_number)
            {
                (*line_number)++;
            }
            else
            {
                should_increment_line_number = 1;
            }
        case ' ':
        case ',':
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

    int token_line_number = *line_number;

    if (should_increment_line_number)
    {
        (*line_number)++;
    }

    current_token[current_token_size] = '\0';

    if (current_token_size == 0)
    {
        return NULL;
    }

    token_type = _get_token_type(current_token, current_token_size, &token_line_number, asm_config);

    Token *t = (Token *)malloc(sizeof(Token));
    t->lexemes = (char *)malloc((current_token_size + 1) * sizeof(char));
    strcpy(t->lexemes, current_token);
    t->lexemes[current_token_size] = '\0';
    t->size = current_token_size;
    t->ttype = token_type;
    t->line_number = token_line_number;
    return t;
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
    int line_number = 1;
    while ((current_token = _find_next_token(&line_number, asm_config)) != NULL)
    {
        tokenArray.tokens[tokenArray.size] = *current_token;
        tokenArray.size++;
    }

    return tokenArray;
}
