#include "Value.h"

ll::Value::Value()
{
}

ll::Value::Value(unsigned char v)
{
}

ll::Value::Value(int v)
{
}

ll::Value::Value(unsigned int v)
{
}

ll::Value::Value(float v)
{
}

ll::Value::Value(double v)
{
}

ll::Value::Value(bool v)
{
}

ll::Value::Value(const char* v)
{
}

ll::Value::Value(const std::string& v)
{
}

ll::Value::Value(const ValueVector& v)
{
}

ll::Value::Value(ValueVector&& v)
{
}

ll::Value::Value(const ValueMap& v)
{
}

ll::Value::Value(ValueMap&& v)
{
}

ll::Value::Value(const ValueMapIntKey& v)
{
}

ll::Value::Value(ValueMapIntKey&& v)
{
}

ll::Value::Value(const Value& other)
{
}

ll::Value::Value(Value&& other) noexcept
{
}

ll::Value::~Value()
{
}

`Value& ll::Value::operator=(const Value& other)
{
    // TODO: 在此处插入 return 语句
}

Value& ll::Value::operator=(Value&& other) noexcept
{
    // TODO: 在此处插入 return 语句
}

Value& ll::Value::operator=(unsigned char v)
{
    // TODO: 在此处插入 return 语句
}

Value& ll::Value::operator=(int v)
{
    // TODO: 在此处插入 return 语句
}

Value& ll::Value::operator=(unsigned int v)
{
    // TODO: 在此处插入 return 语句
}

Value& ll::Value::operator=(float v)
{
    // TODO: 在此处插入 return 语句
}

Value& ll::Value::operator=(double v)
{
    // TODO: 在此处插入 return 语句
}

Value& ll::Value::operator=(bool v)
{
    // TODO: 在此处插入 return 语句
}

Value& ll::Value::operator=(const char* v)
{
    // TODO: 在此处插入 return 语句
}

Value& ll::Value::operator=(const std::string& v)
{
    // TODO: 在此处插入 return 语句
}

Value& ll::Value::operator=(const ValueVector& v)
{
    // TODO: 在此处插入 return 语句
}

Value& ll::Value::operator=(ValueVector&& v)
{
    // TODO: 在此处插入 return 语句
}

Value& ll::Value::operator=(const ValueMap& v)
{
    // TODO: 在此处插入 return 语句
}

Value& ll::Value::operator=(ValueMap&& v)
{
    // TODO: 在此处插入 return 语句
}

Value& ll::Value::operator=(const ValueMapIntKey& v)
{
    // TODO: 在此处插入 return 语句
}

Value& ll::Value::operator=(ValueMapIntKey&& v)
{
    // TODO: 在此处插入 return 语句
}

bool ll::Value::operator!=(const Value& v)
{
    return false;
}

bool ll::Value::operator!=(const Value& v) const
{
    return false;
}

bool ll::Value::operator==(const Value& v)
{
    return false;
}

bool ll::Value::operator==(const Value& v) const
{
    return false;
}

unsigned char ll::Value::AsByte() const
{
    return 0;
}

int ll::Value::AsInt() const
{
    return 0;
}

unsigned int ll::Value::AsUnsignedInt() const
{
    return 0;
}

float ll::Value::AsFloat() const
{
    return 0.0f;
}

double ll::Value::AsDouble() const
{
    return 0.0;
}

bool ll::Value::AsBool() const
{
    return false;
}

std::string ll::Value::AsString() const
{
    return std::string();
}

ValueVector& ll::Value::AsValueVector()
{
    // TODO: 在此处插入 return 语句
}

const ValueVector& ll::Value::AsValueVector() const
{
    // TODO: 在此处插入 return 语句
}

ValueMap& ll::Value::AsValueMap()
{
    // TODO: 在此处插入 return 语句
}

const ValueMap& ll::Value::AsValueMap() const
{
    // TODO: 在此处插入 return 语句
}

ValueMapIntKey& ll::Value::AsIntKeyMap()
{
    // TODO: 在此处插入 return 语句
}

const ValueMapIntKey& ll::Value::AsIntKeyMap() const
{
    // TODO: 在此处插入 return 语句
}

std::string ll::Value::GetDescription() const
{
    return std::string();
}

void ll::Value::Clear()
{
}

void ll::Value::Reset(Type type)
{
}
