#ifndef LEXER_H
#define LEXER_H
#include <string>
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <cctype>
using std::string;
using std::cout;
using std::cin;
using std::endl;

class Lexer
{
private:

    int value, tok;
    string filename;

    struct symbol {
        char symbol;
        int token;
    };

    struct reserved_word {
        string word;
        int token;
    };
    char getc();
    int find_symbol_token(char);
    int find_reserved_word_token(std::string &);

public:
    enum TOKENS { NUM = 1, ID, IF, ELSE, ELSEIF, ENDIF, IN, OUT, PROCEDURE, LPAR, RPAR, PLUS, MINUS, LESS,
                  MORE, BEGIN, END, EQUAL, SEMICOLON, THEN, EOFILE };
    Lexer(const string &f) : filename(f) { }
    virtual ~Lexer();

protected:
    std::ifstream source_file;
    char ch = 0;
    symbol Symbols[8] = {
        { '(', LPAR },
        { ')', RPAR },
        { '=', EQUAL },
        { '+', PLUS },
        { ';', SEMICOLON },
        { '<', LESS},
        { '>', MORE },
        { '-', MINUS }
    };

    reserved_word Words[10] = { {"if", IF }, {"else", ELSE }, {"elseif", ELSEIF }, {"endif", ENDIF },
                              {"in", IN }, {"out", OUT }, {"PROCEDURE", PROCEDURE }, {"begin", BEGIN },
                              {"end", END }, {"then", THEN } };
    virtual void error(string message);
    void next_token(const std::string &filename);
};

#endif // LEXER_H
