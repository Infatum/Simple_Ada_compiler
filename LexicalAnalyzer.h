#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <stdio.h>
#include <ctype.h>
using namespace std;

#define NEWLINE_MARK    '\n'
#define COMMENT_MARK    '-'
#define BLANK_MARK      ' '
#define UNDERSCORE      '_'
#define MAX_ID_LEN		17

#define TOKEN_UKWN		0
#define TOKEN_RSVD		1
#define TOKEN_TKID		2
#define TOKEN_DGIT		3
#define TOKEN_REAL		4
#define TOKEN_LTRL		5
#define TOKEN_RLOP		6
#define TOKEN_ADOP		7
#define TOKEN_MLOP		8
#define TOKEN_ASOP		9
#define TOKEN_ALWD		10

typedef struct _token {
    string	token_name;
    int		token_type;
    // unknown, reserved, digit, float, literal ...
} TOKEN;

extern TOKEN*          GetNextToken();
extern string	       Lexeme;
extern int             Value;
extern float	       ValueR;
extern string	       Literal;
