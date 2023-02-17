#pragma once

#include "Macros.h"
#include "ISystem.h"

#include <vector>
#include <algorithm>
#include <functional>

namespace ll
{

class BasePlatform
{
public:
    BasePlatform();
    virtual ~BasePlatform();

    static BasePlatform* GetPlatform();
    virtual int32_t Init() = 0;
    virtual int32_t Run(int argc, const char** argv) = 0;
    virtual int32_t Loop() = 0;

    virtual void PollEvent() = 0;

    virtual ISystem::OSType GetOSType() const = 0;
    virtual int32_t GetFps() const = 0;
    virtual void SetFps(int32_t fps) = 0;

    using ThreadCallback = std::function<void(void)>;
    virtual void RunInPlatformThread(const ThreadCallback& task) = 0;

    template <class T>
    std::enable_if_t<std::is_base_of<OSInterface, T>::value, T*> GetInterface() const 
    {
        for (const auto& it : _osInterfaces) 
        {
            T* intf = dynamic_cast<T*>(it.get());
            if (intf) 
            {
                return intf;
            }
        }
        return nullptr;
    }

    template <class T>
    std::enable_if_t<std::is_base_of<OSInterface, T>::value, T*> GetInterface() 
    {
        for (const auto& it : _osInterfaces) 
        {
            T* intf = dynamic_cast<T*>(it.get());
            if (intf) 
            {
                return intf;
            }
        }
        return nullptr;
    }

    bool RegisterInterface(const OSInterface::Ptr& osInterface) 
    {
        auto it = std::find(_osInterfaces.begin(), _osInterfaces.end(), osInterface);
        if (it != _osInterfaces.end()) 
        {
            return false;
        }
        _osInterfaces.push_back(osInterface);
        return true;
    }

    void UnregisterInterface(const OSInterface::Ptr& osInterface) 
    {
        auto it = std::find(_osInterfaces.begin(), _osInterfaces.end(), osInterface);
        if (it != _osInterfaces.end()) 
        {
            return;
        }
        _osInterfaces.erase(it);
    }

    void UnregisterAllInterfaces() 
    {
        _osInterfaces.clear();
    }

private:
    static BasePlatform* CreateDefaultPlatform();

    static BasePlatform* _currentPlatform;
    std::vector<OSInterface::Ptr> _osInterfaces;
    CC_DISALLOW_COPY_MOVE_ASSIGN(BasePlatform)
};

}

#define START_PLATFORM(argc, argv)                                      \
    do                                                                  \
    {                                                                   \
        ll::BasePlatform *platform = ll::BasePlatform::GetPlatform();   \
        if (platform->Init())                                           \
        {                                                               \
            return -1;                                                  \
        }                                                               \
        return platform->Run(argc, argv);                               \
    } while (0)