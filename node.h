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
//    explicit Node(const int &k, const Node &parent_n, TValue *val = nullptr);

//    explicit Node(const int &k, const Node &parent_n, vector<Node<int,TValue>> siblings,
//                  TValue *val = nullptr);

//    explicit Node(const int &k, vector<Node<int,TValue>> sibling_ns, TValue *val = nullptr);

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

    void ass_sibling_node(const Node<TValue> &op)
    {
        op.parent = parent;
        sibling_nodes.push_back(op);
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

    virtual ~Node()
    {
        delete kind, value, parent;
        sibling_nodes.clear();
    }
};

template <class TValue>
Node<TValue>::Node(const int k, const TValue &v) : kind(k), value(v) { }

//template <class int, class TValue>
//Node<int,TValue>::Node(const Node<int, TValue> &node)
//{
//    if (node.parent != nullptr) {
//        this->parent = node.parent;
//    }
//}

/*template <class int, class TValue>
Node<int,TValue>::Node(const int &k, const Node &parent_n, TValue *val)
    : kind(k), parent(parent_n)
{
    if (val != nullptr) {
        this->*value = *val;
    }
}
template <class int, class TValue>
Node<int,TValue>::Node(const int &k, const Node &parent_n, vector<Node<int,TValue>> siblings,
TValue *val) : kind(k), parent(parent_n), sibling_nodes(siblings)
{
    if (val != nullptr) {
        this->*value = *val;
    }
}
template <class int, class TValue>
Node<int,TValue>::Node(const int &k, vector<Node<int,TValue>> sibling_ns, TValue *val)
    : kind(k), sibling_nodes(sibling_ns)
{
     if (val != nullptr) {
        *value = *val;
    }
}*/

#endif // NODE_H
