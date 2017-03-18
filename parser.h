#ifndef PARSER_H
#define PARSER_H
#include "LexicalAnalyzer.h"
#include <string>
#include <iostream>
#include <locale>
#include "node.h"

class Parser
{
private:
    Token * token = nullptr;
protected:
    void parse_error(const string &);
public:
    Parser() {}

void parse_err(const string &s)
{
    cerr << "Parse error: " << s << '\n';
}

/******************************************************************************************
*** FUNCTION: terminal                                                                  ***
*******************************************************************************************
*** DESCRIPTION: parses terminals basing on token type, forms the lexical tree          ***
*** INPUT ARGS :                                                                        ***
*** TYPE PARAMS: T where T - string, integer, real                                      ***
*** OUTPUT ARGS:                                                                        ***
*** IN/OUT ARGS:                                                                        ***
*** RETURN     : Node<T>                                                                ***
******************************************************************************************/
template <typename T>
BaseNode<T> terminal()
{
    size_t size;
    if (token->token_type == TOKEN_TKID) {
        BaseNode<T> n(VAR, token->token_value);
        GetNextToken();
        return  n;
    } else {
        return parent_expr<T>();
    }
}
template <typename T>
BaseNode<T> non_terminal()
{
    BaseNode<T> n(CONST, token->token_value);
    GetNextToken();
    return n;
}

/******************************************************************************************
*** FUNCTION: summa                                                                     ***
*******************************************************************************************
*** DESCRIPTION: parses math operations basing on token type, forms the lexical         ***
    tree(Node with child expressions)
*** INPUT ARGS :                                                                        ***
*** TYPE PARAMS: T where T - type of the Node                                           ***
*** OUTPUT ARGS:                                                                        ***
*** IN/OUT ARGS:                                                                        ***
*** RETURN     : Node<T>                                                                ***
******************************************************************************************/
template <typename T>
BaseNode<T> summa()
{
      int kind;
      vector<BaseNode<T>> child_nodes;
      int tok_t = token->token_type;
      if (tok_t == TOKEN_TKID)
          child_nodes.push_back(terminal<T>());
      else if (tok_t == TOKEN_REAL || tok_t == TOKEN_DGIT || tok_t == TOKEN_LTRL)
          child_nodes.push_back(non_terminal<T>());
      BaseNode<T> n;

      while (token->token_type == TOKEN_ADOP) {
           if (token->token_value == "+")
               kind = ADD;
           else if (token->token_value == "-")
               kind = SUBTR;
           else if (token->token_value == "*")
               kind = MULT;
           else if (token->token_value == "/")
               kind = DIV;
           GetNextToken();
           child_nodes.push_back(terminal<T>());
           n = BaseNode<T>(kind, child_nodes);
       }
      return n;
}

/******************************************************************************************
*** FUNCTION: relational_operations                                                                     ***
*******************************************************************************************
*** DESCRIPTION: parses terminals basing on token type, forms the lexical               ***
    tree(variables and constants)
*** INPUT ARGS :                                                                        ***
*** TYPE PARAMS: T where T - type of the Node                                           ***
*** OUTPUT ARGS:                                                                        ***
*** IN/OUT ARGS:                                                                        ***
*** RETURN     : Node<T>                                                                ***
******************************************************************************************/
template <typename T>
BaseNode<T> relational_operation()
{
    BaseNode<T> n = summa<T>();
    vector<BaseNode<T>> tmp_nodes;
    if (token->token_value == "<") {
        GetNextToken();
        tmp_nodes.push_back(n);
        tmp_nodes.push_back(summa<T>());
        n = BaseNode<T>(LESS, tmp_nodes);
    } else if (token->token_value == ">") {
        GetNextToken();
        tmp_nodes.push_back(n);
        tmp_nodes.push_back(summa<T>());
        n = BaseNode<T>(MORE, summa<T>());
    }
    return n;
}
template<typename T>
BaseNode<T> expretion()
{
    std::vector<BaseNode<T>> sibling_nodes;

    if (token->token_type != TOKEN_TKID)
        return relational_operation<T>();
    BaseNode<T> n(relational_operation<T>());
    if (n.state == TOKEN_TKID && token->token_type == TOKEN_ASOP) {
        GetNextToken();
        sibling_nodes.push_back(n);
        sibling_nodes.push_back(expretion<T>());
        n = BaseNode<T>(SET, sibling_nodes);
    }
    return n;
}

template <typename T>
BaseNode<T> parent_expr()
{
    if (token->token_value != "(")
        parse_error("'(' expected");
    GetNextToken();
    BaseNode<T> n(expretion<T>());
    if (token->token_value != ")")
        parse_error("')' expected");
    GetNextToken();
    return n;
}

template <typename T>
BaseNode<T> keyword()
{
    BaseNode<T> n;
    std::locale loc;
    string keyword = std::toupper(token->token_value, loc);
    if (token->token_type == TOKEN_RSVD) {
        if (keyword == "PROCEDURE")
            n = BaseNode<T>(PROCD);
         if (keyword == "LOOP")
            n = BaseNode<T>(WHILE);
         if (keyword == "IS")
            n = BaseNode<T>(SCOPE);
         if (keyword == "END")
             n = BaseNode<T>(ENDSCOPE);
    }
    GetNextToken();
    return n;
}

template <typename T>
BaseNode<T> statement()
{
    BaseNode<T> n;
    std::vector<BaseNode<T>> tmp_opers;
    std::locale loc;
    string lexem = std::toupper(token->token_value, loc);
    if (token->token_type == TOKEN_RLOP) {
        n = relational_operation<T>();
        GetNextToken();
        n.add_sibling_node(parent_expr<T>());
        n.add_sibling_node(statement<T>());

        if (lexem == "ELSEIF") {
            n = BaseNode<T>(ELIF);
            GetNextToken();
            n.add_sibling_node(statement<T>());
        }
    } else if (token->token_type == TOKEN_RSVD) {
       n = keyword<T>();
       GetNextToken();
       n.add_sibling_node(terminal<T>());
       GetNextToken();
       n.add_sibling_node(parent_expr<T>());
       n.add_sibling_node(statement<T>());
    } else if (token->token_value == ";") {
        n = BaseNode<T>(ENDSTAT);
        GetNextToken();
    } else if (token->token_type == TOKEN_ALWD)
        if (lexem == "(") {
            n = BaseNode<T>(EMPTY);
            GetNextToken();
            while (token->token_value != ")")
                n = BaseNode<T>(SEQ, n, statement<T>());
            GetNextToken();
        } else {
            n = BaseNode<T>(EXPR, expretion<T>());
            if (token->token_value != ";")
                parse_error("';' expected");
            GetNextToken();
    }
    return n;
}

template <typename T>
BaseNode<T> parse()
{
    GetNextToken();
    BaseNode<T> node(PROG, statement<T>());
    return node;
}
};

#endif // PARSER_H
