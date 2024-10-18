#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

// Define a structure for Token
typedef struct
{
    char *type;  // Type of the token (e.g., instruction, identifier, etc.)
    char *value; // The actual value of the token
} Token;

// Define a structure for Statements (You will need to define this based on your specific needs)
// typedef struct
// {
//     // Add fields as needed
//     // For example: Token *tokens; size_t tokenCount;
// } Statements;

// Function prototypes
int lex(const char *assembly, Token **tokens, size_t *tokenCount);
// int parse(const Token *tokens, size_t tokenCount, Statements *statements);
// int translate(const Statements *statements, int **code, size_t *codeCount);
void writeResult(const int *code, size_t codeCount, const char *destPath);

#endif // ASSEMBLER_H