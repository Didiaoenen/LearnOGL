#pragma once

#include <string>

namespace ll
{

enum class CmdType : uint8_t 
{
    BEGIN_RENDER_PASS,
    END_RENDER_PASS,
    BIND_STATES,
    DRAW,
    UPDATE_BUFFER,
    COPY_BUFFER_TO_TEXTURE,
    BLIT_TEXTURE,
    DISPATCH,
    BARRIER,
    QUERY,
    COUNT,
};

class Cmd 
{
public:
    CmdType type;
    uint32_t refCount = 0;

    explicit Cmd(CmdType type) : type(type) {}
    virtual ~Cmd() = default;

    virtual void clear() = 0;
};

enum class MSRTSupportLevel 
{
    NONE,
    LEVEL1,
    LEVEL2,
};

enum class FBFSupportLevel 
{
    NONE,
    COHERENT,
    NON_COHERENT_EXT,
    NON_COHERENT_QCOM,
};

template <typename T, typename = std::enable_if_t<std::is_base_of<Cmd, T>::value>>
class CommandPool 
{
public:
    CommandPool() : _freeCmds(GLES_COMMAND_POOL_INITIAL_CAPACITY) 
    {
        _frees = ccnew T * [GLES_COMMAND_POOL_INITIAL_CAPACITY];
        _count = GLES_COMMAND_POOL_INITIAL_CAPACITY;
        _freeIdx = GLES_COMMAND_POOL_INITIAL_CAPACITY - 1;
        for (uint32_t i = 0; i < _count; ++i) 
        {
            _frees[i] = ccnew T;
        }
    }

    ~CommandPool() 
    {
        for (uint32_t i = 0; i < _count; ++i) 
        {
            delete _frees[i];
        }
        delete[](_frees);

        for (uint32_t i = 0; i < _freeCmds.size(); ++i) 
        {
            delete _freeCmds[i];
        }
        _freeCmds.clear();
    }

    T* Alloc() 
    {
        if (_freeIdx < 0) 
        {
            T** oldFrees = _frees;
            uint32_t size = _count * 2;
            _frees = ccnew T * [size];
            uint32_t increase = size - _count;
            for (uint32_t i = 0; i < increase; ++i) 
            {
                _frees[i] = ccnew T;
            }
            for (uint32_t i = increase, j = 0; i < size; ++i, ++j) 
            {
                _frees[i] = oldFrees[j];
            }
            delete[](oldFrees);

            _count = size;
            _freeIdx += static_cast<int>(increase);
        }

        T* cmd = _frees[_freeIdx];
        _frees[_freeIdx--] = nullptr;
        ++cmd->refCount;
        return cmd;
    }

    void Free(T* cmd) 
    {
        if (--cmd->refCount == 0) 
        {
            _freeCmds.push(cmd);
        }
    }

    void FreeCmds(CachedArray<T*>& cmds) 
    {
        for (uint32_t i = 0; i < cmds.size(); ++i) 
        {
            if (--cmds[i]->refCount == 0) 
            {
                _freeCmds.push(cmds[i]);
            }
        }
        cmds.clear();
    }

    void Release() 
    {
        for (uint32_t i = 0; i < _freeCmds.size(); ++i) 
        {
            T* cmd = _freeCmds[i];
            cmd->clear();
            _frees[++_freeIdx] = cmd;
        }
        _freeCmds.clear();
    }

protected:
    T** _frees = nullptr;
    uint32_t _count = 0;
    CachedArray<T*> _freeCmds;
    int _freeIdx = 0;
};

struct BindingMapping 
{
    std::vector<int32_t> blockOffsets;
    std::vector<int32_t> samplerTextureOffsets;
    uint32_t flexibleSet{ 0 };
};

}