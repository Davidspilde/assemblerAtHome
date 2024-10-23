#include "translate.h"

void send_word(int data)
{
}

int translateToken(TokenArray *tokenarr)
{
    int start_data = tokenarr->size;
    int word_fill = 0;
    for (int i = 0; i < tokenarr->size; i++)
    {
        Token token = tokenarr->tokens[i];
        switch (token.ttype)
        {
        case REG:

            break;

        default:
            break;
        }
    }
}

void translate(TokenArray *tokens)
{
    translateToken(tokens);
}
