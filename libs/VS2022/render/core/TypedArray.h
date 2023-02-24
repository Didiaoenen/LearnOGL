#pragma once

#include <cstdint>
#include <memory>
#include <variant>

namespace ll
{

template <typename T>
class TypedArrayTemp 
{
public:
    static constexpr uint32_t BYTES_PER_ELEMENT{ sizeof(T) };
    using value_type = T;

    TypedArrayTemp() = default;

    explicit TypedArrayTemp(uint32_t length) 
    {
        reset(length);
    }

    explicit TypedArrayTemp(ArrayBuffer* buffer)
        : TypedArrayTemp(buffer, 0) {}

    TypedArrayTemp(ArrayBuffer* buffer, uint32_t byteOffset)
        : TypedArrayTemp(buffer, byteOffset, (buffer->byteLength() - byteOffset) / BYTES_PER_ELEMENT) {}

    TypedArrayTemp(ArrayBuffer* buffer, uint32_t byteOffset, uint32_t length)
        : _buffer(buffer),
        _byteOffset(byteOffset),
        _byteLength(length* BYTES_PER_ELEMENT),
        _byteEndPos(byteOffset + length * BYTES_PER_ELEMENT) 
    {
        _jsTypedArray = se::Object::createTypedArrayWithBuffer(toTypedArrayType<T>(), buffer->getJSArrayBuffer(), byteOffset, _byteLength);
        _jsTypedArray->root();
    }

    TypedArrayTemp(const TypedArrayTemp& o) 
    {
        *this = o;
    }

    TypedArrayTemp(TypedArrayTemp&& o) noexcept 
    {
        *this = std::move(o);
    }

    ~TypedArrayTemp() 
    {
        if (_jsTypedArray != nullptr) 
        {
            _jsTypedArray->unroot();
            _jsTypedArray->decRef();
        }
    }

    TypedArrayTemp& operator=(const TypedArrayTemp& o) 
    {
        if (this != &o) 
        {
            setJSTypedArray(o._jsTypedArray);
        }
        return *this;
    }

    TypedArrayTemp& operator=(TypedArrayTemp&& o) noexcept 
    {
        if (this != &o) 
        {
            _buffer = o._buffer;
            _byteOffset = o._byteOffset;
            _byteLength = o._byteLength;
            _byteEndPos = o._byteEndPos;

            if (_jsTypedArray != nullptr) 
            {
                _jsTypedArray->unroot();
                _jsTypedArray->decRef();
            }
            _jsTypedArray = o._jsTypedArray;

            o._buffer = nullptr;
            o._byteOffset = 0;
            o._byteLength = 0;
            o._byteEndPos = 0;
            o._jsTypedArray = nullptr;
        }
        return *this;
    }

    T& operator[](uint32_t idx) 
    {
        return *((reinterpret_cast<T*>(_buffer->_data + _byteOffset)) + idx);
    }

    const T& operator[](uint32_t idx) const 
    {
        return *((reinterpret_cast<T*>(_buffer->_data + _byteOffset)) + idx);
    }

    TypedArrayTemp subarray(uint32_t begin, uint32_t end) 
    {
        return TypedArrayTemp(_buffer, begin * BYTES_PER_ELEMENT, end - begin);
    }

    TypedArrayTemp subarray(uint32_t begin) 
    {
        return TypedArrayTemp(_buffer, begin * BYTES_PER_ELEMENT);
    }

    TypedArrayTemp slice() 
    {
        return slice(0);
    }

    TypedArrayTemp slice(uint32_t start) 
    {
        return slice(start, _byteLength / BYTES_PER_ELEMENT);
    }

    TypedArrayTemp slice(uint32_t start, uint32_t end) 
    {
        uint32_t newBufByteLength = (end - start) * BYTES_PER_ELEMENT;
        auto* buffer = ccnew ArrayBuffer(newBufByteLength);
        memcpy(buffer->getData(), _buffer->getData() + start * BYTES_PER_ELEMENT + _byteOffset, newBufByteLength);
        return TypedArrayTemp(buffer);
    }

    void set(ArrayBuffer* buffer) 
    {
        set(buffer, 0);
    }

    void set(ArrayBuffer* buffer, uint32_t offset) 
    {
        memcpy(_buffer->_data + offset, buffer->_data, buffer->byteLength());
    }

    template <typename SrcType>
    void set(const TypedArrayTemp<SrcType>& array) 
    {
        set(array, 0);
    }

    template <typename SrcType>
    typename std::enable_if_t<std::is_same<T, SrcType>::value, void>
        set(const TypedArrayTemp<SrcType>& array, uint32_t offset);

    template <typename SrcType>
    typename std::enable_if_t<!std::is_same<T, SrcType>::value, void>
        set(const TypedArrayTemp<SrcType>& array, uint32_t offset);

    void reset(uint32_t length) 
    {
        if (_jsTypedArray != nullptr) 
        {
            _jsTypedArray->unroot();
            _jsTypedArray->decRef();
            _jsTypedArray = nullptr;
        }
        const uint32_t byteLength = length * BYTES_PER_ELEMENT;
        _buffer = ccnew ArrayBuffer(byteLength);
        _byteLength = _buffer->byteLength();
        _byteOffset = 0;
        _byteEndPos = byteLength;
        _jsTypedArray = se::Object::createTypedArrayWithBuffer(toTypedArrayType<T>(), _buffer->getJSArrayBuffer(), 0, byteLength);
        _jsTypedArray->root();
    }

    void clear() 
    {
        if (_jsTypedArray != nullptr) 
        {
            _jsTypedArray->unroot();
            _jsTypedArray->decRef();
            _jsTypedArray = nullptr;
        }
        _buffer = nullptr;
        _byteLength = 0;
        _byteOffset = 0;
        _byteEndPos = 0;
    }

    inline ArrayBuffer* buffer() const { return _buffer; }
    inline uint32_t byteLength() const { return _byteLength; }
    inline uint32_t length() const { return _byteLength / BYTES_PER_ELEMENT; }
    inline uint32_t byteOffset() const { return _byteOffset; }
    inline bool empty() const { return _byteLength == 0; }
    inline se::Object* getJSTypedArray() const { return _jsTypedArray; }
    inline void setJSTypedArray(se::Object* typedArray) 
    {
        if (_jsTypedArray != nullptr) 
        {
            _jsTypedArray->unroot();
            _jsTypedArray->decRef();
        }
        _jsTypedArray = typedArray;

        if (_jsTypedArray != nullptr) 
        {
            _jsTypedArray->root();
            _jsTypedArray->incRef();

            Value tmpVal;
            _jsTypedArray->getProperty("buffer", &tmpVal);

            _buffer = ccnew ArrayBuffer();
            _buffer->setJSArrayBuffer(tmpVal.toObject());

            _jsTypedArray->getProperty("byteOffset", &tmpVal);
            _byteOffset = tmpVal.toUint32();

            _jsTypedArray->getProperty("byteLength", &tmpVal);
            _byteLength = tmpVal.toUint32();

            _byteEndPos = _buffer->byteLength();
        }
        else 
        {
            _buffer = nullptr;
            _byteOffset = 0;
            _byteLength = 0;
            _byteEndPos = 0;
        }
    }

private:
    ArrayBuffer::Ptr _buffer;
    uint32_t _byteOffset{ 0 };
    uint32_t _byteLength{ 0 };
    uint32_t _byteEndPos{ 0 };
    se::Object* _jsTypedArray{ nullptr };
};

using Int8Array = TypedArrayTemp<int8_t>;
using Int16Array = TypedArrayTemp<int16_t>;
using Int32Array = TypedArrayTemp<int32_t>;
using Uint8Array = TypedArrayTemp<uint8_t>;
using Uint16Array = TypedArrayTemp<uint16_t>;
using Uint32Array = TypedArrayTemp<uint32_t>;
using Float32Array = TypedArrayTemp<float>;
using Float64Array = TypedArrayTemp<double>;

using TypedArray = std::variant<std::monostate, Int8Array, Int16Array, Int32Array, Uint8Array, Uint16Array, Uint32Array, Float32Array, Float64Array>;


}
