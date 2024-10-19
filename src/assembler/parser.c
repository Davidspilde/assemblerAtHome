#include "parser.h"

TokenArray parse_tokens(TokenArray tokens, Config *asm_config)
{
    TokenArray parsed_tokens;
    parsed_tokens.size = 0;
    parsed_tokens.tokens = (Token *)malloc(tokens.size * sizeof(Token));

    for (int i = 0; i < tokens.size; i++)
    {
        Token token = tokens.tokens[i];
        switch (token.ttype)
        {
        case INST:
            break;
        case OP:
            break;
        case IMM:
            break;
        case LABEL:
            break;
        case UNKNOWN:
            break;
        }
    }
}