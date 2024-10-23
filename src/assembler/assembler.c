#include <stdio.h>
#include <time.h>
#include "assembler.h"

void assemble(char *destPath)
{
    time_t start = time(NULL);

    // pipeline
    // read_asm_config
    char *mnemonic_path = "./src/assembler/asm_config/mnemonics";
    char *register_path = "./src/assembler/asm_config/registers";
    char *instruction_format_path = "./src/assembler/asm_config/instruction_format";
    Config *config = read_asm_config(mnemonic_path, register_path, instruction_format_path);
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
