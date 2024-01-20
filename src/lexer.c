#include "include/lexer.h"

lexer_t* init_lexer(char* src)
{
    lexer_t* lexer = calloc(1, sizeof(struct LEXER_STRUCT));
    lexer->src = src;
    lexer->src_size = strlen(src);
    lexer->idx = 0;
    lexer->c = src[lexer->idx];

    return lexer;
}

void lexer_advance(lexer_t* lexer)
{
    if (lexer->idx < lexer->src_size && lexer->c != '\0') {
         lexer->idx++;
         lexer->c = lexer->src[lexer->idx];
    }
}

char lexer_peek(lexer_t* lexer, int offset)
{
    return lexer->src[MIN(lexer->idx + offset, lexer->src_size)];
}

token_t* lexer_advance_with(lexer_t* lexer, token_t* token)
{
    lexer_advance(lexer);
    return token;
}

token_t* lexer_advance_current(lexer_t* lexer, int type)
{
    char* value = calloc(2, sizeof(char));
    value[0] = lexer->c;
    value[1] = '\0';

    token_t* token = init_token(value, type);
    lexer_advance(lexer);

    return token;
}

void lexer_skip_whitespace(lexer_t* lexer)
{
    while (lexer->c == 13   ||
           lexer->c == '\n' ||
           lexer->c == '\t' ||
           lexer->c == ' ')
    lexer_advance(lexer);
}

token_t* lexer_parse_id(lexer_t* lexer)
{
    char* value = calloc(1, sizeof(char));
    while (isalpha(lexer->c))
    {
        value = realloc(value, (strlen(value) + 1) * sizeof(char));
        strcat(value, (char[]){lexer->c, 0});
        lexer_advance(lexer);
    }
    return init_token(value, TOKEN_ID);
}

token_t* lexer_parse_number(lexer_t* lexer)
{
    char* value = calloc(1, sizeof(char));
    while (isdigit(lexer->c))
    {
        value = realloc(value, (strlen(value) + 1) * sizeof(char));
        strcat(value, (char[]){lexer->c, 0});
        lexer_advance(lexer);
    }
    return init_token(value, TOKEN_INT);
}

token_t* lexer_next_token(lexer_t* lexer)
{
    while(lexer->c != '\0') {
        lexer_skip_whitespace(lexer);
        if (isalpha(lexer->c)) {
            return lexer_parse_id(lexer);
        }
        if (isdigit(lexer->c)) {
            return lexer_advance_with(lexer, lexer_parse_number(lexer));
        }
        switch (lexer->c)
        {
            case '=':
                if (lexer_peek(lexer, 1) == '>'){
                    lexer_advance(lexer);
                    return lexer_advance_with(lexer, init_token("=>", TOKEN_RIGHT_ARROW));
                }
                return lexer_advance_with(lexer, init_token("=", TOKEN_EQUALS));
                break;
            case '(': return lexer_advance_current(lexer, TOKEN_LPARENT);
            case ')': return lexer_advance_current(lexer, TOKEN_RPARENT);
            case '{': return lexer_advance_current(lexer, TOKEN_LBRACE);
            case '}': return lexer_advance_current(lexer, TOKEN_RBRACE);
            case '<': return lexer_advance_current(lexer, TOKEN_LT);
            case '>': return lexer_advance_current(lexer, TOKEN_GT);
            case ':': return lexer_advance_current(lexer, TOKEN_COLON);
            case ',': return lexer_advance_current(lexer, TOKEN_COMMA);
            case ';': return lexer_advance_current(lexer, TOKEN_SEMI);
            case '\0': break;
            default:
            printf("[Lexer]: Unexpected character %c\n", lexer->c); exit(1); break;
        }
    }
    return init_token(0, TOKEN_EOF);
}