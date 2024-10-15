#include <stdio.h>
#include <time.h>
#include "assembler.h"

int lex(const char *assembly, Token **tokens, size_t *tokenCount)
{
    *tokenCount = 0;
    *tokens = malloc(sizeof(Token) * 10);
    if (!(*tokens))
        return -1;
    return 0;
}

int parse(const Token *tokens, size_t tokenCount, Statements *statements)
{
    return 0; 
}

int translate(const Statements *statements, int **code, size_t *codeCount)
{
    return 0;
}

void writeResult(const int *code, size_t codeCount, const char *destPath)
{
    FILE *file = fopen(destPath, "w");
    if (!file)
        return;

    for (size_t i = 0; i < codeCount; ++i)
    {
        fprintf(file, "%d\n", code[i]);
    }

    fclose(file);
}

int printStats = 1;     //bool
int emitIndices = 1;    //bool

void assemble(char *assembly,char *destPath){
    // if(printStats){
    //     fprintf("\tTime estimate %d s",(assembly.count/300))//get size of assembly
    // }

    time_t start = time(NULL);

    int tokens = lex(assembly);

    int labels = parse(tokens);

    int code = translate(labels);

    time_t end = time(NULL);

    long diff = end - start;

    fprintf("Finished in: %lds", diff);

    writeResult(code, destPath);
}

int main(int argc, char const *argv[])
{
    assemble(NULL, NULL);
    return 0;
}
