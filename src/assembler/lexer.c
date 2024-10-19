#include "lexer.h"

int line_number;

TType _get_token_type(char *token, int token_size, Config *asm_config)
{
    /*
    gets the token type
    */
    for (int i = 0; i < asm_config->mnemonics_count; i++)
    {
        if (strcmp(token, asm_config->mnemonics[i].name) == 0)
        {
            return INST, line_number;
        }
    }


    // check if token is an immediate value
    if (isdigit(token[0]))
    {
        int hex_char_count = 0;
        for (int i = 0; i < token_size - 1; i++)
        {
            if (token[i] > 'F')
                hex_char_count++;
            if (!isdigit(token[i]) && token[i] != 'x'||hex_char_count>1){
            fprintf(stderr, "Error on line: %d, Labels can not start with digits", line_number);
            exit(EXIT_FAILURE);
            }
        }
        return IMM, line_number;
    }

    for (int i = 0; i < asm_config->registers_count; i++)
    {
        if (strcmp(token, asm_config->registers[i].name) == 0)
        {
            return REG,line_number;
        }
    }

    // check if token is a declare label
    if (token[token_size - 1] == ':')
    {
        if (token_size == 1)
        {
            fprintf(stderr, "error on line: %d, Not valid label declaration", line_number);
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < token_size - 1; i++)
        {
            if (!isalpha(token[i]) && !isdigit(token[i]) && token[i] != '_'){
                fprintf(stderr, "error on line: %d, Not valid label declaration", line_number);
                exit(EXIT_FAILURE);
            }}
        return DEC_LABEL,line_number;
    }
    for (int i = 0; i < token_size - 1; i++){
        if (isalpha(token[i]) && isdigit(token[i]) && token[i] == '_')
        {
            return LABEL,line_number;
        }
    }
    fprintf(stderr, "Error on line: %d, Unkown Token: %s", line_number, token);
    exit(EXIT_FAILURE);
}

Token *_find_next_token(int *line_number, Config *asm_config)
{
    /*
    finds the next token in the assembly code
    */
    char *current_token = (char *)malloc(1000 * sizeof(char));
    int current_token_size = 0;
    int token_line_num;
    TType token_type;

    char lexeme;
    int end_of_token_reached = 0;
    while (!end_of_token_reached && (lexeme = (char)getchar()) != EOF)
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

    current_token[current_token_size] = '\0';

    if (current_token_size == 0)
    {
        return NULL;
    }

    token_type, token_line_num = _get_token_type(current_token, current_token_size, asm_config);

    Token *t = (Token *)malloc(sizeof(Token));
    t->lexemes = (char *)malloc((current_token_size + 1) * sizeof(char));
    strcpy(t->lexemes, current_token);
    t->lexemes[current_token_size] = '\0';
    t->size = current_token_size;
    t->ttype = token_type;
    t->line_number = token_line_num;
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
    line_number = 0;
    while ((current_token = _find_next_token(&line_number, asm_config)) != NULL)
    {
        tokenArray.tokens[tokenArray.size] = *current_token;
        tokenArray.size++;
    }

    return tokenArray;
}
