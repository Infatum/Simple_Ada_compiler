#ifndef BASENODE_H
#define BASENODE_H
#include <vector>
#include <array>
#include <string>
#include <cassert>
#include "parser.h"
using std::string;
using std::vector;

enum STATE { VAR = 1, SET, ENDSTAT, CONST, ADD, SUBTR, LESS, MULT, IF, ELIF, DIV,
       ELSE, MORE, WHILE, PROCD, SCOPE, ENDSCOPE, EMPTY, SEQ, EXPR, PROG };

template <typename T>
struct BaseNode {
    int type;
    T value;
    BaseNode<T> * parent;
    BaseNode<T> * children;
    int depth;

    BaseNode() {}
    BaseNode(BaseNode<T> * parent = nullptr, BaseNode<T> * children = nullptr)
        : parent(parent), children(children) {}

    virtual ~BaseNode()
    {
        delete parent;
        delete children;
    }
    //virtual T get_type() = 0;
};
#endif // NODE_H
