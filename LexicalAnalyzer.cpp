#include "LexicalAnalyzer.h"

string Lexer::getLexeme() const
{
    return Lexeme;
}

void Lexer::trim(char **str)
{
    char *end;
    while(isspace(**str)) (*str)++;
    end = *str + strlen(*str) - 1;
    while(end > *str && isspace(*end)) end--;
    *(end+1) = 0;
}

/******************************************************************************************
*** FUNCTION: GetOperator                                                               ***
*******************************************************************************************
*** DESCRIPTION: get operator from current Lexeme                                       ***
*** INPUT ARGS :                                                                        ***
*** OUTPUT ARGS:                                                                        ***
*** IN/OUT ARGS:                                                                        ***
*** RETURN     :                                                                        ***
******************************************************************************************/
TOKEN* Lexer::GetOperator()
{
    if (Lexeme.empty())
        return NULL;
    // ignore comments
    while (Lexeme.at(0) == '-' && Lexeme.at(1) == '-') {
        size_t pos = Lexeme.find(NEWLINE_MARK);
        Lexeme = Lexeme.substr(pos + 1);
    }
    int token_type = TOKEN_UKWN;
    string	token_name = "";

    // check relational operators
    for (size_t i = 0; i < sizeof(rla_ops) / sizeof(rla_ops[0]); i++) {
        token_name = rla_ops[i];
        if ( token_name.compare(Lexeme.substr(0, token_name.length())) == 0) {
            token_type = TOKEN_RLOP;
            break;
        }
    }
    if (token_type == TOKEN_UKWN) {
        // check additional operators
        for (size_t i = 0; i < sizeof(add_ops) / sizeof(add_ops[0]); i++) {
            token_name = add_ops[i];
            if ( token_name.compare(Lexeme.substr(0, token_name.length())) == 0) {
                token_type = TOKEN_ADOP;
                break;
            }
        }
    }
    if (token_type == TOKEN_UKWN) {
        // check miltiplicational operators
        for (size_t i = 0; i < sizeof(mul_ops) / sizeof(mul_ops[0]); i++) {
            token_name = mul_ops[i];
            if ( token_name.compare(Lexeme.substr(0, token_name.length())) == 0) {
                token_type = TOKEN_MLOP;
                break;
            }
        }
    }
    if (token_type == TOKEN_UKWN) {
        // check assign operators
        for (size_t i = 0; i < sizeof(asn_ops) / sizeof(asn_ops[0]); i++) {
            token_name = asn_ops[i];
            if ( token_name.compare(Lexeme.substr(0, token_name.length())) == 0) {
                token_type = TOKEN_ASOP;
                break;
            }
        }
    }
    // check token type
    if (token_type == TOKEN_UKWN) return NULL;
    TOKEN* token = new TOKEN;
    token->token_value = token_name;
    token->token_type = token_type;
    Lexeme = Lexeme.substr(token_name.length());
    return token;
}
/******************************************************************************************
*** FUNCTION: IsDigital                                                                 ***
*******************************************************************************************
*** DESCRIPTION: check the token is digital number or not                               ***
*** INPUT ARGS :                                                                        ***
*** OUTPUT ARGS:                                                                        ***
*** IN/OUT ARGS:                                                                        ***
*** RETURN     : bool                                                                   ***
******************************************************************************************/

bool Lexer::IsDigital(string token)
{
    for (size_t i = 0; i < token.length(); i++) {
        char ch = token.at(i);
        if (ch < '0' || ch > '9') return false;
    }
    return true;
}
/******************************************************************************************
*** FUNCTION:  GetTokenType                                                             ***
*******************************************************************************************
*** DESCRIPTION: return token type except operators                                     ***
*** INPUT ARGS :                                                                        ***
*** OUTPUT ARGS:                                                                        ***
*** IN/OUT ARGS:                                                                        ***
*** RETURN     : int                                                                    ***
******************************************************************************************/

int Lexer::GetTokenType(string token)
{
    // check reserved keywords
    for (size_t i = 0; i < sizeof(keyword) / sizeof(keyword[0]); i++) {
        if (token.compare(keyword[i]) == 0)
            return TOKEN_RSVD;
    }

    // check digital numbers
    if (IsDigital(token))
        return TOKEN_DGIT;

    // check float numbers
    size_t pos = token.find(".");
    if (pos != string::npos) {
        string token1 = token.substr(0, pos);
        string token2 = token.substr(pos+1);
        if (IsDigital(token1) && IsDigital(token2))
            return TOKEN_REAL;
    }
    size_t token_len = token.length();

    // check tokenid value
    bool istokenid = true;
    for (size_t i = 0; i < token_len; i++) {
        char ch = token.at(i);
        if (!isalnum(ch) && ch != UNDERSCORE && ch != '.') {
            istokenid = false;
            break;
        }
    }
    if (istokenid)
        return TOKEN_TKID;
    if (token.length() == 1 && allow_syms.find(token) != string::npos)
        return TOKEN_ALWD;

    // check literal string
    if (token.at(0) == '"' && token.at(token_len - 1) == '"' && token.find(NEWLINE_MARK) == string::npos)
        return TOKEN_LTRL;

    // unknown token
    return TOKEN_UKWN;
}
/******************************************************************************************
*** FUNCTION: GetNextToken                                                              ***
*******************************************************************************************
*** DESCRIPTION: get next token from the Lexeme                                         ***
*** INPUT ARGS :                                                                        ***
*** OUTPUT ARGS:                                                                        ***
*** IN/OUT ARGS:                                                                        ***
*** RETURN     :                                                                        ***
******************************************************************************************/

TOKEN* Lexer::GetNextToken()
{
    string token = "";
    TOKEN* token_desc = NULL;
    while (token.empty() && !Lexeme.empty()) {
        // ignore comments
        while (Lexeme.at(0) == '-' && Lexeme.at(1) == '-') {
            size_t pos = Lexeme.find(NEWLINE_MARK);
            Lexeme = Lexeme.substr(pos + 1);
        }

        // ignore spaces or newlines until meet a new letters
        while (!Lexeme.empty() && (Lexeme.at(0) == BLANK_MARK || Lexeme.at(0) == NEWLINE_MARK))
            Lexeme = Lexeme.substr(1);

        if (Lexeme.empty())
            break;

        // parse token with delimeters
        size_t ptr = Lexeme.find_first_of(delimiters, 0);
        if (ptr == 0) { // operator met
            token_desc = GetOperator();
            if (token_desc)
                return token_desc;
            else {
                token = Lexeme.substr(0, 1);
                Lexeme = Lexeme.substr(1);
            }
        } else if (ptr == string::npos) {
            token = Lexeme;
            Lexeme = "";
        } else {
            // check operator once more for the word type operators
            token_desc = GetOperator();
            if (token_desc)
                return token_desc;
            token = Lexeme.substr(0, ptr);
            Lexeme = Lexeme.substr(ptr);
        }
        // check literal string
        if (token.at(0) == '"') {
            ptr = Lexeme.find('"', 0);
            if (ptr != string::npos) {
                token.append(Lexeme.substr(0, ptr + 1));
                Lexeme = Lexeme.substr(ptr + 1);
            } else { // single '"'
                token = "\"";
                Lexeme = token.substr(1) + Lexeme;
            }
        }
        char *data = strdup(token.c_str());
        trim(&data);
        token = data;
        if (Lexeme.empty())
            break;
    }
    if (token.empty())
        return token_desc;   // return NULL
    else {
        token_desc = new TOKEN;
        token_desc->token_value = token;
        token_desc->token_type = GetTokenType(token_desc->token_value);
        switch (token_desc->token_type) {
            case TOKEN_DGIT:
                Value = atoi(token.c_str());
                break;
            case TOKEN_REAL:
                ValueR = atof(token.c_str());
                break;
            case TOKEN_LTRL:
                Literal = token_desc->token_value;
                break;
            default:
                Value = 0;
                ValueR = 0;
                Literal = "";
                break;
        }
    }
    return token_desc;
}
