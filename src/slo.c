#include "include/slo.h"
#include "include/lexer.h"
#include "include/io.h"

void slo_compile(char* src)
{
    lexer_t* lexer = init_lexer(src);
    token_t* tok = {0};

    while ((tok = lexer_next_token(lexer))->type != TOKEN_EOF)
    {
        printf("TOK(%s) (%d)\n", tok->value, tok->type);
    }
}

void slo_compile_file(const char* filename)
{
    char* src = slo_read_file(filename);
    slo_compile(src);

    if (NULL != src) {
        free(src);
        src = NULL;
    }
}
