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
    vector<Node<TValue>> child_nodes;

protected:
    set_state(const STATE st)
    {
        state = st;
    }

public:
    Node() : state(EMPTY), value(nullptr), parent(nullptr) { }
    explicit Node(const STATE s, const TValue &v);
    explicit Node(const Node<TValue> &node);
    explicit Node(const STATE s, const Node<TValue> &child, TValue *val = nullptr);
    explicit Node(const STATE s, vector<Node<TValue> > &children,
                  TValue *val = nullptr);

    void set_val(const TValue &val)
    {
        value = val;
    }

    int get_state() const
    {
        return state;
    }

    TValue get_value() const
    {
        return value;
    }

    void add_sibling_node(const Node<TValue> &op)
    {
        op.parent = parent;
        child_nodes.push_back(op);
    }

    void add_parent(const Node<TValue> &parent_n)
    {
        parent = parent_n;
    }

    std::vector<int> get_sibling_nodes() const
    {
        return child_nodes;
    }

    void set_sibling_nodes(const vector<Node<TValue>> &nodes)
    {
        child_nodes = nodes;
    }

    void add_sibling(Node<TValue> &node)
    {
        child_nodes.push_back(node);
    }

    Node<TValue> operator=(const Node &n)
    {
        if (&n != this) {
            delete value, parent;
            child_nodes.clear();
            *value = n.value;
            *parent = Node(n.parent);
            child_nodes = n.child_nodes;
            return *this;
        } else
            return *this;
    }

    virtual ~Node()
    {
        delete state, value, parent;
        child_nodes.clear();
    }
};

template <class TValue>
Node<TValue>::Node(const STATE s, const TValue &v) : state(s), value(v) { }

template <class TValue>
Node<TValue>::Node(const Node<TValue> &node)
{
    if (node.parent != nullptr)
        add_parent(node.parent);
    if (node.child_nodes.size() > 0)
        child_nodes = node.child_nodes;
    if (node.value != nullptr)
        *value = node->value;
}

template <class TValue>
Node<TValue>::Node(const STATE s, const Node<TValue> &child, TValue *val)
    : state(s)
{
    if (val != nullptr) {
        value = *val;
    }
    child_nodes.push_back(add_parent(child));
    child.add_parent(*this);
}

template <class TValue>
Node<TValue>::Node(const STATE s, vector<Node<TValue>> &children,
                   TValue *val) : state(s)
 {
    if (val != nullptr) {
        value = *val;
    }
    if (children.size() > 0)
        child_nodes = children;
    for (auto n : children) {
        n.add_parent(*this);
    }
  }

#endif // NODE_H
