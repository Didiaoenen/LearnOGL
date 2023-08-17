#pragma once

#include <string>
#include <memory>

#include "SceneObjectBase.h"

#include "Image.h"

using namespace std;

namespace OGL
{
class SceneObjectTexture : public SceneObjectBase
{
public:
    SceneObjectTexture()
    {
    }

    explicit SceneObjectTexture(const string& name)
        : mName(name)
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

    bool mLoaded{ false };
};
}

