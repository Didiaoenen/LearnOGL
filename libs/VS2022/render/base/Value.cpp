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

ll::Value& ll::Value::operator=(const Value& other)
{
    // TODO: �ڴ˴����� return ���
    return *this;
}

ll::Value& ll::Value::operator=(Value&& other) noexcept
{
    // TODO: �ڴ˴����� return ���
    return *this;
}

ll::Value& ll::Value::operator=(unsigned char v)
{
    // TODO: �ڴ˴����� return ���
    return *this;
}

ll::Value& ll::Value::operator=(int v)
{
    // TODO: �ڴ˴����� return ���
    return *this;
}

ll::Value& ll::Value::operator=(unsigned int v)
{
    // TODO: �ڴ˴����� return ���
    return *this;
}

ll::Value& ll::Value::operator=(float v)
{
    // TODO: �ڴ˴����� return ���
    return *this;
}

ll::Value& ll::Value::operator=(double v)
{
    // TODO: �ڴ˴����� return ���
    return *this;
}

ll::Value& ll::Value::operator=(bool v)
{
    // TODO: �ڴ˴����� return ���
    return *this;
}

ll::Value& ll::Value::operator=(const char* v)
{
    // TODO: �ڴ˴����� return ���
    return *this;
}

ll::Value& ll::Value::operator=(const std::string& v)
{
    // TODO: �ڴ˴����� return ���
    return *this;
}

ll::Value& ll::Value::operator=(const ValueVector& v)
{
    // TODO: �ڴ˴����� return ���
    return *this;
}

ll::Value& ll::Value::operator=(ValueVector&& v)
{
    // TODO: �ڴ˴����� return ���
    return *this;
}

ll::Value& ll::Value::operator=(const ValueMap& v)
{
    // TODO: �ڴ˴����� return ���
    return *this;
}

ll::Value& ll::Value::operator=(ValueMap&& v)
{
    // TODO: �ڴ˴����� return ���
    return *this;
}

ll::Value& ll::Value::operator=(const ValueMapIntKey& v)
{
    // TODO: �ڴ˴����� return ���
    return *this;
}

ll::Value& ll::Value::operator=(ValueMapIntKey&& v)
{
    // TODO: �ڴ˴����� return ���
    return *this;
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

ll::ValueVector& ll::Value::AsValueVector()
{
    // TODO: �ڴ˴����� return ���
    ValueVector v;
    return v;
}

const ll::ValueVector& ll::Value::AsValueVector() const
{
    // TODO: �ڴ˴����� return ���
    ValueVector v;
    return v;
}

ll::ValueMap& ll::Value::AsValueMap()
{
    // TODO: �ڴ˴����� return ���
    ValueMap v;
    return v;
}

const ll::ValueMap& ll::Value::AsValueMap() const
{
    // TODO: �ڴ˴����� return ���
    ValueMap v;
    return v;
}

ll::ValueMapIntKey& ll::Value::AsIntKeyMap()
{
    // TODO: �ڴ˴����� return ���
    ValueMapIntKey v;
    return v;
}

const ll::ValueMapIntKey& ll::Value::AsIntKeyMap() const
{
    // TODO: �ڴ˴����� return ���
    ValueMapIntKey v;
    return v;
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
