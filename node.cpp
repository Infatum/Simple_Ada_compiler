#include "node.h"

Node::~Node()
{
    delete kind, value, left, right;
    operators.clear();
}
