#include "translator.h"

template <typename T>
void start_translation(BaseNode<T> &node)
{
    Parser p;
    switch (node.get_state()) {
    case VAR:

        break;
    case SET:

        break;
    case ENDSTAT:

        break;
    case CONST:

        break;
    case ADD:

        break;
    case SUBTR:

        break;
    case LESS:

        break;
    case MULT:

        break;
    case IF:

        break;
    case ELIF:

        break;
    case DIV:

        break;
    case ELSE:

        break;
    case MORE:

        break;
    case WHILE:

        break;
    case PROCD:

        break;
    case SCOPE:

        break;
    case ENDSCOPE:

        break;
    case EMPTY:

        break;
    case SEQ:

        break;
    case EXPR:

        break;
    case PROG:

        break;
    default:
        break;
    }
}

void program_start()
{

}
