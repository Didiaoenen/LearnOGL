#pragma once

namespace ll
{

template <typename T>
class CachedArray final 
{
public:
    explicit CachedArray(uint32_t size = 1U) 
    {
        _size = 0;
        _capacity = std::max(size, 1U);
        _array = new T[_capacity];
    }

    ~CachedArray() 
    {
    }

    CachedArray(const CachedArray& other)
        : _size(other._size), _capacity(other._capacity), _array(new T[other._capacity]) 
    {
        memcpy(_array, other._array, _size * sizeof(T));
    }

    CachedArray& operator=(const CachedArray& other) 
    {
        if (this != &other) {
            delete[] _array;
            _size = other._size;
            _capacity = other._capacity;
            _array = new T[_capacity];
            memcpy(_array, other._array, _size * sizeof(T));
        }
        return *this;
    }

    CachedArray(CachedArray&& other) noexcept : _size(other._size), _capacity(other._capacity), _array(other._array) 
    {
        other._size = 0;
        other._capacity = 0;
        other._array = nullptr;
    }

    CachedArray& operator=(CachedArray&& other) noexcept 
    {
        if (this != &other) 
        {
            delete[] _array;
            _size = other._size;
            _capacity = other._capacity;
            _array = other._array;
            other._size = 0;
            other._capacity = 0;
            other._array = nullptr;
        }
        return *this;
    }

    T& operator[](uint32_t index) 
    {
        return _array[index];
    }

    const T& operator[](uint32_t index) const
    {
        return _array[index];
    }

    inline void clear() { _size = 0; }
    inline uint32_t size() const { return _size; }
    inline T pop() { return _array[--_size]; }

    void reserve(uint32_t size) 
    {
        if (size > _capacity) 
        {
            T* temp = _array;
            _array = new T[size];
            memcpy(_array, temp, _capacity * sizeof(T));
            _capacity = size;
            delete[] temp;
        }
    }

    void push(T item) 
    {
        if (_size >= _capacity) 
        {
            T* temp = _array;
            _array = new T[_capacity * 2];
            memcpy(_array, temp, _capacity * sizeof(T));
            _capacity *= 2;
            delete[] temp;
        }
        _array[_size++] = item;
    }

    void concat(const CachedArray<T>& array) 
    {
        if (_size + array._size > _capacity) 
        {
            T* temp = _array;
            uint32_t size = std::max(_capacity * 2, _size + array._size);
            _array = new T[size];
            memcpy(_array, temp, _size * sizeof(T));
            _capacity = size;
            delete[] temp;
        }
        memcpy(_array + _size, array._array, array._size * sizeof(T));
        _size += array._size;
    }

    void concat(T* array, uint32_t count) 
    {
        if (_size + count > _capacity) 
        {
            T* temp = _array;
            uint32_t size = std::max(_capacity * 2, _size + count);
            _array = new T[size];
            memcpy(_array, temp, _size * sizeof(T));
            _capacity = size;
            delete[] temp;
        }
        memcpy(_array + _size, array, count * sizeof(T));
        _size += count;
    }

    void fastRemove(uint32_t idx) 
    {
        if (idx >= _size) 
        {
            return;
        }
        _array[idx] = _array[--_size];
    }

    uint32_t indexOf(T item) 
    {
        for (uint32_t i = 0; i < _size; ++i) 
        {
            if (_array[i] == item) 
            {
                return i;
            }
        }
        return UINT_MAX;
    }

private:
    uint32_t _size = 0;
    uint32_t _capacity = 0;
    T* _array = nullptr;
};

}