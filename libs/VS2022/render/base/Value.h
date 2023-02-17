#pragma once

#include <string>
#include <vector>
#include <unordered_map>

namespace ll 
{

class Value;

using ValueVector = std::vector<Value>;
using ValueMap = std::unordered_map<std::string, Value>;
using ValueMapIntKey = std::unordered_map<int, Value>;

extern const ValueMap VALUE_MAP_NULL;
extern const ValueVector VALUE_VECTOR_NULL;
extern const ValueMapIntKey VALUE_MAP_INT_KEY_NULL;

class Value 
{
public:
    static const Value VALUE_NULL;

    Value();

    explicit Value(unsigned char v);
    explicit Value(int v);
    explicit Value(unsigned int v);
    explicit Value(float v);
    explicit Value(double v);
    explicit Value(bool v);
    explicit Value(const char* v);
    explicit Value(const std::string& v);
    explicit Value(const ValueVector& v);
    explicit Value(ValueVector&& v);
    explicit Value(const ValueMap& v);
    explicit Value(ValueMap&& v);
    explicit Value(const ValueMapIntKey& v);
    explicit Value(ValueMapIntKey&& v);

    Value(const Value& other);
    Value(Value&& other) noexcept;

    ~Value();

    Value& operator=(const Value& other);
    Value& operator=(Value&& other) noexcept;

    Value& operator=(unsigned char v);
    Value& operator=(int v);
    Value& operator=(unsigned int v);
    Value& operator=(float v);
    Value& operator=(double v);
    Value& operator=(bool v);
    Value& operator=(const char* v);
    Value& operator=(const std::string& v);

    Value& operator=(const ValueVector& v);
    Value& operator=(ValueVector&& v);

    Value& operator=(const ValueMap& v);
    Value& operator=(ValueMap&& v);

    Value& operator=(const ValueMapIntKey& v);
    Value& operator=(ValueMapIntKey&& v);

    bool operator!=(const Value& v);
    bool operator!=(const Value& v) const;
    bool operator==(const Value& v);
    bool operator==(const Value& v) const;

    unsigned char AsByte() const;
    int AsInt() const;
    unsigned int AsUnsignedInt() const;
    float AsFloat() const;
    double AsDouble() const;
    bool AsBool() const;
    std::string AsString() const;

    ValueVector& AsValueVector();
    const ValueVector& AsValueVector() const;

    ValueMap& AsValueMap();
    const ValueMap& AsValueMap() const;

    ValueMapIntKey& AsIntKeyMap();
    const ValueMapIntKey& AsIntKeyMap() const;

    inline bool IsNull() const { return _type == Type::NONE; }

    enum class Type 
    {
        NONE = 0,
        BYTE,
        INTEGER,
        UNSIGNED,
        FLOAT,
        DOUBLE,
        BOOLEAN,
        STRING,
        VECTOR,
        MAP,
        INT_KEY_MAP
    };

    inline Type GetType() const { return _type; }

    std::string GetDescription() const;

private:
    void Clear();
    void Reset(Type type);

    union 
    {
        unsigned char byteVal;
        int intVal;
        unsigned int unsignedVal;
        float floatVal;
        double doubleVal;
        bool boolVal;

        std::string* strVal;
        ValueVector* vectorVal;
        ValueMap* mapVal;
        ValueMapIntKey* intKeyMapVal;
    } _field;

    Type _type;
};

}