#ifndef PARSER_H
#define PARSER_H
#include "LexicalAnalyzer.h"
#include <string>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include "node.h"

class Parser
{
private:
    Lexer *lexer;
protected:
    void error(const string &);
public:
    Parser();
    Parser(Lexer &l) : lexer(l) { }
    template <typename T>
    Node<T> terminal();
    template <typename T>
    Node<T> summa();
    template <typename T>
    Node<T> relational_operation();
    template <typename T>
    Node<T> expretion();
    template <typename T>
    Node<T> parent_expr();
    template <typename T>
    Node<T> statement();
    template <typename T>
    Node<T> keyword();
    template <typename T>
    Node<T> parse();
};

#endif // PARSER_H
