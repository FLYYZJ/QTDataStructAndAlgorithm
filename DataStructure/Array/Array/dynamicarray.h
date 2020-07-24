#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H
#include "common.h"

template <class T>
class DynamicArray
{
public:
    ~DynamicArray();
    DynamicArray();
    DynamicArray(unsigned int, unsigned int = 0);
    DynamicArray(DynamicArray const&);
    DynamicArray& operator = (DynamicArray const&);
    T const& operator [] (unsigned int) const;
    T& operator[] (unsigned int);
    T const* Data() const;
    unsigned int Base() const;
    unsigned int Length() const;
    void SetBase(unsigned int);
    void SetLength(unsigned int);
protected:
    T* data;
    unsigned int base;
    unsigned int length;
public:

};

#include "dynamicarray.h"
template <class T>
DynamicArray<T>::DynamicArray():
    data (new T [10]),
    base(0),
    length(0)
{

}
// 长度为n，初值都设置为m
template <class T>
DynamicArray<T>::DynamicArray(unsigned int n, unsigned int m):
    data (new T [n]),
    base(m),
    length(n)
{

}
// 拷贝构造函数
template <class T>
DynamicArray<T>::DynamicArray(DynamicArray<T> const& array):
    data (new T [array.Length()]),
    base(array.Base()),
    length(array.Length())
{
    for(unsigned int i = 0; i < length; i++)
        data[i] = array.data[i];
}
// 析构函数
template <class T>
DynamicArray<T>::~DynamicArray()
{
    delete []data;
}

// 获取数据
template <class T>
T const* DynamicArray<T>::Data() const
{
    return data;
}
template <class T>
unsigned int DynamicArray<T>::Base() const
{
    return base;
}
template <class T>
unsigned int DynamicArray<T>::Length() const
{
    return length;
}
// 设置属性
template <class T>
void DynamicArray<T>::SetLength(unsigned l)
{
    T *const newData = new T[l];
    unsigned int const min = length < l ? length : l;
    for (unsigned int i = 0; i<min; i++) {  // 只保留最短长度的数据
        newData[i] = data[i];
    }
    delete []data;
    data = newData;
    length = l;
}

template <class T>
void DynamicArray<T>::SetBase(unsigned b)
{
    base = b;
}
// 运算符重载
template<class T>
DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray<T> const& rhs)
{

    const T* temp = rhs.Data();
    for(unsigned int i = 0; i < rhs.Length(); i++)
    {
        data[i] = temp[i];
    }
    return *this;
}
template<class T>
T const& DynamicArray<T>::operator [] (unsigned int pos) const
{
    unsigned int const offset = pos - base;
    if(offset >= length)
    {
        throw std::out_of_range("invalid position");
    }
    return data[offset];
}

template<class T>
T& DynamicArray<T>::operator[](unsigned int pos)
{
    unsigned int const offset = pos - base;
    if(offset >= length)
    {
        throw std::out_of_range("invalid position");
    }
    return data[offset];
}



#endif // DYNAMICARRAY_H
