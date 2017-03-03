#ifndef NODE_H
#define NODE_H
#include <vector>
#include <unordered_map>
#include <array>

template <class TKey, class TValue, class V = std::vector<TKey, TValue>>
class Node
{
private:
    TKey *kind;
    TValue *value;
    Node *parent;
    std::vector<Node> sibling_nodes;
    std::unordered_map<TKey,TValue> operators;

public:
    Node() { }
    Node(const TKey &kind, const TValue &val = nullptr,
         const std::unordered_map<TKey, TValue> &op = std::unordered_map<TKey,TValue>())
    {
        this->kind = kind;
        if (val != nullptr) {
            this->value = val;
        }
        if (op.size() > 0) {
            this->operators = op;
        }
    }

    Node(const TKey &kind, const Node &n, const TValue &val = nullptr,
         const std::unordered_map<TKey, TValue> &op = std::unordered_map<TKey,TValue>())
        : kind(kind), parent(n)
    {
        if (val != nullptr) {
            this->value = val;
        } if (op.size() > 0) {
            operators = op;
        }
    }

    Node(const TKey &kind, const std::vector &sn = {}, const TValue &val = nullptr,
         const std::unordered_map<TKey, TValue> &op = std::unordered_map<TKey,TValue>())
        : kind(kind)
    {
        if (sn.size() > 0) {
            sibling_nodes = sn;
        } if (val != nullptr) {
            value = val;
        } if (op.size() > 0) {
           op.size();
        }
    }

    void set_val(const TValue &sn )
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

#endif // NODE_H
