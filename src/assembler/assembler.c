#include <stdio.h>
#include <time.h>
#include "assembler.h"

void assemble(char *dest_path, char *flag)
{
    // flag is either -b for binary or -h for hex
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
    translate(&tokens, config, dest_path, flag[1]);

    printf("Assembled in %ld seconds\n", time(NULL) - start);
}

int main(int argc, char const *argv[])
{
    assemble(argv[1], argv[2]);
    return 0;
}
