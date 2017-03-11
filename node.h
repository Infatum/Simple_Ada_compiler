#ifndef NODE_H
#define NODE_H
#include <vector>
#include <array>
#include <string>
#include <cassert>
#include "parser.h"
using std::string;
using std::vector;

enum STATE { VAR = 1, SET, ENDSTAT, CONST, ADD, SUBTR, LESS, MULT, IF, ELIF, DIV,
       ELSE, MORE, WHILE, PROCD, SCOPE, ENDSCOPE, EMPTY, SEQ, EXPR, PROG };

template <class TValue>
class Node
{
private:
    STATE state;
    TValue *value;
    Node *parent;
    vector<Node<TValue>> child_node_operators;

protected:
    set_state(const STATE st)
    {
        state = st;
    }

public:
    //Node() : state(EMPTY), value(nullptr), parent(nullptr) { }
    Node(STATE s, TValue &val = nullptr, vector<Node<TValue>> &children = { }):
        state(s), value(val), child_node_operators(children) { }

    Node(const Node<TValue> &n)
    {
        delete parent, value;
        child_node_operators.clear();
        state = n.state;

    }

    int get_state() const
    {
        return state;
    }

    TValue get_value() const
    {
        return value;
    }

    std::vector<int> get_children_nodes() const
    {
        return child_node_operators;
    }

    Node<TValue> operator=(const Node &n)
    {
        if (&n != this) {
            delete value, parent;
            child_node_operators.clear();
            *value = n.value;
            *parent = Node(n.parent);
            child_node_operators = n.child_node_operators;
            return *this;
        } else
            return *this;
    }

    virtual ~Node()
    {
        delete value, parent;
        child_node_operators.clear();
    }
};

#endif // NODE_H
