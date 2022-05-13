#ifndef CMATCOMPLEXARRAY_H
#define CMATCOMPLEXARRAY_H

#include "cmatarray.h"

template<typename T, bool isComplex = false>
class CMatComplexArray : public CMatArray<T>
{
public:
    CMatComplexArray(const std::vector<mwSize> &dims,bool unbuffered = true) : CMatArray<T>(dims,unbuffered)
    {
        static_assert(!(isComplex && !std::is_arithmetic<T>::value),"isComplex[true] only used for arithmetic");
    }

};

template<typename T>
class CMatComplexArray<T,true> : public CMatArray<T>
{
public:
    CMatComplexArray(const std::vector<mwSize> &dims,bool unbuffered = true) : CMatArray<T>(dims,unbuffered),imaginaryData(dims,unbuffered)
    {

    }

    virtual T& Imaginary(const mwSize index)
    {
        return imaginaryData[index];
    }

    virtual T& Imaginary(const std::vector<mwSize> &indexes)
    {
        return imaginaryData.At(indexes);
    }

    virtual bool Resize(const std::vector<mwSize> &dims)
    {
        bool ret = CMatArray<T>::Resize(dims);
        ret &= imaginaryData.Resize(dims);
        return ret;
    }
protected:
    CMatArrayBase<T>    imaginaryData;
};

#endif // CMATCOMPLEXARRAY_H
