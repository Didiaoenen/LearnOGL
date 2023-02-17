#pragma once

#include <vector>
#include <memory>

namespace ll
{

    class BaseApplication;

class ApplicationManager
{
public:
    static ApplicationManager* GetInstance();

    using ApplicationPtr = std::shared_ptr<BaseApplication>;

    template <class T>
    std::enable_if_t<std::is_base_of<BaseApplication, T>::value, ApplicationPtr> CreateApplication() 
    {
        ApplicationPtr app = std::make_shared<T>();
        _apps.push_back(app);
        _currentApp = app;
        return app;
    }

    void ReleseAllApplications();
    ApplicationPtr GetCurrentApp() const;
    ApplicationPtr GetCurrentAppSafe() const;

private:
    std::weak_ptr<BaseApplication> _currentApp;
    std::vector<ApplicationPtr> _apps;
};

}

#define CC_APPLICATION_MANAGER()        ll::ApplicationManager::GetInstance()
#define CC_CURRENT_APPLICATION()        CC_APPLICATION_MANAGER()->GetCurrentApp()
#define CC_CURRENT_APPLICATION_SAFE()   CC_APPLICATION_MANAGER()->GetCurrentAppSafe()
#define CC_CURRENT_ENGINE()             CC_CURRENT_APPLICATION_SAFE()->GetEngine()
#define CC_GET_PLATFORM_INTERFACE(intf) CC_CURRENT_ENGINE()->GetInterface<intf>()
#define CC_GET_XR_INTERFACE() BasePlatform::GetPlatform()->GetInterface<IXRInterface>()

#define CC_START_APPLICATION(className)                                         \
    do                                                                          \
    {                                                                           \
        auto app = CC_APPLICATION_MANAGER()->CreateApplication<className>();    \
        if (app->Init())                                                        \
        {                                                                       \
            return -1;                                                          \
        }                                                                       \
        return app->Run(argc, argv);                                            \
    } while (0)

#define CC_REGISTER_APPLICATION(className)          \
    int cocos_main(int argc, const char** argv)     \
    {                                               \
        CC_START_APPLICATION(className);            \
    }
