#pragma once

#include <string>

namespace ll
{

class Object
{
public:

    static void DeferredDestroy();

    std::string _name;

    explicit Object(std::string name = "");
    virtual ~Object();

    inline const std::string& GetName() const { return _name; }
    inline void SetName(const std::string& value) { _name = value; }

    inline bool IsValid() const;

    virtual bool Destroy();

    void DestroyImmediate();

    virtual std::string ToString() const { return ""; };
};

inline void Object::DeferredDestroy()
{
}

inline Object::Object(std::string name)
{
}

inline Object::~Object()
{
}

inline bool Object::IsValid() const
{
    return false;
}

inline bool Object::Destroy()
{
    return false;
}

inline void Object::DestroyImmediate()
{

}

bool IsObjectValid(Object* value, bool strictMode = false);
};