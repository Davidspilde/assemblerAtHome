#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include "token.h"

#include "config.h"

TokenArray lex(Config *asm_config);

#endif