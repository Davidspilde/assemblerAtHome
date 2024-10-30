#ifndef TRANSLATE_H
#define TRANSLATE_H

#include "token.h"
#include "config.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct
{
    char *immediate;
    char *dest;
    char *srca;
    char *srcb;
    char *opcode;
} Instruction;

#define MAX_WORD_SIZE 16

void translate(TokenArray *tokens, Config *asm_config, char *output_file_path, char flag);

#endif