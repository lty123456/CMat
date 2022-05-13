#ifndef CMATDATA_ARITHMETIC_H
#define CMATDATA_ARITHMETIC_H

#include "cmatdata.h"
#include "cmatdatatype_arithmetic.h"

template<mxClassID classID,bool isComplex,typename dataT,template <bool> class wapperT>
class CMatData_Arithmetic : public CMatDataBase, public CMatComplexArray<dataT,isComplex>
{
public:
    CMatData_Arithmetic(const std::vector<mwSize> &dims,bool unbuffered = true) : CMatDataBase(), CMatComplexArray<dataT, isComplex> (dims,unbuffered)
    {
        static_assert (std::is_arithmetic<dataT>::value, "CMatData_Arithmetic only for arithmetic type");
    }

    virtual ~CMatData_Arithmetic()
    {

    }

    virtual bool IsComplex() const
    {
        return isComplex;
    }

    virtual mxClassID Type()
    {
        return classID;
    }

    virtual const std::vector<mwSize>& Dims()
    {
        return CMatComplexArray<dataT,isComplex>::Dims();
    }

    virtual mwSize Size()
    {
        return CMatComplexArray<dataT,isComplex>::Size();
    }

    virtual bool Resize(const std::vector<mwSize> &dims)
    {
        return CMatComplexArray<dataT,isComplex>::Resize(dims);
    }

    virtual bool Get(const mwSize index, CMatDataType &data)
    {
        //faster
        ((wapperT<isComplex>&)data).matData = this;
        ((wapperT<isComplex>&)data).index = index;
        ((wapperT<isComplex>&)data).indexes.clear();

        //slower
//        dynamic_cast<wapperT<isComplex>&>(data) = wapperT<isComplex>(this,index);
        return true;
    }

    virtual bool Get(const std::vector<mwSize> &indexes, CMatDataType &data)
    {
        //faster
        ((wapperT<isComplex>&)data).matData = this;
        ((wapperT<isComplex>&)data).index = -1;
        ((wapperT<isComplex>&)data).indexes = indexes;

        //slower
//        dynamic_cast<wapperT<isComplex>&>(data) = wapperT<isComplex>(this,indexes);
        return true;
    }

    virtual mxArray* CreateMXArray()
    {
        mxArray *array;
        const std::vector<mwSize> &dims = Dims();
        if constexpr(isComplex)
        {
            array = mxCreateNumericArray(dims.size(),dims.data(),classID,mxCOMPLEX);

            dataT* dynamicDataR = (dataT*)mxCalloc(Size(),sizeof(dataT));
            dataT* dynamicDataI = (dataT*)mxCalloc(Size(),sizeof(dataT));
            memcpy(dynamicDataR,this->array.data(),Size() * sizeof(dataT));
            memcpy(dynamicDataI,this->imaginaryData.array.data(),Size() * sizeof(dataT));

            if constexpr(std::is_same<double,dataT>::value)
            {
                mxSetPr(array,dynamicDataR);
                mxSetPi(array,dynamicDataI);
            }else{
                mxSetData(array,dynamicDataR);
                mxSetImagData(array,dynamicDataI);
            }
        }else
        {
            array = mxCreateNumericArray(dims.size(),dims.data(),classID,mxREAL);
            dataT* dynamicDataR = (dataT*)mxCalloc(Size(),sizeof(dataT));
            for(mwSize i = 0;i < Size();++i)
            {
                dynamicDataR[i] = operator[](i);
            }
            if constexpr(std::is_same<double,dataT>::value)
            {
                mxSetPr(array,dynamicDataR);
            }else{
                mxSetData(array,dynamicDataR);
            }
        }

        return array;
    }

    virtual bool FromMxArray(mxArray *array)
    {
        const std::vector<mwSize> dims = GetDimsFromMxArray(array);
        Resize(dims);
        if constexpr(isComplex)
        {
            assert(mxIsComplex(array));
            dataT *dynamicDataR;
            dataT *dynamicDataI;
            if constexpr(std::is_same<double,dataT>::value)
            {
                dynamicDataR = mxGetPr(array);
                dynamicDataI = mxGetPi(array);
            }else
            {
                dynamicDataR = (dataT *)mxGetData(array);
                dynamicDataI = (dataT *)mxGetImagData(array);
            }
            assert(dynamicDataR && dynamicDataI);

            for(mwSize i = 0;i < Size();++i)
            {
                CMatArrayBase<dataT>::operator[](i) = dynamicDataR[i];
                this->imaginaryData.operator[](i) = dynamicDataI[i];
            }

        }else
        {

            dataT *dynamicDataR;
            if constexpr(std::is_same<double,dataT>::value)
            {
                dynamicDataR = mxGetPr(array);
            }else
            {
                dynamicDataR = (dataT *)mxGetData(array);
            }
            assert(dynamicDataR);

            for(mwSize i = 0;i < Size();++i)
            {
                CMatArrayBase<dataT>::operator[](i) = dynamicDataR[i];
            }
        }

        return true;
    }

    wapperT<isComplex> At(const std::vector<mwSize> &indexes)
    {
        return wapperT<isComplex>(this,indexes);
    }

    wapperT<isComplex> operator[](mwSize index)
    {
        return wapperT<isComplex>(this,index);
    }
};

#define DECLARE_ARITHMETIC_DATA(name,classID,type)   \
template<bool isComplex>    \
class CMatData<classID,isComplex> : public CMatData_Arithmetic<classID,isComplex,type,CMatDataType_##name>  \
{   \
public: \
    using DataType = CMatDataType_##name<isComplex>;\
    CMatData(const std::vector<mwSize> &dims,bool unbuffered = true) : CMatData_Arithmetic<classID,isComplex,type,CMatDataType_##name> (dims,unbuffered)   \
    {    }  \
};

DECLARE_ARITHMETIC_DATA(Logical,mxLOGICAL_CLASS,char);
DECLARE_ARITHMETIC_DATA(Char,mxCHAR_CLASS,char);
DECLARE_ARITHMETIC_DATA(Double,mxDOUBLE_CLASS,double);
DECLARE_ARITHMETIC_DATA(Single,mxSINGLE_CLASS,float);
DECLARE_ARITHMETIC_DATA(Int8,mxINT8_CLASS,int8_t);
DECLARE_ARITHMETIC_DATA(UInt8,mxUINT8_CLASS,uint8_t);
DECLARE_ARITHMETIC_DATA(Int16,mxINT16_CLASS,int16_t);
DECLARE_ARITHMETIC_DATA(UInt16,mxUINT16_CLASS,uint16_t);
DECLARE_ARITHMETIC_DATA(Int32,mxINT32_CLASS,int32_t);
DECLARE_ARITHMETIC_DATA(UInt32,mxUINT32_CLASS,uint32_t);
DECLARE_ARITHMETIC_DATA(Int64,mxINT64_CLASS,int64_t);
DECLARE_ARITHMETIC_DATA(UInt64,mxUINT64_CLASS,uint64_t);

#endif // CMATDATA_ARITHMETIC_H
