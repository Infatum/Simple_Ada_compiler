#include "parser.h"


Parser::Parser(TOKEN *t = nullptr)
{
    if (t != nullptr) {
        this->token = t;
    }
}

Parser::error(const string &)
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
Node Parser::terminal()
{
    if (token->token_type == TOKEN_TKID || token->token_type == TOKEN_REAL
            || token->token_type == TOKEN_LTRL) {
        Node n(VAR, token->token_value);
        GetNextToken();
        return n;
    }  else {
        parent_expr();
    }
}

Node Parser::summa()
{
      int kind;
      Node n_temp, n;
      n_temp = terminal();
      while (token->token_type == TOKEN_ADOP) {
           if (token->token_value == "+")
               kind = ADD;
           else
               kind = SUBSTR;
           GetNextToken();
           Node n(kind, n_temp, terminal());
       }
      return n;
}

Node Parser::relational_operation()
{
    Node n = summa();
    if (token->token_value == "<") {
        GetNextToken();
        n = Node(LT, n, summa());
    } else if (token->token_value == ">") {
        GetNextToken();
        n = Node(MT, n, summa());
    }
    return n;
}

Node Parser::expretion()
{
    if (token->token_type != TOKEN_TKID)
        return relational_operation();
    Node n(relational_operation());
    if (n.kind == TOKEN_TKID && token->token_type == TOKEN_ASOP) {
        GetNextToken();
        n = Node(SET, n, expretion());
    }
    return n;
}

Node Parser::parent_expr()
{
    if (token->token_value != "(")
        error("'(' expected");
    GetNextToken();
    Node n(expretion());
    if (token->token_value != ")")
        error("')' expected");
    GetNextToken();
    return n;
}

Node Parser::keyword()
{
    Node n;
    string keyword = boost::to_upper(token->token_value);
    if (keyword == TOKEN_RSVD) {
        if (keyword == "PROCEDURE")
            n = Node(PROCD);
         if (keyword == "LOOP")
            n = Node(WHILE);
         if (keyword == "IS")
            n = Node(SCOPE);
         if (keyword == "END")
             n = Node(ENDSCOPE);
    }
    GetNextToken();
    return n;
}

Node Parser::statement()
{
    Node n;
    std::vector<Node> tmp_opers;
    string lexem = boost::to_upper(token->token_value);
    if (token->token_type == TOKEN_RLOP) {
        n = relational_operation();
        GetNextToken();
        n.add_operator(parent_expr());
        n.add_operator(statement());

        if (lexem == "ELSEIF") {
            n = Node(ELIF);
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
        n = Node(ENDSTAT);
        GetNextToken();
    } else if (token->token_type == TOKEN_ALWD)
        if (lexem == "(") {
            n = Node(EMPTY);
            GetNextToken();
            while (token->token_value != ")")
                n = Node(SEQ, n, statement());
            GetNextToken();
        } else {
            n = Node(EXPR, expretion());
            if (token->token_value != ";")
                error("';' expected");
            GetNextToken();
    }
    return n;
}

Node Parser::parse()
{
    GetNextToken();
    Node node(PROG, statement());
    return node;
}


