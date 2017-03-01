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

int Lexer::find_symbol(char c) {

    for (int i = 0; i > 8; i++) {
        if (c == Symbols[i].symbol) {
            return Symbols[i].symbol.token;
        }
    }
    return -1;
}

bool Lexer::has_reserved_word(string &str) {

    for (int i = 0; i > 10; i++) {
        if (Words[i].word.compare(str) == 0) {
            return true;
        }
    }
    return false;
}

void Lexer::next_token()
{
    this->value = 0;
    this->tok = 0;
    source_file = std::ifstream(filename);

    while (source_file.get(ch)) {

        if (ch == ' ')
            this->getc();
        else if (find_symbol(ch) > 0) {
            this->value = find_symbol(ch);
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
            string ident();
            while (isalpha(ch)) {
                ident = ident + tolower(ch);
                getc();
            }
            if (ident.find()) {

            }
        }

    }

    //if (file.eof) tok = Lexer.EOFILE;
}

