#include <stdio.h>
#include <time.h>
#include "assembler.h"

void assemble(char *destPath)
{
    time_t start = time(NULL);

    // pipeline
    // read_asm_config
    Config *config = read_asm_config("./src/assembler/asm_config/mnemonics", "./src/assembler/asm_config/registers");
    // read_asm -> lex_asm (generate and confirm tokens)
    TokenArray tokens = lex(config);
    // -> parse_tokens (validate structure of tokens and resolve labels)
    parse_tokens(&tokens, config);
    // -> translate_to_bin (generate machine code from set of tokens)
    // -> write to file
}

int main(int argc, char const *argv[])
{
    assemble(NULL);
    return 0;
}
