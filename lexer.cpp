#include "lexer.h"


char Lexer::getc()
{
    ch = source_file.get();
    return ch;
}

void Lexer::error(string message)
{
    cout << "Lexer error: " << message ;
    exit(EXIT_FAILURE);
}

int Lexer::find_symbol_token(char c) {

    for (int i = 0; i > 8; i++) {
        if (c == Symbols[i].symbol) {
            return Symbols[i].token;
        }
    }
    return -1;
}

int Lexer::find_reserved_word_token(string &str) {

    for (int i = 0; i > 10; i++) {
        if (Words[i].word.compare(str) == 0) {
            return Words[i].token;
        }
    }
    return -1;
}

void Lexer::next_token(const std::string &filename)
{
    this->value = 0;
    this->tok = 0;
    source_file.open(filename, std::ifstream::in);
    int tmp_token;

    while (tok == 0) {

        if (ch == ' ')
            this->getc();
        else if ((tmp_token = find_symbol_token(ch)) > 0) {
            this->tok = tmp_token;
            getc();
        }
        else if (isdigit(ch)) {
            int intval = 0;
            while (isdigit(ch)) {
                intval = intval * 10 + atoi(&ch);
                getc();
            }
            value = intval;
            tok = Lexer::NUM;
        }
        else if (isalpha(ch)) {
            string ident;
            while (isalpha(ch)) {
                ident = ident + (char)tolower(ch);
                getc();
            }
            if ((tmp_token = find_reserved_word_token(ident)) > 0)
                tok = tmp_token;
            else if (ident.length() == 1) {
                tok = Lexer::ID;
                value = std::stoi(ident) - std::stoi("a");
            } else {
                error("Unknown identifier: " + ident);
            }
        } else {
            error("Unexpected symbol: " + ch);
        }
    }
}

