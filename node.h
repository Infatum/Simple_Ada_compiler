#ifndef NODE_H
#define NODE_H
#include <cstddef>
#include "basenode.h"

enum STATE { VAR = 1, SET, ENDSTAT, CONST, ADD, SUBTR, LESS, MULT, IF, ELIF, DIV,
       ELSE, MORE, WHILE, PROCD, SCOPE, ENDSCOPE, EMPTY, SEQ, EXPR, PROG };

namespace AST {
template <class... Args>
struct node;

template <typename Root, typename... Leaf>
struct node<Root, Leaf...> : node<Leaf...>
{
    node() {}
    //node(Root r) : root(r) {}
    //Recursively instantiating and initializing each node of the tree(starting with a root node and moving on)
    node(Root h, Leaf... tail) : node<Leaf...>(tail...), root(h)
    {}
    node(const node<Root, Leaf...> &t) {}

    typedef node<Leaf...>  current_node;
    typedef Root           root_node;

    current_node &node_ = static_cast<current_node&>(*this);
    Root    root;

    node<Root, Leaf...>& operator=(const node<Root, Leaf...>&n)
    {
        *this = node<Root, Leaf...>(n);
    }
};

template<>
struct node<>
{};

template<int I, typename Root, typename... Args>
    struct getter
    {
        typedef typename getter<I-1, Args...>::return_type return_type;

        static return_type get(node<Root, Args...> t)
        {
            return getter<I-1, Args...>::get(t);
        }
    };

template<typename Root, typename... Args>
    struct getter<0, Root, Args...>
       {
           typedef typename node<Root, Args...>::root_node return_type;

           static return_type get(node<Root, Args...> t)
           {
               return t.root;
           }
       };

template<int I, typename Root, typename... Args>
typename getter<I, Root, Args...>::return_type
    get(node<Root, Args...> t)
    {
       return getter<I, Root, Args...>::get(t);
    }
}
#endif // NODE_H
