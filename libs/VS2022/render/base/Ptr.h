#pragma once

#include <utility>

namespace ll {

template <class T>
class IntrusivePtr 
{
public:
    using element_type = T;

    IntrusivePtr() 
    {
    }

    IntrusivePtr(T* p) : _ptr(p) 
    {
        if (_ptr) 
        {
            _ptr->addRef();
        }
    }

    IntrusivePtr(const IntrusivePtr<T>& r) : _ptr(r._ptr) 
    {
        if (_ptr) 
        {
            _ptr->addRef();
        }
    }

    template <typename U>
    IntrusivePtr(const IntrusivePtr<U>& r) : _ptr(r.get()) 
    {
        if (_ptr) 
        {
            _ptr->addRef();
        }
    }

    IntrusivePtr(IntrusivePtr<T>&& r) noexcept : _ptr(r.release()) 
    {
    }

    template <typename U>
    IntrusivePtr(IntrusivePtr<U>&& r) noexcept : _ptr(r.release()) 
    {
    }

    ~IntrusivePtr() 
    {
        if (_ptr) 
        {
            _ptr->release();
        }
    }

    T* get() const { return _ptr; }
    operator T* () const { return _ptr; }
    T& operator*() const { return *_ptr; }
    T* operator->() const { return _ptr; }

    IntrusivePtr<T>& operator=(T* p) 
    {
        reset(p);
        return *this;
    }

    IntrusivePtr<T>& operator=(const IntrusivePtr<T>& r) 
    { 
        return *this = r._ptr;                             
    }

    template <typename U>
    IntrusivePtr<T>& operator=(const IntrusivePtr<U>& r) 
    {
        return *this = r.get();
    }

    IntrusivePtr<T>& operator=(IntrusivePtr<T>&& r) noexcept 
    {
        IntrusivePtr<T>(std::move(r)).swap(*this);
        return *this;
    }

    template <typename U>
    IntrusivePtr<T>& operator=(IntrusivePtr<U>&& r) noexcept 
    {
        IntrusivePtr<T>(std::move(r)).swap(*this);
        return *this;
    }

    bool operator==(std::nullptr_t) 
    {
        return _ptr == nullptr;
    }

    bool operator==(T* r) 
    {
        return _ptr == r;
    }

    bool operator!=(std::nullptr_t) 
    {
        return _ptr != nullptr;
    }

    bool operator!=(T* r) 
    {
        return _ptr != r;
    }

    void reset() noexcept 
    {
        if (_ptr) 
        {
            _ptr->release();
        }
        _ptr = nullptr;
    }

    void reset(T* p) 
    {
        if (p) 
        {
            p->addRef();
        }
        if (_ptr) {
            _ptr->release();
        }
        _ptr = p;
    }

    void swap(T** pp) noexcept 
    {
        T* p = _ptr;
        _ptr = *pp;
        *pp = p;
    }

    void swap(IntrusivePtr<T>& r) noexcept { swap(&r._ptr); }

private:
    T* release() 
    {
        T* retVal = _ptr;
        _ptr = nullptr;
        return retVal;
    }

protected:
    T* _ptr{ nullptr };
};

}