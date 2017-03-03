#ifndef NODE_H
#define NODE_H
#include <vector>
#include <unordered_map>
#include <array>
#include <string>
using std::string;
using std::unordered_map;
using std::vector;

template <class TKey, class TValue>
class Node
{
private:
    typedef unordered_map<int,string> unord_map;
    TKey *kind;
    TValue *value;
    Node *parent;
    vector<Node> sibling_nodes;
    unordered_map<TKey,TValue> operators;

public:
    Node() { }

    explicit Node(const TKey &, const TValue &);

    explicit Node(const TKey &k, TValue &val = nullptr,
          unord_map &op = unord_map());

    explicit Node(const TKey &k, const Node &n, TValue &val = nullptr,
          unord_map &op = unord_map());

    explicit Node(const TKey &kind, std::vector<Node> &sn = {}, TValue &val = nullptr,
          unord_map &op = unord_map());

    explicit Node(const TKey &k, const Node &n, TValue &val = nullptr);

    void set_val(const TValue &val )
    {
        value = val;
    }

    void set_kind(const TKey &k)
    {
        kind = k;
    }

    TKey get_kind() const
    {
        return kind;
    }

    TValue get_value() const
    {
        return value;
    }

    void add_operator(const TKey &op)
    {
        operators.push_back(op);
    }

    std::vector<TKey> get_operators() const
    {
        return operators;
    }

    virtual ~Node()
    {
        delete kind, value, parent;
        operators.clear();
    }
};

template <class TKey, class TValue>
Node<TKey,TValue>::Node(const TKey &k, TValue &val, unord_map &op) : kind(k)
{
    this->kind = k;
    if (val != nullptr) {
        this->value = val;
    }
    if (op.size() > 0) {
        this->operators = op;
    }
}
template <class TKey, class TValue>
Node<TKey,TValue>::Node(const TKey &k, const Node &n, TValue &val, unord_map &op)
    : kind(k), parent(n)
{
    kind = k;
    parent = n;
    if (val != nullptr) {
        this->value = val;
    } if (op.size() > 0) {
        operators = op;
    }
}
template <class TKey, class TValue>
Node<TKey,TValue>::Node(const TKey &kind, std::vector<Node> &sn, TValue &val, unord_map &op)
    : kind(kind)
{
    this->kind = kind;
    if (sn.size() > 0) {
        sibling_nodes = sn;
    } if (val != nullptr) {
        value = val;
    } if (op.size() > 0) {
       op.size();
    }
}

template <class TKey, class TValue>
Node<TKey,TValue>::Node(const TKey &k, const Node &n, TValue &val) : kind(k), parent(n)
{
    if (val != nullptr)
        value = val;
}

template <class TKey, class TValue>
Node<TKey,TValue>::Node(const TKey &k, const TValue &v) : kind(k), value(v) { }
#endif // NODE_H
