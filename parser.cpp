#include "parser.h"


Parser::Parser(TOKEN &t)
{
    if (&t != nullptr) {

    }
}

void Parser::error(const string &s)
{
    cerr << "Parse error: " << s << '\n';
}

/******************************************************************************************
*** FUNCTION: readfile                                                                  ***
*******************************************************************************************
*** DESCRIPTION: parses terminals                                                       ***
*** INPUT ARGS : T where T - real or integer                                            ***
*** OUTPUT ARGS:                                                                        ***
*** IN/OUT ARGS:                                                                        ***
*** RETURN     : Node                                                                   ***
******************************************************************************************/
Node<int, string> Parser::terminal()
{
    if (token->token_type == TOKEN_TKID || token->token_type == TOKEN_REAL
            || token->token_type == TOKEN_LTRL) {
        Node<int,string> n(VAR, token->token_value);
        GetNextToken();
        return n;
    }  else {
        return parent_expr();
    }
}

Node<int, string> Parser::summa()
{
      int kind;
      vector<Node<int,string>> sibl_nodes;
      sibl_nodes.push_back(terminal());
      Node<int,string> n;

      while (token->token_type == TOKEN_ADOP) {
           if (token->token_value == "+")
               kind = ADD;
           else
               kind = SUBSTR;
           GetNextToken();
           sibl_nodes.push_back(terminal());
           n = Node<int,string>(kind, sibl_nodes);
       }
      return n;
}

Node<int,string> Parser::relational_operation()
{
    Node<int,string> n = summa();
    vector<Node<int,string>> tmp_nodes;
    if (token->token_value == "<") {
        GetNextToken();
        tmp_nodes.push_back(n);
        tmp_nodes.push_back(summa());
        n = Node<int,string>(LT, tmp_nodes);
    } else if (token->token_value == ">") {
        GetNextToken();
        tmp_nodes.push_back(n);
        tmp_nodes.push_back(summa());
        n = Node<int,string>(MT, summa());
    }
    return n;
}

Node<int, string> Parser::expretion()
{
    std::vector<Node<int,string>> sibling_nodes;

    if (token->token_type != TOKEN_TKID)
        return relational_operation();
    Node<int,string> n(relational_operation());
    if (n.kind == TOKEN_TKID && token->token_type == TOKEN_ASOP) {
        GetNextToken();
        sibling_nodes.push_back(n);
        sibling_nodes.push_back(expretion());
        n = Node<int,string>(SET, sibling_nodes);
    }
    return n;
}

Node<int,string> Parser::parent_expr()
{
    if (token->token_value != "(")
        error("'(' expected");
    GetNextToken();
    Node<int,string> n(expretion());
    if (token->token_value != ")")
        error("')' expected");
    GetNextToken();
    return n;
}

Node<int, string> Parser::keyword()
{
    Node<int,string> n;
    string keyword = boost::to_upper(token->token_value);
    if (keyword == TOKEN_RSVD) {
        if (keyword == "PROCEDURE")
            n = Node<int,string>(PROCD);
         if (keyword == "LOOP")
            n = Node<int,string>(WHILE);
         if (keyword == "IS")
            n = Node<int,string>(SCOPE);
         if (keyword == "END")
             n = Node<int,string>(ENDSCOPE);
    }
    GetNextToken();
    return n;
}

Node<int, string> Parser::statement()
{
    Node<int,string> n;
    std::vector<Node<int,string>> tmp_opers;
    string lexem = boost::to_upper(token->token_value);
    if (token->token_type == TOKEN_RLOP) {
        n = relational_operation();
        GetNextToken();
        n.add_operator(parent_expr());
        n.add_operator(statement());

        if (lexem == "ELSEIF") {
            n = Node<int,string>(ELIF);
            GetNextToken();
            n.add_operator(statement());
        }
    } else if (token->token_type == TOKEN_RSVD) {
       n = keyword();
       GetNextToken();
       n.add_operator(terminal());
       GetNextToken();
       n.add_operator(parent_expr());
       n.add_operator(statement());
    } else if (token->token_value == ";") {
        n = Node<int,string>(ENDSTAT);
        GetNextToken();
    } else if (token->token_type == TOKEN_ALWD)
        if (lexem == "(") {
            n = Node<int,string>(EMPTY);
            GetNextToken();
            while (token->token_value != ")")
                n = Node<int,string>(SEQ, n, statement());
            GetNextToken();
        } else {
            n = Node<int,string>(EXPR, expretion());
            if (token->token_value != ";")
                error("';' expected");
            GetNextToken();
    }
    return n;
}

Node<int, string> Parser::parse()
{
    GetNextToken();
    Node<int,string> node(PROG, statement());
    return node;
}


