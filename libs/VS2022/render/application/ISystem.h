#pragma once

#include "OSInterface.h"

#include <string>

namespace ll
{

class ISystem : public OSInterface
{
public:
    ~ISystem() override = default;

    enum class LanguageType 
    {
        ENGLISH = 0,
        CHINESE,
        FRENCH,
        ITALIAN,
        GERMAN,
        SPANISH,
        DUTCH,
        RUSSIAN,
        KOREAN,
        JAPANESE,
        HUNGARIAN,
        PORTUGUESE,
        ARABIC,
        NORWEGIAN,
        POLISH,
        TURKISH,
        UKRAINIAN,
        ROMANIAN,
        BULGARIAN
    };
    enum class OSType 
    {
        WINDOWS,
    };

    virtual OSType GetOSType() const = 0;
    virtual std::string GetDeviceModel() const = 0;
    virtual LanguageType GetCurrentLanguage() const = 0;
    virtual std::string GetCurrentLanguageCode() const = 0;
    virtual std::string GetCurrentLanguageToString() = 0;
    virtual bool OpenURL(const std::string& url) = 0;
};

}