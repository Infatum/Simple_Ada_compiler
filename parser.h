#ifndef PARSER_H
#define PARSER_H

class Parser
{
protected:
    enum { VAR, CONST, ADD, SUB, LT, SET, IF1, IF2, WHILE, DO, EMPTY, SEQ, EXPR, PROG };
public:
    Parser();
};

#endif // PARSER_H
