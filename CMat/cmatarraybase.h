#ifndef CMATARRAYBASE_H
#define CMATARRAYBASE_H
#include "cmatexception.h"

#include <mat.h>
#include <vector>
#include <memory>
#include <numeric>
#include <functional>

//template<typename _Tp>
//struct dim_multiplies : public std::binary_function<_Tp, _Tp, _Tp>
//{
//_GLIBCXX14_CONSTEXPR
//_Tp
//operator()(const _Tp& __x, const _Tp& __y) const
//{ return (__x + 1) * (__y + 1); }
//};

template<typename T>
class CMatArrayBase
{
public:
    CMatArrayBase() = default;
    CMatArrayBase(const std::vector<mwSize> &dims,bool unbuffered);

    virtual ~CMatArrayBase();

    virtual void Clear();

    const std::vector<mwSize> &Dims();

    mwSize Size();

    T& operator[](mwSize index);

    T& At(const std::vector<mwSize>& indexes);

    virtual bool Resize(const std::vector<mwSize> &dims);

protected:
    void SetDims(const std::vector<mwSize> &dims);

    std::vector<T>      array;
    std::vector<mwSize> dims;
    std::vector<mwSize> dim_size;
    mwSize              size;

    template<mxClassID,bool,typename,template <bool> class>
    friend class CMatData_Arithmetic;
};

template<typename T>
CMatArrayBase<T>::CMatArrayBase(const std::vector<mwSize> &dims, bool)
{
    Resize(dims);
}

template<typename T>
CMatArrayBase<T>::~CMatArrayBase()
{
    Clear();
}

template<typename T>
void CMatArrayBase<T>::Clear()
{
    dims = {0};
    dim_size.clear();
    size = 0;
    array.clear();
}

template<typename T>
const std::vector<mwSize> &CMatArrayBase<T>::Dims()
{
    return dims;
}

template<typename T>
mwSize CMatArrayBase<T>::Size()
{
    return size;
}

template<typename T>
T& CMatArrayBase<T>::operator[](mwSize index)
{
    if(index >= array.size())
        throw CMatException_IndexOutRange();

    return array[index];
}

template<typename T>
T& CMatArrayBase<T>::At(const std::vector<mwSize>& indexes)
{
    if(indexes.size() > dims.size())
        throw CMatException_DimsOutRange();

    mwSize trueIndex = 0;
    for(size_t i = 0;i < indexes.size();++i)
    {
        const mwSize& index= indexes[i];
        if(index >= dims[i])
            throw CMatException_IndexOutRange();

        trueIndex += index * dim_size[i];
    }      

    return array[trueIndex];
}

template<typename T>
bool CMatArrayBase<T>::Resize(const std::vector<mwSize> &dims)
{
    SetDims(dims);
    size = std::accumulate(this->dims.begin(),this->dims.end(),mwSize(1),std::multiplies<mwSize>());
    array.resize(size);
    return true;
}

template<typename T>
void CMatArrayBase<T>::SetDims(const std::vector<mwSize> &dims)
{
/*    if(0 >= dims.size())
        this->dims = {1,1};
    else */if(1 == dims.size())
    {
        this->dims = dims;
        this->dims.push_back(1);
    }else
    {
        this->dims = dims;
    }

    dim_size.resize(dims.size());
    if(dims.size() > 0)
    {
        dim_size[0] = 1;
        for(mwSize i = 1;i < dims.size();++i)
        {
            dim_size[i] = dims[i - 1] * dim_size[i - 1];
        }
    }
}

#endif // CMATARRAYBASE_H
