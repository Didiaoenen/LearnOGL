#pragma once

#include "Shader.h"
#include "glDevice.h"
#include "glObjects.h"
#include "glCommands.h"

namespace ll
{

struct GPUShader;

class glShader final : public Shader
{
public:
    glShader();
    ~glShader() override;

    GPUShader* GpuShader() const;

private:
    void DoInit(const ShaderInfo& info) override;
    void DoDestroy() override;

    GPUShader* _gpuShader = nullptr;

};

}
