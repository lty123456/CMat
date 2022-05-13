#ifndef CMATARRAY_H
#define CMATARRAY_H

#include "cmatarraybase.h"
#include "cmatdatatype.h"

#include <string.h>

template<typename T,bool is_arithmetic = std::is_arithmetic<T>::value>
class CMatArray : public CMatArrayBase<T>
{
public:
    CMatArray(const std::vector<mwSize> &dims,bool unbuffered = true) : CMatArrayBase<T>(dims,unbuffered)
    {
    }

    virtual T& Real(const mwSize index)
    {
        return this->operator[](index);
    }

    virtual T& Real(const std::vector<mwSize> &indexes)
    {
        return this->At(indexes);
    }


protected:
    CMatArray()
    {
    }
};

//template<typename T>
//class CMatArray<T,false> : public CMatArrayBase<CMatDataType*>
//{
//public:
//    CMatArray(const std::vector<mwSize> &dims,bool) : CMatArrayBase<CMatDataType*>(dims,false)
//    {
//        if(Size() > 0)
//            memset(&array[0],0,Size() * sizeof(CMatDataType*));
//    }

//protected:
//    CMatArray()
//    {

//    }
//};


#endif // CMATARRAY_H
