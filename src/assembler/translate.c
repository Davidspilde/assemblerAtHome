#include "translate.h"

void send_word(char *data, char flag, FILE *file, int r, int address)
{
    fill_data(data, 17);
    if (r)
    {
        reverse(data);
    }
    fill_data(address, 17);
    reverse(address);
    (flag == 'b') ? fwrite(address, 1, 17, file) : fprintf(file, "%x\n", strtol(address, NULL, 2));
    (flag == 'b') ? fwrite(data, 1, 2, file) : fprintf(file, "%x\n", strtol(data, NULL, 2));
    data = "";
}

void int_to_binary_string(int value, char *output, int length)
{
    for (int i = length - 1; i >= 0; i--)
    {
        output[i] = (value & 1) ? '1' : '0';
        value >>= 1;
    }
    output[length] = '\0'; // Null-terminate the string
}

void reverse(char *str)
{
    int length = strlen(str);
    for (int i = 0; i < length / 2; i++)
    {
        char temp = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = temp;
    }
}

void fill_data(char *data, int length)
{
    int current_length = strlen(data);
    for (int i = current_length; i < length; i++)
    {
        data[i] = '0';
    }
    data[length] = '\0'; // Null-terminate the string
}

int translateToken(TokenArray *tokenarr, FILE *file, char flag)
{
    int start_data = tokenarr->size;
    int word_fill = 0;
    char *data = "";
    int r = 0;
    int data = 0;
    for (int i = 0; i < tokenarr->size; i++)
    {
        Token token = tokenarr->tokens[i];

        switch (token.ttype)
        {
        case REG:
            char binary_data[4];
            int_to_binary_string(token.data, binary_data, 4);
            strcat(data, binary_data);
            word_fill += 3;
            if (token.is_last)
            {
                r = 1;
                send_word(data, flag, file, r, token.address);
                r = 0;
                word_fill = 0;
            }
            break;
        case INST:
            char binary_opcode[6]; // needs 6 because of null terminator
            int_to_binary_string(token.data, binary_opcode, 6);
            strcat(data, binary_opcode);
            word_fill += 5;
            break;
        case IMM:
            if (word_fill > 0)
            {
                send_word(data, flag, file, r, token.address);
            }
            char binary_immediate[17];
            int_to_binary_string(token.data, binary_immediate, 17);
            strcat(data, binary_immediate);
            send_word(data, flag, file, r, token.address);
            word_fill = 0;
            break;
        default:
            break;
        }
    }
}

void translate(TokenArray *tokens, char *filename, char flag)
{
    FILE *file = fopen(filename, (flag == 'b') ? "wb" : "w");
    if (file == NULL)
    {
        printf("Error opening file %s\n", filename);
        return 1;
    }
    if (flag == 'b')
    {
        translateToken(tokens, file, flag); // binary
    }
    else if (flag == 'h')
    {
        translateToken(tokens, file, flag); // hex
    }
    else
    {
        printf("Must include flag -b for binary or -h for hex\n");
        EXIT_FAILURE;
    }
}
