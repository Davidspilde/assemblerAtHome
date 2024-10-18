#include <stdio.h>
#include <time.h>
#include "assembler.h"
#include "lexer.h"

void assemble(char *assembly, char *destPath)
{
    time_t start = time(NULL);

    // pipeline
    // read_asm_config
    Config *config = read_asm_config("./asm_config/mnemonics", "./asm_config/registers");
    // read_asm -> lex_asm (generate and confirm tokens)
    // -> parse_tokens (validate structure of tokens)
    // -> translate_to_bin (generate machine code from set of tokens)
    // -> write to file
}

int main(int argc, char const *argv[])
{
    assemble(NULL, NULL);
    return 0;
}
