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


#define APPLICATION_MANAGER()        ApplicationManager::GetInstance()
#define CURRENT_APPLICATION()        APPLICATION_MANAGER()->GetCurrentApp()
#define CURRENT_APPLICATION_SAFE()   APPLICATION_MANAGER()->GetCurrentAppSafe()
#define CURRENT_ENGINE()             CURRENT_APPLICATION_SAFE()->GetEngine()

#define START_APPLICATION(className)                                            \
    do                                                                          \
    {                                                                           \
        auto app = APPLICATION_MANAGER()->CreateApplication<className>();       \
        if (app->Init())                                                        \
        {                                                                       \
            return -1;                                                          \
        }                                                                       \
        return app->Run(argc, argv);                                            \
    } while (0)

#define REGISTER_APPLICATION(className)             \
    int _Init(int argc, char* argv[])               \
    {                                               \
        START_APPLICATION(className);               \
    }

}