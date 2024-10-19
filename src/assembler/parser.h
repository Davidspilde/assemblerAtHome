#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "config.h"

TokenArray parse_tokens(TokenArray tokens, Config *asm_config);

#endif