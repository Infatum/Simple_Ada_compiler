#ifndef VALUE_TYPE_H
#define VALUE_TYPE_H
#include <string>

struct ValueType {
    union
    {
        int intValue;
        float floatValue;
        double doubleValue;
        std::string stringValue;
    };
};

#endif // VALUE_TYPE_H
