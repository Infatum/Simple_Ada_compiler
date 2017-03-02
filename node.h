#ifndef NODE_H
#define NODE_H
#include <vector>
#include <array>

template <class TKey, class TValue>
class Node
{
private:
    TKey *kind;
    TValue *value;
    Node *left;
    Node *right;
    std::vector<TKey> operators;

public:
    Node() { }
    explicit Node(const TKey &kind, const TValue &val = nullptr, const std::vector<TKey, TValue> &ar = nullptr)
    {
        this->kind = kind;
        if (val != nullptr) {
            this->value = val;
        }
        if (ar != nullptr) {
            this->operators.assign(ar.begin(), ar.end());
        }
    }

    void set_val(const TValue &val)
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
    virtual ~Node();
};

#endif // NODE_H
