#pragma once

namespace OGL
{
class BaseSceneObject 
{
public:
    BaseSceneObject() = default;

    BaseSceneObject(int type) 
        : mType(type) 
    {
    };
    BaseSceneObject(BaseSceneObject&& obj) noexcept 
        : mType(obj.mType) 
    {
    };
    virtual ~BaseSceneObject() = default;


protected:
    int mType;
};

}