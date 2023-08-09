#include "AssetLoader.h"

using namespace OGL;

string AssetLoader::mTargetPath;

vector<string> AssetLoader::mSearchPath;

bool AssetLoader::Initialize()
{
    AddSearchPath("./../../../");
    return true;
}

bool AssetLoader::AddSearchPath(const char* path)
{
    auto src = mSearchPath.begin();

    while (src != mSearchPath.end()) 
    {
        if (*src == path) return true;
        src++;
    }
    mSearchPath.emplace_back(path);

    return true;
}

bool AssetLoader::RemoveSearchPath(const char* path)
{
    auto src = mSearchPath.begin();

    while (src != mSearchPath.end()) 
    {
        if (*src == path) {
            mSearchPath.erase(src);
            return true;
        }
        src++;
    }

    return true;
}

void AssetLoader::ClearSearchPath()
{
    mSearchPath.clear();
}

string AssetLoader::GetFileRealPath(const char* filePath)
{
    return string();
}

bool AssetLoader::FileExists(const char* filePath)
{
    AssetFilePtr fp = OpenFile(filePath, OPEN_BINARY);
    if (fp != nullptr) 
    {
        CloseFile(fp);
        return true;
    }
    return false;
}

IAssetLoader::AssetFilePtr AssetLoader::OpenFile(const char* name, AssetOpenMode mode)
{
    FILE* fp = nullptr;
    string upPath(mTargetPath);
    
    string fullPath;
    for (int32_t i = 0; i < 10; i++) 
    {
        auto src = mSearchPath.begin();
        bool looping = true;
        while (looping) 
        {
            fullPath.assign(upPath);
            if (src != mSearchPath.end()) 
            {
                fullPath.append(*src);
                //fullPath.append("Asset/");
                src++;
            }
            else 
            {
                //fullPath.append("Asset/");
                looping = false;
            }
            fullPath.append(name);

            switch (mode) 
            {
            case OPEN_TEXT:
                fp = fopen(fullPath.c_str(), "r");
                break;
            case OPEN_BINARY:
                fp = fopen(fullPath.c_str(), "rb");
                break;
            }

            if (fp)
            {
                return (AssetFilePtr)fp;
            }
        }

        upPath.append("../");
    }

    return nullptr;
}

Buffer AssetLoader::SyncOpenAndReadText(const char* filePath)
{
    Buffer buff;
    AssetFilePtr fp = OpenFile(filePath, OPEN_TEXT);

    if (fp) 
    {
        size_t length = GetSize(fp);

        uint8_t* data = new uint8_t[length + 1];
        length = fread(data, 1, length, static_cast<FILE*>(fp));

        data[length] = '\0';
        buff.SetData(data, length + 1);

        CloseFile(fp);
    }

    return buff;
}

Buffer AssetLoader::SyncOpenAndReadBinary(const char* filePath)
{
    Buffer buff;
    AssetFilePtr fp = OpenFile(filePath, OPEN_BINARY);

    if (fp) 
    {
        size_t length = GetSize(fp);

        uint8_t* data = new uint8_t[length];
        fread(data, length, 1, static_cast<FILE*>(fp));

        buff.SetData(data, length);

        CloseFile(fp);
    }

    return buff;
}

size_t AssetLoader::SyncRead(const AssetFilePtr& fp, Buffer& buf)
{
    size_t sz;

    if (!fp) 
    {
        fprintf(stderr, "null file discriptor\n");
        return 0;
    }

    sz = fread(buf.GetData(), buf.GetDataSize(), 1, static_cast<FILE*>(fp));

    return sz;
}

void AssetLoader::CloseFile(AssetFilePtr& fp)
{
    fclose((FILE*)fp);
    fp = nullptr;
}

size_t AssetLoader::GetSize(const AssetFilePtr& fp)
{
    FILE* _fp = static_cast<FILE*>(fp);

    long pos = ftell(_fp);
    fseek(_fp, 0, SEEK_END);
    size_t length = ftell(_fp);
    fseek(_fp, pos, SEEK_SET);

    return length;
}

int32_t AssetLoader::Seek(AssetFilePtr fp, long offset, AssetSeekBase where)
{
    return fseek(static_cast<FILE*>(fp), offset, static_cast<int>(where));
}
