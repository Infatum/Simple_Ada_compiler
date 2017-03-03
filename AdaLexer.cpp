#include <iostream>
#include <stdlib.h>
#include "parser.h"
//#include "LexicalAnalyzer.h"

using namespace std;

/******************************************************************************************
*** FUNCTION: readfile                                                                  ***
*******************************************************************************************
*** DESCRIPTION: read file contents and return it as string                             ***
*** INPUT ARGS :                                                                        ***
*** OUTPUT ARGS:                                                                        ***
*** IN/OUT ARGS:                                                                        ***
*** RETURN     : string                                                                 ***
******************************************************************************************/
string readfile(string filepath)
{
    ifstream file(filepath.c_str());
    if (file.is_open()) {
        string content((std::istreambuf_iterator<char>(file)),	(std::istreambuf_iterator<char>()));
        file.close();
        content.append("\n");
        transform(content.begin(), content.end(), content.begin(), ::toupper);
        return content;
    } else cerr << "Cannot open " << filepath << endl;
    return "";
}

int main(int argc, char*argv[])
{
    if (argc == 1) {
        cerr << "Usage:" << argv[0] << " filename" << endl;
        return -1;
    }
    string filename = argv[1];

    // get file contents
    Lexeme = readfile(filename);
    if (Lexeme.empty())
        return 0;
    else cerr << Lexeme << endl;
    // parse out the tokens
    cerr << endl;
    cerr << "***************  Parsing Token  *********************" << endl << endl;
    //TODO: rewrite to Parser object and assign token to parser object
    TOKEN* token = NULL;
    Parser p;

    while (token = GetNextToken()) {
        // print out the token
        switch (token->token_type) {
        case TOKEN_UKWN:
            cerr << "Unknown symbol\t\t";
            break;

        case TOKEN_RSVD:
            cerr << "Reserved keyword\t";
            //p.keyword();

            //if (find(keyword_list.begin(), keyword_list.end(), token->token_name)
            //== keyword_list.end()) keyword_list.push_back(token->token_name);
            break;

        case TOKEN_DGIT:
            cerr << "Integer number\t\t";
            if (IsDigital(token->token_value)) {

            }
            //if (find(digital_list.begin(), digital_list.end(), token->token_name)
            //== digital_list.end()) digital_list.push_back(token->token_name);
            break;

        case TOKEN_REAL:
            cerr << "Float Number\t\t";
            //if (find(fractional_list.begin(), fractional_list.end(), token->token_name)
            // == fractional_list.end()) fractional_list.push_back(token->token_name);
            break;

        case TOKEN_TKID:
            cerr << "Token ID\t\t";
            if (token->token_value.length() > MAX_ID_LEN)
                cerr << "(Token ID length should be shorter than " << MAX_ID_LEN << ")";
            //cerr << endl;
            //if (find(tokenid_list.begin(), tokenid_list.end(), token->token_name)
            //== tokenid_list.end()) tokenid_list.push_back(token->token_name);
            break;

        case TOKEN_LTRL:
            cerr << "Literal string\t\t";
            //if (find(literal_list.begin(), literal_list.end(), token->token_name)
            //== literal_list.end()) literal_list.push_back(token->token_name);
            break;

        case TOKEN_RLOP:
            cerr << "Rel'operator\t\t";
            //if (find(relopr_list.begin(), relopr_list.end(), token->token_name)
            //== relopr_list.end()) relopr_list.push_back(token->token_name);
            break;

        case TOKEN_ADOP:
            cerr << "Add'operator\t\t";
            //if (find(addopr_list.begin(), addopr_list.end(), token->token_name)
            //== addopr_list.end()) addopr_list.push_back(token->token_name);
            break;

        case TOKEN_MLOP:
            cerr << "Mul'operator\t\t";
            break;

        case TOKEN_ASOP:
            cerr << "Assign'operator\t\t";
            break;

        case TOKEN_ALWD:
            if (token->token_value.compare("(") == 0)
                cerr << "L-parent\t\t";
            else if (token->token_value.compare(")")== 0 )
                cerr << "R-parent\t\t";
            else
                cerr << "Allowed symbol\t\t";
            break;

        }
        cerr << token->token_value.c_str() << endl;
    }
    cerr<<endl;
    cerr << "***************  Parsing Finished  ******************" << endl<<endl;

    return 0;
}

