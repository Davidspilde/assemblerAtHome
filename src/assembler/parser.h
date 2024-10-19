#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "config.h"

void parse_tokens(TokenArray *tokens, Config *asm_config);

#endif