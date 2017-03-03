#ifndef NODE_H
#define NODE_H
#include <vector>
#include <unordered_map>
#include <array>
#include <string>
#include <cassert>
using std::string;
using std::unordered_map;
using std::vector;

template <class TValue>
class Node
{
private:
    typedef unordered_map<int,string> unord_map;
    int kind;
    TValue *value;
    Node *parent;
    vector<Node<TValue>> child_nodes;

public:
    Node() : value(nullptr), parent(nullptr) { }

    explicit Node(const int k, const TValue &s);

    explicit Node(const Node<TValue> &node);
    explicit Node(const int &k, const Node<TValue> &child, TValue *val = nullptr);

    explicit Node(const int &k, vector<Node<TValue> > &children,
                  TValue *val = nullptr);

    void set_val(const TValue &val)
    {
        value = val;
    }

    void set_kind(const int &k)
    {
        kind = k;
    }

    int get_kind() const
    {
        return kind;
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
        delete kind, value, parent;
        child_nodes.clear();
    }
};

template <class TValue>
Node<TValue>::Node(const int k, const TValue &v) : kind(k), value(v) { }

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
Node<TValue>::Node(const int &k, const Node<TValue> &child, TValue *val)
    : kind(k)
{
    if (val != nullptr) {
        value = *val;
    }
    child_nodes.push_back(add_parent(child));
    child.add_parent(*this);
}

template <class TValue>
Node<TValue>::Node(const int &k, vector<Node<TValue>> &children,
                   TValue *val) : kind(k)
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
