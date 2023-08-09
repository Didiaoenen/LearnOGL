#pragma once

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <memory>

namespace OGL 
{
    class Buffer 
    {
    public:
        Buffer() = default;

        explicit Buffer(size_t size, size_t alignment = 4) 
            : mSize(size) 
        {
            mData = reinterpret_cast<uint8_t*>(new uint8_t[size]);
        }

        Buffer(const Buffer& rhs) = delete;

        Buffer(Buffer&& rhs) noexcept 
        {
            mData = rhs.mData;
            mSize = rhs.mSize;
            rhs.mData = nullptr;
            rhs.mSize = 0;
        }

        Buffer& operator=(const Buffer& rhs) = delete;

        Buffer& operator=(Buffer&& rhs) noexcept 
        {
            delete[] mData;
            mData = rhs.mData;
            mSize = rhs.mSize;
            rhs.mData = nullptr;
            rhs.mSize = 0;
            return *this;
        }

        ~Buffer() 
        {
            if (mData != nullptr) 
            {
                delete[] mData;
            }
        }

        [[nodiscard]] uint8_t* GetData() { return mData; };
        [[nodiscard]] const uint8_t* GetData() const { return mData; };
        [[nodiscard]] size_t GetDataSize() const { return mSize; };
        
        uint8_t* MoveData() 
        {
            uint8_t* tmp = mData;
            mData = nullptr;
            mSize = 0;
            return tmp;
        }

        void SetData(uint8_t* data, size_t size) 
        {
            if (mData != nullptr) 
            {
                delete[] mData;
            }
            mData = data;
            mSize = size;
        }

    protected:
        size_t mSize{ 0 };
        uint8_t* mData{ nullptr };
    };
}
