#ifndef TRANSLATOR_H
#define TRANSLATOR_H
#include "translator.h"
#include "parser.h"

void program_start();

template <typename T>
void start_translation(BaseNode<T> &node);

template <typename T>
void function_signature(BaseNode<T> function_declaration_node);

void function_body(int token_types[], vector<void*> args, void* returnVal);

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

#endif // TRANSLATOR_H
