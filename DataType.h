#ifndef DATATYPE_H
#define DATATYPE_H

#include <memory>
#include <string>

using namespace std;

using namespace std;
class DataType {
public:
    virtual ~DataType() = default;

    // Pure virtual function for deep copying
    virtual unique_ptr<DataType> deep_copy() const = 0;

    // Virtual function for string representation
    virtual string to_string() const = 0;
};

#endif // DATATYPE_H
