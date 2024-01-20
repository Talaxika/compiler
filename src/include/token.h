#ifndef SLO_TOKEN_H
#define SLO_TOKEN_H
#include "slibs.h"

typedef struct TOKEN_STRUCT
{
    char* value;
    enum
    {
        TOKEN_ID,
        TOKEN_EQUALS,       // =
        TOKEN_LPARENT,      // (
        TOKEN_RPARENT,      // )
        TOKEN_LBRACE,       // {
        TOKEN_RBRACE,       // }
        TOKEN_COLON,        // :
        TOKEN_COMMA,        // ,
        TOKEN_LT,           // <
        TOKEN_GT,           // >
        TOKEN_RIGHT_ARROW,  // =>
        TOKEN_INT,          // int
        TOKEN_SEMI,         // ;
        TOKEN_EOF,          // \0
    } type;
} token_t;

token_t* init_token(char* value, int type);

#endif