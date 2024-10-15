
typedef struct{

} Token;

typedef struct
{
    int index; // what type of int should this be?
    char *input;
    Token *tokens;
} FastLexer;

//Lexes
Token lex(FastLexer *lexer,char *input){
    lexer->index = 0;
    lexer->input = input; //Er no way dette er riktig
    lexer->tokens = ArrayList.empty();
}