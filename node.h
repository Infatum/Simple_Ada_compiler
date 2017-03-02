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
    std::vector<TKey, TValue> operators;

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

    virtual ~Node();
};

#endif // NODE_H
