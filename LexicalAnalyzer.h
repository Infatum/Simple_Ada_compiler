#ifndef LEXER_H
#define LEXER_H
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
    string	token_value;
    int		token_type;
    // unknown, reserved, digit, float, literal ...
} TOKEN;

class Lexer
{
private:
        TOKEN*          GetNextToken();
        string	       Lexeme;
        int             Value;
        float	       ValueR;
        string	       Literal;
        const char *keyword[] = { "BEGIN", "MODULE", "CONSTANT", "PROCEDURE", "IS", "IF", "THEN",
                                  "ELSE", "ELSIF", "WHILE", "LOOP", "FLOAT", "INTEGER", "CHAR", "GET",
                                  "PUT", "END"
                                };
        const char *rla_ops[] = { "/=", "<=", ">=", "=", "<",  ">"};
        const char *add_ops[] = { "+", "-", "OR"};
        const char *mul_ops[] = { "*", "/" , "REM", "MOD", "AND" };
        const char *asn_ops[] = {":=", ":"};
        const char delimiters[] = " ;\n\t=:<>+-*/()";
        string allow_syms = "(),:;.\"";

        string          Lexeme = "";
        int		        Value = 0;
        float	        ValueR = 0;
        string	        Literal = "";
protected:
          bool IsDigital(string token);
          void trim(char **str);
          int GetTokenType(string token);
          TOKEN* GetOperator();
public:

       Lexer(string &filename) : Lexeme(filename) {}
       TOKEN* GetNextToken();
       string getLexeme() const;
};
#endif



