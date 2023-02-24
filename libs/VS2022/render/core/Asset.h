#pragma once

#include "../base/Macros.h"

#include "Object.h"

namespace ll
{

class Asset : public Object
{
public:
    using Super = Object;

    Asset();
    ~Asset() override;

    virtual void OnLoaded() {}

    bool Destroy() override;

protected:
    void SetRawAsset(const std::string& filename, bool inLibrary = true);

public:
    std::string _native;
    std::string _nativeUrl;

protected:
    bool _loaded{ true };
    bool _isDefault{ false };

    DISALLOW_COPY_MOVE_ASSIGN(Asset)
};

}