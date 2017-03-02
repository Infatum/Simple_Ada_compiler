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
    Parser(TOKEN *t = nullptr);
    Node terminal();
    Node summa();
    Node relational_operation();
    Node expretion();
    Node parent_expr();
    Node statement();
    Node keyword();
    Node parse();
};

#endif // PARSER_H
