#pragma once

#include <string>
#include <vector>

#include "IAssetLoader.h"

using namespace std;

namespace OGL
{
class AssetLoader : public IAssetLoader
{
public:
	AssetLoader() = default;
	~AssetLoader() override = default;

    bool Initialize() override;
    void Finalize() override {}
    void Tick() override {}

    bool AddSearchPath(const char* path) override;

    bool RemoveSearchPath(const char* path) override;

    void ClearSearchPath() override;

    string GetFileRealPath(const char* filePath);

    bool FileExists(const char* filePath) override;

    AssetFilePtr OpenFile(const char* name, AssetOpenMode mode) override;

    Buffer SyncOpenAndReadText(const char* filePath) override;

    Buffer SyncOpenAndReadBinary(const char* filePath) override;

    size_t SyncRead(const AssetFilePtr& fp, Buffer& buf) override;

    void CloseFile(AssetFilePtr& fp) override;

    size_t GetSize(const AssetFilePtr& fp) override;

    int32_t Seek(AssetFilePtr fp, long offset, AssetSeekBase where) override;

    inline string SyncOpenAndReadTextFileToString(const char* fileName) override 
    {
        string result;
        Buffer buffer = SyncOpenAndReadText(fileName);
        if (buffer.GetDataSize()) 
        {
            char* content = reinterpret_cast<char*>(buffer.GetData());

            if (content) 
            {
                result = string(content);
            }
        }

        return result;
    }

protected:
    static string mTargetPath;

private:
    static vector<string> mSearchPath;
};
}

