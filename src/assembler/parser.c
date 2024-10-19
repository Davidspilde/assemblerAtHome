#include "parser.h"

void _set_token_addresses(TokenArray *tokens)
{
    // instructions take one address
    // immediates take one address
    // labels take one address (basically an immediate)

    int current_address = -1;

    for (int i = 0; i < tokens->size; i++)
    {
        Token *token = &tokens->tokens[i];
        switch (token->ttype)
        {
        case INST:
            token->address = ++current_address;
            break;
        case REG:
            token->address = current_address;
            break;
        case IMM:
            token->address = ++current_address;
            break;
        case DEC_LABEL:
            token->address = current_address + 1; // point to next instruction
            break;
        case LABEL:
            token->address = ++current_address;
            break;
        }
    }
}

int _get_label_address(Token *declared_labels, char *label)
{
    // check if label is valid
    for (int i = 0; i < declared_labels->size; i++)
    {
        if (!strcmp(label, declared_labels[i].lexemes))
            return declared_labels[i].address;
    }

    return -1;
}

void _resolve_labels(TokenArray *tokens)
{
    // gather all labels
    int number_of_labels = 0;
    for (int i = 0; i < tokens->size; i++)
    {
        Token *token = &tokens->tokens[i];
        if (token->ttype == DEC_LABEL)
            number_of_labels++;
    }

    int current_declared = 0;
    Token *declared_labels = (Token *)malloc(number_of_labels * sizeof(Token));
    declared_labels->size = number_of_labels;
    for (int i = 0; i < tokens->size; i++)
    {
        Token *token = &tokens->tokens[i];
        if (token->ttype == DEC_LABEL)
            declared_labels[current_declared++] = *token;
    }

    // convert labels to immediates
    for (int i = 0; i < tokens->size; i++)
    {
        Token *token = &tokens->tokens[i];
        if (token->ttype != LABEL)
            continue;

        int address = _get_label_address(declared_labels, token->lexemes);

        token->ttype = IMM;
        token->lexemes = (char *)malloc(100 * sizeof(char));
        token->size = sprintf(token->lexemes, "%d", address);
    }
}

void parse_tokens_Viktor(TokenArray *tokens, Config *asm_config)
{
    // find address of all tokens
    _set_token_addresses(tokens);

    // replace all labels with addresses
    _resolve_labels(tokens);

    // validate tokens
}

void parse_tokens_David(TokenArray *tokens, Config *asm_config)
{
    validateTokens();
    checkLabelValidator();
}