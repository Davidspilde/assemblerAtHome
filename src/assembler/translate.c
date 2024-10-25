#include "translate.h"

void _reverse_string(char *str)
{
    int length = strlen(str);
    for (int i = 0; i < length / 2; i++)
    {
        char temp = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = temp;
    }
}

void _empty_data(char *data, int length)
{
    memset(data, 0, length);
    data[0] = '\0'; // set null terminator at start
}

void _pad_data(char *data, int length)
{
    int data_length = strlen(data);
    for (int i = data_length; i < length - 1; i++)
    {
        data[i] = '0';
    }
    data[length - 1] = '\0'; // Null-terminate the string
}

void _send_word(char *data, char flag, FILE *file, int reversed)
{
    _pad_data(data, MAX_WORD_SIZE + 1);
    if (reversed)
    {
        _reverse_string(data);
    }
    _pad_data(data, MAX_WORD_SIZE + 1);
    (flag == 'b') ? fwrite(data, 1, MAX_WORD_SIZE, file) : fprintf(file, "%X", (int)strtol(data, NULL, 2));
    fwrite("\n", 1, 1, file);
    _empty_data(data, MAX_WORD_SIZE + 1);
}

void _int_to_binary_string(int value, char *output, int length)
{
    for (int i = length - 1; i >= 0; i--)
    {
        output[i] = (value & 1) ? '1' : '0';
        value >>= 1;
    }
    output[length - 1] = '\0'; // Null-terminate the string
}

char *_registry_to_binary(char *registry, Config *asm_config)
{
    for (int i = 0; i < asm_config->registers_count; i++)
    {
        if (strcmp(registry, asm_config->registers[i].name) == 0)
        {
            return asm_config->registers[i].binary_representation;
        }
    }
    return NULL;
}

char *_instruction_to_binary(char *instruction, Config *asm_config)
{
    for (int i = 0; i < asm_config->mnemonics_count; i++)
    {
        if (strcmp(instruction, asm_config->mnemonics[i].name) == 0)
        {
            return asm_config->mnemonics[i].binary_representation;
        }
    }
    return NULL;
}

char *_immediate_to_binary(char *immediate)
{
    int is_hex = 0;
    if (immediate[0] == '0' && (immediate[1] == 'x' || immediate[1] == 'X'))
    {
        is_hex = 1;
    }

    int value = is_hex ? strtol(immediate, NULL, MAX_WORD_SIZE) : atoi(immediate);

    char *binary_immediate = (char *)malloc((MAX_WORD_SIZE + 1) * sizeof(char));
    _int_to_binary_string(value, binary_immediate, MAX_WORD_SIZE + 1);
    return binary_immediate;
}

void _translate(TokenArray *tokenarr, Config *asm_config, FILE *file, char flag)
{
    char *data = (char *)malloc((MAX_WORD_SIZE + 1) * sizeof(char)); // word size + 1 for null terminator
    memset(data, 0, MAX_WORD_SIZE + 1);
    data[0] = '\0';
    for (int i = 0; i < tokenarr->size; i++)
    {
        Token token = tokenarr->tokens[i];

        switch (token.ttype)
        {
        case REG:
            char *binary_data = _registry_to_binary(token.lexemes, asm_config);
            strcat(data, binary_data);
            if (token.is_last)
            {
                _send_word(data, flag, file, 1);
            }
            break;
        case INST:
            char *binary_opcode = _instruction_to_binary(token.lexemes, asm_config);
            strcat(data, binary_opcode);

            break;
        case IMM:
            char *binary_immediate = _immediate_to_binary(token.lexemes);
            strcat(data, binary_immediate);

            _send_word(data, flag, file, 0);
            break;
        default:
            break;
        }
    }
}

void translate(TokenArray *tokens, Config *asm_config, char *output_file_path, char flag)
{
    FILE *file = fopen(output_file_path, (flag == 'b') ? "w" : "w");
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file %s\n", output_file_path);
        exit(1);
    }
    if (!(flag == 'b' || flag == 'h'))
    {
        fprintf(stderr, "Error, must include flag -b for binary or -h for hex\n");
        exit(1);
    }
    _translate(tokens, asm_config, file, flag);
}
