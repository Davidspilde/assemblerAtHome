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

int _get_label_address(TokenArray *declared_labels, char *label)
{
    // check if label is valid
    for (int i = 0; i < declared_labels->size; i++)
    {
        if (!strncmp(label, declared_labels->tokens[i].lexemes, strlen(label)))
        {
            return declared_labels->tokens[i].address;
        }
    }

    return -1;
}

void _resolve_labels(TokenArray *tokens)
{
    // gather all labels
    int number_of_labels = 0;
    for (int i = 0; i < tokens->size; i++)
    {
        Token token = tokens->tokens[i];
        if (token.ttype == DEC_LABEL)
            number_of_labels++;
    }

    int current_declared = 0;
    TokenArray *declared_labels = (TokenArray *)malloc(sizeof(TokenArray));
    declared_labels->tokens = (Token *)malloc(number_of_labels * sizeof(Token));
    declared_labels->size = number_of_labels;
    for (int i = 0; i < tokens->size; i++)
    {
        Token token = tokens->tokens[i];
        if (token.ttype == DEC_LABEL)
            declared_labels->tokens[current_declared++] = token;
    }

    // convert labels to immediates
    for (int i = 0; i < tokens->size; i++)
    {
        Token *token = &tokens->tokens[i];
        if (token->ttype != LABEL)
            continue;

        int address = _get_label_address(declared_labels, token->lexemes);
        if (address == -1)
        {
            fprintf(stderr, "Error: Invalid token %s at line %d\n", token->lexemes, token->line_number);
            exit(1);
        }

        token->ttype = IMM;
        token->lexemes = (char *)malloc(100 * sizeof(char));
        token->size = sprintf(token->lexemes, "%d", address);
    }
}

char *_get_pattern(Token *token, Config *asm_config)
{
    if (token->ttype == INST)
    {
        for (int i = 0; i < asm_config->instruction_formats_count; i++)
        {
            if (!strcmp(token->lexemes, asm_config->instruction_formats[i].name))
            {
                return asm_config->instruction_formats[i].format;
            }
        }
    }
    return NULL;
}

void _validate_tokens(TokenArray *tokenarr, Config *asm_config)
{
    // get next pattern
    char *current_pattern = NULL;
    int current_pattern_index = -1;
    int current_pattern_size = -1;

    Token *last_registry = NULL;

    for (int i = 0; i < tokenarr->size; i++)
    {
        Token *current_token = &tokenarr->tokens[i];
        current_token->is_last = 0;
        if (current_pattern_index == current_pattern_size)
        {
            if (last_registry != NULL)
            {

                last_registry->is_last = 1;
            }
            current_pattern = NULL;
        }

        if (current_token->ttype == REG)
        {
            last_registry = current_token;
        }

        if (current_pattern == NULL)
        {
            char *token_pattern = _get_pattern(current_token, asm_config);
            if (token_pattern == NULL)
            {
                if (current_token->ttype != DEC_LABEL)
                {
                    fprintf(stderr, "Error: Unexpected token %s at line %d\n", current_token->lexemes, current_token->line_number);
                    exit(1);
                }
                continue;
            }
            if (token_pattern[0] != 'N')
            {
                // we reached an instruction
                current_pattern = token_pattern;
                current_pattern_index = 0;
                current_pattern_size = strlen(current_pattern);
                continue;
            }
            continue;
        }

        TType expected_type = current_pattern[current_pattern_index] == 'I' ? IMM : REG;

        if (current_token->ttype != expected_type)
        {
            fprintf(stderr, "Error: Unexpected token %s at line %d (expected token of type %s)\n", current_token->lexemes, current_token->line_number, expected_type == REG ? "registry" : "immediate");
            exit(1);
        }

        current_token->registry_type = current_pattern[current_pattern_index];

        current_pattern_index++;
    }
}

void parse_tokens(TokenArray *tokens, Config *asm_config)
{
    // find address of all tokens
    _set_token_addresses(tokens);

    // replace all labels with addresses
    _resolve_labels(tokens);

    // validate tokens (raises error if something is wrong)
    _validate_tokens(tokens, asm_config);
}
