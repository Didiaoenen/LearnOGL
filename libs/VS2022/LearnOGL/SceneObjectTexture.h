#pragma once

#include <string>
#include <memory>

#include "BaseSceneObject.h"

#include "Image.h"

using namespace std;

namespace OGL
{
class SceneObjectTexture : public BaseSceneObject
{
public:
    SceneObjectTexture()
        : BaseSceneObject(0) 
    {
    }

    explicit SceneObjectTexture(const string& name)
        : BaseSceneObject(0), mName(name)
    {
    }

    bool LoadTexture();
    shared_ptr<Image> GetTextureImage();

public:
    string mName;
    shared_ptr<Image> mImage;

    bool mHDR;
    bool mFlip;
    bool mGammaCorrection;

    bool mLoaded;
};
}

