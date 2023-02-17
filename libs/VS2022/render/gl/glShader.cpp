#include "glShader.h"

ll::glShader::glShader()
{
}

ll::glShader::~glShader()
{
}

ll::GPUShader* ll::glShader::GpuShader() const
{
    if (!_gpuShader->glProgram)
    {
        cmdFuncCreateShader(ll::glDevice::GetInstance(), _gpuShader);

        for (auto &stage : _gpuShader->gpuStages)
        {
            stage.source.clear();
            stage.source.shrink_to_fit();
        }
    }
    return _gpuShader;
}

void ll::glShader::DoInit(const ShaderInfo& info)
{
    _gpuShader = new GPUShader;
    _gpuShader->name = _name;
    _gpuShader->blocks = _blocks;
    _gpuShader->samplerTextures = _samplerTextures;
    _gpuShader->subpassInputs = _subpassInputs;

    for (const auto &stage : _stages)
    {
        _gpuShader->gpuStages.push_back({ stage.stage, stage.source });
    }

    for (auto &state : _stages)
    {
        state.source.clear();
        state.source.shrink_to_fit();
    }
}

void ll::glShader::DoDestroy()
{
}
