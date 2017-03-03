#include "translator.h"
#include "parser.h"

void start_translation();

template <typename T>
T translate_function();

template <typename T>
bool translate_relational_operation(T lval, T rval);

template <typename T>
void translate_loop(int start, int end, T &obj);

template <typename T>
T assign_operation(T &lval, const T &rval);

template <typename T>
T translate_statement(int operator_type, T &lval, vector<T> rvals);
