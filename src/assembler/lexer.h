#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include "token.h"


TokenArray lex(const char *assembly_code);

#endif