#include "parser.h"


Parser::Parser() { }

void Parser::error(const string &s)
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
Node<T> Parser::terminal()
{
    size_t size;
    if (token->token_type == TOKEN_TKID) {
        Node<string> n(VAR, token->token_value);
        GetNextToken();
        return  n;
    } if (token->token_type == TOKEN_DGIT) {
        Node<int> n(CONST, stoi(token->token_value));
        GetNextToken();
        return n;
    } if (token->token_type == TOKEN_REAL) {
        Node<float> n(CONST, stof(token->token_value, &size));
        GetNextToken();
        return n;
    } if (token->token_type == TOKEN_LTRL) {
        Node<string> n(CONST, token->token_value);
        GetNextToken();
        return n;
    }  else {
        return parent_expr<T>();
    }
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
Node<T> Parser::summa()
{
      int kind;
      vector<Node<T>> sibl_nodes;
      sibl_nodes.push_back(terminal<T>());
      Node<T> n;

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
           sibl_nodes.push_back(terminal<T>());
           n = Node<T>(kind, sibl_nodes);
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
Node<T> Parser::relational_operation()
{
    Node<T> n = summa<T>();
    vector<Node<T>> tmp_nodes;
    if (token->token_value == "<") {
        GetNextToken();
        tmp_nodes.push_back(n);
        tmp_nodes.push_back(summa<T>());
        n = Node<T>(LESS, tmp_nodes);
    } else if (token->token_value == ">") {
        GetNextToken();
        tmp_nodes.push_back(n);
        tmp_nodes.push_back(summa<T>());
        n = Node<T>(MORE, summa<T>());
    }
    return n;
}
template<typename T>
Node<T> Parser::expretion()
{
    std::vector<Node<T>> sibling_nodes;

    if (token->token_type != TOKEN_TKID)
        return relational_operation<T>();
    Node<T> n(relational_operation<T>());
    if (n.state == TOKEN_TKID && token->token_type == TOKEN_ASOP) {
        GetNextToken();
        sibling_nodes.push_back(n);
        sibling_nodes.push_back(expretion<T>());
        n = Node<T>(SET, sibling_nodes);
    }
    return n;
}

template <typename T>
Node<T> Parser::parent_expr()
{
    if (token->token_value != "(")
        error("'(' expected");
    GetNextToken();
    Node<T> n(expretion<T>());
    if (token->token_value != ")")
        error("')' expected");
    GetNextToken();
    return n;
}

template <typename T>
Node<T> Parser::keyword()
{
    Node<T> n;
    string keyword = boost::to_upper(token->token_value);
    if (token->token_type == TOKEN_RSVD) {
        if (keyword == "PROCEDURE")
            n = Node<T>(PROCD);
         if (keyword == "LOOP")
            n = Node<T>(WHILE);
         if (keyword == "IS")
            n = Node<T>(SCOPE);
         if (keyword == "END")
             n = Node<T>(ENDSCOPE);
    }
    GetNextToken();
    return n;
}

template <typename T>
Node<T> Parser::statement()
{
    Node<T> n;
    std::vector<Node<T>> tmp_opers;
    string lexem = boost::to_upper(token->token_value);
    if (token->token_type == TOKEN_RLOP) {
        n = relational_operation<T>();
        GetNextToken();
        n.add_sibling_node(parent_expr<T>());
        n.add_sibling_node(statement<T>());

        if (lexem == "ELSEIF") {
            n = Node<T>(ELIF);
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
        n = Node<T>(ENDSTAT);
        GetNextToken();
    } else if (token->token_type == TOKEN_ALWD)
        if (lexem == "(") {
            n = Node<T>(EMPTY);
            GetNextToken();
            while (token->token_value != ")")
                n = Node<T>(SEQ, n, statement<T>());
            GetNextToken();
        } else {
            n = Node<T>(EXPR, expretion<T>());
            if (token->token_value != ";")
                error("';' expected");
            GetNextToken();
    }
    return n;
}

template <typename T>
Node<T> Parser::parse()
{
    GetNextToken();
    Node<T> node(PROG, statement<T>());
    return node;
}


