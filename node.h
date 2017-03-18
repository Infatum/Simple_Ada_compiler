#ifndef NODE_H
#define NODE_H
#include <cstddef>
#include "basenode.h"

template <class... Args>
struct node;

template <typename Root, typename... Leaf>
struct node<Root, Leaf...> : node<Leaf...>
{
    //Recursively instantiating and initializing each node of the tree(starting with a root node and moving on)
    node(Root h, Leaf... tail) : node<Leaf...>(tail...), Root(h)
    {}

    typedef node<Leaf...>  current_node;
    typedef Root           root_node;

    current_node &node_ = static_cast<root_node&>(*this);
    Root    root;
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
           typedef typename node<Root, Args...>::value_type return_type;
           static return_type get(node<Root, Args...> t)
           {
               return t.head_;
           }
       };

template<int I, typename Root, typename... Args>
    typename getter<I, Root, Args...>::return_type
    get(tuple<Root, Args...> t)
    {
       return getter<I, Root, Args...>::get(t);
    }
#endif // NODE_H
