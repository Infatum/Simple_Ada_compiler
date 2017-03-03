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
template <typename T>
Node<T> Parser::terminal()
{
    if (token->token_type == TOKEN_TKID || token->token_type == TOKEN_REAL
            || token->token_type == TOKEN_LTRL) {
        Node<string> n(VAR, token->token_value);
        GetNextToken();
        return n;
    }  else {
        return parent_expr<T>();
    }
}
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
           else
               kind = SUBSTR;
           GetNextToken();
           sibl_nodes.push_back(terminal<T>());
           n = Node<T>(kind, sibl_nodes);
       }
      return n;
}
template <typename T>
Node<T> Parser::relational_operation()
{
    Node<T> n = summa<T>();
    vector<Node<T>> tmp_nodes;
    if (token->token_value == "<") {
        GetNextToken();
        tmp_nodes.push_back(n);
        tmp_nodes.push_back(summa<T>());
        n = Node<T>(LT, tmp_nodes);
    } else if (token->token_value == ">") {
        GetNextToken();
        tmp_nodes.push_back(n);
        tmp_nodes.push_back(summa<T>());
        n = Node<T>(MT, summa<T>());
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
    if (n.kind == TOKEN_TKID && token->token_type == TOKEN_ASOP) {
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

//Node<int, string> Parser::keyword()
//{
//    Node<int,string> n;
//    string keyword = boost::to_upper(token->token_value);
//    if (keyword == TOKEN_RSVD) {
//        if (keyword == "PROCEDURE")
//            n = Node<int,string>(PROCD);
//         if (keyword == "LOOP")
//            n = Node<int,string>(WHILE);
//         if (keyword == "IS")
//            n = Node<int,string>(SCOPE);
//         if (keyword == "END")
//             n = Node<int,string>(ENDSCOPE);
//    }
//    GetNextToken();
//    return n;
//}

//Node<int, string> Parser::statement()
//{
//    Node<int,string> n;
//    std::vector<Node<int,string>> tmp_opers;
//    string lexem = boost::to_upper(token->token_value);
//    if (token->token_type == TOKEN_RLOP) {
//        n = relational_operation();
//        GetNextToken();
//        n.ass_sibling_node(parent_expr());
//        n.ass_sibling_node(statement());

//        if (lexem == "ELSEIF") {
//            n = Node<int,string>(ELIF);
//            GetNextToken();
//            n.ass_sibling_node(statement());
//        }
//    } else if (token->token_type == TOKEN_RSVD) {
//       n = keyword();
//       GetNextToken();
//       n.ass_sibling_node(terminal());
//       GetNextToken();
//       n.ass_sibling_node(parent_expr());
//       n.ass_sibling_node(statement());
//    } else if (token->token_value == ";") {
//        n = Node<int,string>(ENDSTAT);
//        GetNextToken();
//    } else if (token->token_type == TOKEN_ALWD)
//        if (lexem == "(") {
//            n = Node<int,string>(EMPTY);
//            GetNextToken();
//            while (token->token_value != ")")
//                n = Node<int,string>(SEQ, n, statement());
//            GetNextToken();
//        } else {
//            n = Node<int,string>(EXPR, expretion());
//            if (token->token_value != ";")
//                error("';' expected");
//            GetNextToken();
//    }
//    return n;
//}

//Node<int, string> Parser::parse()
//{
//    GetNextToken();
//    Node<int,string> node(PROG, statement());
//    return node;
//}


