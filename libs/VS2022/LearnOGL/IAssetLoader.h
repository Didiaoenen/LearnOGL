#pragma once

#include <string>

#include "IRuntimeModule.h"

#include "Buffer.h"

using namespace std;

namespace OGL
{
class IAssetLoader : public IRuntimeModule
{
public:
    IAssetLoader() = default;
    virtual ~IAssetLoader() = default;
    using AssetFilePtr = void*;

    enum AssetOpenMode 
    {
        OPEN_TEXT = 0,    
        OPEN_BINARY = 1,  
    };

    enum AssetSeekBase 
    {
        SET = 0,
        CUR = 1,
        END = 2,
    };

    virtual bool AddSearchPath(const char* path) = 0;

    virtual bool RemoveSearchPath(const char* path) = 0;

    virtual void ClearSearchPath() = 0;

    virtual bool FileExists(const char* filePath) = 0;

    virtual AssetFilePtr OpenFile(const char* name, AssetOpenMode mode) = 0;

    virtual Buffer SyncOpenAndReadText(const char* filePath) = 0;

    virtual Buffer SyncOpenAndReadBinary(const char* filePath) = 0;

    virtual string SyncOpenAndReadTextFileToString(const char* fileName) = 0;

    virtual size_t SyncRead(const AssetFilePtr& fp, Buffer& buf) = 0;

    virtual void CloseFile(AssetFilePtr& fp) = 0;

    virtual size_t GetSize(const AssetFilePtr& fp) = 0;

    virtual int32_t Seek(AssetFilePtr fp, long offset, AssetSeekBase where) = 0;
};
}
