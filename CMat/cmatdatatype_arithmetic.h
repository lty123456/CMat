#ifndef CMATDATATYPE_ARITHMETIC_H
#define CMATDATATYPE_ARITHMETIC_H

#include "cmatdatatype.h"
#include "cmatdatabase.h"
#include "cmatexception.h"

#include <memory>

template<mxClassID classID,bool isComplex>
class CMatData;

template<mxClassID classID, typename T, bool isComplex>
class CMatDataType_Arithmetic : public CMatDataType
{
public:
    constexpr static bool _isComplex = isComplex;

    CMatDataType_Arithmetic();
    CMatDataType_Arithmetic(CMatDataBase *matData,const size_t index);
    CMatDataType_Arithmetic(CMatDataBase *matData,const std::vector<mwSize> &indexes);

    virtual ~CMatDataType_Arithmetic();

    virtual mxClassID Type();

    virtual bool IsComplex();

    virtual T& Real();

    virtual typename std::conditional<isComplex,T&,void>::type
    Imaginary();

    operator T&();

protected:
    inline CMatData<classID,isComplex>* Cast()
    {
        return (CMatData<classID,isComplex>*)this->matData;
    }

protected:
    CMatDataBase                        *matData;    //the matData is parent's mat data
    size_t                              index;
    std::vector<mwSize>                 indexes;

    template<mxClassID,bool,typename,template <bool> class>
    friend class CMatData_Arithmetic;
};

template<mxClassID classID, typename T, bool isComplex>
CMatDataType_Arithmetic<classID,T,isComplex>::CMatDataType_Arithmetic() : matData(NULL),index(-1)
{

}

template<mxClassID classID, typename T, bool isComplex>
CMatDataType_Arithmetic<classID,T,isComplex>::CMatDataType_Arithmetic(CMatDataBase *matData,const size_t index) : matData(matData),index(index)
{
    if(!dynamic_cast<CMatData<classID,isComplex>*>(matData))
    {
        throw CMatException_TypeDiff();
    }
}

template<mxClassID classID, typename T, bool isComplex>
CMatDataType_Arithmetic<classID,T,isComplex>::CMatDataType_Arithmetic(CMatDataBase *matData,const std::vector<mwSize> &indexes) : matData(matData),index(-1),indexes(indexes)
{
    if(!dynamic_cast<CMatData<classID,isComplex>*>(matData))
    {
        throw CMatException_TypeDiff();
    }
}

template<mxClassID classID, typename T, bool isComplex>
CMatDataType_Arithmetic<classID,T,isComplex>::~CMatDataType_Arithmetic()
{
    matData = NULL;
}

template<mxClassID classID, typename T, bool isComplex>
mxClassID CMatDataType_Arithmetic<classID,T,isComplex>::Type()
{
    return classID;
}

template<mxClassID classID, typename T, bool isComplex>
bool CMatDataType_Arithmetic<classID,T,isComplex>::IsComplex()
{
    return isComplex;
}

template<mxClassID classID, typename T, bool isComplex>
T& CMatDataType_Arithmetic<classID,T,isComplex>::Real()
{
    if(size_t(-1) == index)
        return Cast()->Real(indexes);
    else
        return Cast()->Real(index);
}

template<mxClassID classID, typename T, bool isComplex>
typename std::conditional<isComplex,T&,void>::type
CMatDataType_Arithmetic<classID,T,isComplex>::Imaginary()
{
    if constexpr(isComplex)
    {
        if(size_t(-1) == index)
            return Cast()->Imaginary(indexes);
        else
            return Cast()->Imaginary(index);
    }
}

template<mxClassID classID, typename T, bool isComplex>
CMatDataType_Arithmetic<classID,T,isComplex>::operator T&()
{
    return Real();
}

template<mxClassID _classID>
class REG_CLASS
{
public:
};

#define REG_ARITHMETIC_TYPE2(classID,Name)  \
template<>   \
class REG_CLASS<classID> \
{   \
public: \
    template<bool isComplex>    \
    using REG_TYPE = Name<isComplex>;  \
};

#define GET_REG_ARITHMETIC_TYPE2(classID,isComplex)    REG_CLASS<classID>::REG_TYPE<isComplex>

#define REG_ARITHMETIC_TYPE(classID,Name)   \
template<bool isComplex>    \
using REG_TYPE##classID = Name<isComplex>;  \

#define GET_REG_ARITHMETIC_TYPE(classID,isComplex)    REG_TYPE##classID<isComplex>

#define DECLARE_ARITHMETIC_TYPE(Name,classID,type) \
template<bool isComplex> \
class CMatDataType_##Name : public CMatDataType_Arithmetic<classID,type,isComplex> \
{   \
public: \
    CMatDataType_##Name(){}   \
    CMatDataType_##Name(CMatDataBase *matData,const size_t index) : CMatDataType_Arithmetic<classID,type,isComplex>(matData,index) {} \
    CMatDataType_##Name(CMatDataBase *matData,const std::vector<mwSize> &indexes) : CMatDataType_Arithmetic<classID,type,isComplex>(matData,indexes){}   \
};  \
REG_ARITHMETIC_TYPE(classID,CMatDataType_##Name);   \
REG_ARITHMETIC_TYPE2(classID,CMatDataType_##Name);


DECLARE_ARITHMETIC_TYPE(Logical,mxLOGICAL_CLASS,char);
DECLARE_ARITHMETIC_TYPE(Char,mxCHAR_CLASS,char);
DECLARE_ARITHMETIC_TYPE(Double,mxDOUBLE_CLASS,double);
DECLARE_ARITHMETIC_TYPE(Single,mxSINGLE_CLASS,float);
DECLARE_ARITHMETIC_TYPE(Int8,mxINT8_CLASS,int8_t);
DECLARE_ARITHMETIC_TYPE(UInt8,mxUINT8_CLASS,uint8_t);
DECLARE_ARITHMETIC_TYPE(Int16,mxINT16_CLASS,int16_t);
DECLARE_ARITHMETIC_TYPE(UInt16,mxUINT16_CLASS,uint16_t);
DECLARE_ARITHMETIC_TYPE(Int32,mxINT32_CLASS,int32_t);
DECLARE_ARITHMETIC_TYPE(UInt32,mxUINT32_CLASS,uint32_t);
DECLARE_ARITHMETIC_TYPE(Int64,mxINT64_CLASS,int64_t);
DECLARE_ARITHMETIC_TYPE(UInt64,mxUINT64_CLASS,uint64_t);

#endif // CMATDATATYPE_ARITHMETIC_H
