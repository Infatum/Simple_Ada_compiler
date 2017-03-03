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
    vector<Node<TValue>> sibling_nodes;

public:
    Node() { }

    explicit Node(const int k, const TValue &s);

    explicit Node(const Node<TValue> &node);
    explicit Node(const int &k, const Node<TValue> &parent_n, TValue *val = nullptr);

    explicit Node(const int &k, const Node &parent_n, vector<Node<TValue>> siblings,
                  TValue *val = nullptr);

    explicit Node(const int &k, vector<Node<TValue>> sibling_ns, TValue *val = nullptr);

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
        sibling_nodes.push_back(op);
    }

    void add_parent(const Node<TValue> &parent_n)
    {

    }

    std::vector<int> get_sibling_nodes() const
    {
        return sibling_nodes;
    }

    void set_sibling_nodes(const vector<Node<TValue>> &nodes)
    {
        sibling_nodes = nodes;
    }

    void add_sibling(Node<TValue> &node)
    {
        sibling_nodes.push_back(node);
    }

    Node<TValue> operator=(const Node &n)
    {
        if (&n != this) {
            delete value, parent;
            sibling_nodes.clear();
            *value = n.value;
            *parent = Node(n.parent);
            sibling_nodes = n.sibling_nodes;
            return *this;
        } else
            return *this;
    }

    virtual ~Node()
    {
        delete kind, value, parent;
        sibling_nodes.clear();
    }
};

template <class TValue>
Node<TValue>::Node(const int k, const TValue &v) : kind(k), value(v) { }

template <class TValue>
Node<TValue>::Node(const Node<TValue> &node)
{
    if (node.parent != nullptr)
        add_parent(node.parent);
    if (node.sibling_nodes.size() > 0)
        sibling_nodes = node.sibling_nodes;
    if (node.value != nullptr)
        *value = node->value;
}

template <class TValue>
Node<TValue>::Node(const int &k, const Node<TValue> &parent_n, TValue *val)
    : kind(k)
{
    if (val != nullptr) {
        //this->value = *val;
    }
}

template <class TValue>
Node<TValue>::Node(const int &k, const Node &parent_n, vector<Node<TValue>> siblings,
                   TValue *val) : kind(k)
 {
    if (val != nullptr) {
        value = *val;
    } if (parent_n.parent != nullptr)
        parent.add_parent(parent_n.n);
    if (siblings.size() > 0)
        sibling_nodes = siblings;
  }


#endif // NODE_H
