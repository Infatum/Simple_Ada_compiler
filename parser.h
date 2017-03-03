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
    TOKEN *token;
    enum { VAR = 1, SET, ENDSTAT, CONST, ADD, SUBSTR, LT, MT, IF, ELIF,
           ELSE, WHILE, PROCD, SCOPE, ENDSCOPE, EMPTY, SEQ, EXPR, PROG };
protected:
    void error(const string &);
public:
    Parser(TOKEN &t);
    template <typename T>
    Node<T> terminal();
//    Node<int,string> summa();
//    Node<int,string> relational_operation();
//    Node<int,string> expretion();
//    Node<int,string> parent_expr();
//    Node<int,string> statement();
//    Node<int,string> keyword();
//    Node<int,string> parse();
};

#endif // PARSER_H
