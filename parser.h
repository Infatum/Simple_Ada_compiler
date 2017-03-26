#ifndef PARSER_H
#define PARSER_H
#include "LexicalAnalyzer.h"
#include <string>
#include <iostream>
#include <locale>
#include "node.h"
#include <tuple>

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
template <typename Root, typename... T>
typename node<Root,T...>::return_type terminal()
{
    size_t size;
    if (token->token_type == TOKEN_TKID) {
        node<Root> n(VAR, token->token_value);
        GetNextToken();
        return  n;
    } else {
        return parent_expr<Root, T...>();
    }
}

template <typename Root, typename... T>
typename node<Root,T...>::return_type non_terminal()
{
    node<Root> n(CONST, token->token_value);
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
template <typename Root, typename... T>
typename node<Root,T...>::return_type summa()
{
      int kind;
      vector<node<T...>> child_nodes;
      int tok_t = token->token_type;
      if (tok_t == TOKEN_TKID)
          child_nodes.push_back(node<T...>(terminal<T...>));
      else if (tok_t == TOKEN_REAL || tok_t == TOKEN_DGIT || tok_t == TOKEN_LTRL)
          child_nodes.push_back(node<T...>(terminal<T...>));
      node<Root, T...> n;

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
           child_nodes.push_back(node<T...>(terminal<T...>()));
           n = node<Root, T...>(kind, child_nodes);
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
template <typename Root, typename... T>
typename node<Root,T...>::return_type relational_operation()
{
    node<Root, T...> n = summa<Root, T...>();
    vector<node<Root, T...>> tmp_nodes;
    if (token->token_value == "<") {
        GetNextToken();
        tmp_nodes.push_back(n);
        tmp_nodes.push_back(summa<T...>());
        n = node<T...>(LESS, tmp_nodes);
    } else if (token->token_value == ">") {
        GetNextToken();
        tmp_nodes.push_back(n);
        tmp_nodes.push_back(summa<T...>());
        n = node<T...>(MORE, summa<T...>());
    }
    return n;
}
template <typename Root, typename... T>
typename node<Root,T...>::return_type expretion()
{
    std::vector<node<T...>> sibling_nodes;

    if (token->token_type != TOKEN_TKID)
        return relational_operation<Root, T...>();
    node<Root, T...> n(relational_operation<Root,T...>());
    if (n.state == TOKEN_TKID && token->token_type == TOKEN_ASOP) {
        GetNextToken();
        sibling_nodes.push_back(n);
        sibling_nodes.push_back(expretion<T...>());
        n = node<Root,T...>(SET, sibling_nodes);
    }
    return n;
}

template <typename Root, typename... T>
typename node<Root,T...>::return_type parent_expr()
{
    if (token->token_value != "(")
        parse_error("'(' expected");
    GetNextToken();
    node<Root, T...> n(expretion<Root, T...>());
    if (token->token_value != ")")
        parse_error("')' expected");
    GetNextToken();
    return n;
}

template <typename Root, typename... T>
typename node<Root,T...>::return_type keyword()
{
    node<Root, T...> n;
    std::locale loc;
    string keyword = std::toupper(token->token_value, loc);
    if (token->token_type == TOKEN_RSVD) {
        if (keyword == "PROCEDURE")
            n = node<Root>(PROCD);
         if (keyword == "LOOP")
            n = node<Root>(WHILE);
         if (keyword == "IS")
            n = node<Root>(SCOPE);
         if (keyword == "END")
             n = node<Root>(ENDSCOPE);
    }
    GetNextToken();
    return n;
}

template <typename Root, typename... T>
typename node<Root,T...>::return_type statement()
{
    node<Root,T...> n;
    std::vector<node<Root, T...>> sibling_nodes;
    std::vector<node<Root, T...>> tmp_opers;
    std::locale loc;
    string lexem = std::toupper(token->token_value, loc);
    if (token->token_type == TOKEN_RLOP) {
        n = relational_operation<Root, T...>();
        GetNextToken();
        sibling_nodes.push_back(node<T...>(parent_expr<T...>()));
        sibling_nodes.push_back(node<T...>(statement<T...>()));

        if (lexem == "ELSEIF") {
            n = node<Root>(ELIF);
            GetNextToken();
            sibling_nodes.push_back(statement<T...>());
        }
    } else if (token->token_type == TOKEN_RSVD) {
       n = keyword<Root>();
       GetNextToken();
       sibling_nodes.push_back(terminal<T...>());
       GetNextToken();
       sibling_nodes.push_back(parent_expr<T...>());
       sibling_nodes.push_back(statement<T...>());
    } else if (token->token_value == ";") {
        n = sibling_nodes.push_back(ENDSTAT);
        GetNextToken();
    } else if (token->token_type == TOKEN_ALWD)
        if (lexem == "(") {
            n = node<Root>(EMPTY);
            GetNextToken();
            while (token->token_value != ")")
                n = node<Root, T...>(SEQ, n, statement<T...>());
            GetNextToken();
        } else {
            n = node<Root,T...>(EXPR, expretion<T...>());
            if (token->token_value != ";")
                parse_error("';' expected");
            GetNextToken();
    }
    return n;
}

template <typename Root, typename... T>
typename node<Root,T...>::return_type parse()
{
    GetNextToken();
    node<Root, T...> node(PROG, statement<T...>());
    return node;
}
};

#endif // PARSER_H
