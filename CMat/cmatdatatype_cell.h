#ifndef CMATDATATYPE_CELL_H
#define CMATDATATYPE_CELL_H

#include "cmatdatatype_arithmetic.h"

class CMatDataType_Cell : public CMatDataType
{
public:
    class CellData_Proxy
    {
    public:
        CellData_Proxy(const CMatDataType_Cell *parent,const int64_t index) : parent(parent), index(index){}
        CellData_Proxy(const CMatDataType_Cell *parent,const std::vector<mwSize> indexes) : parent(parent), index(-1),indexes(indexes){}

        template<typename T>
        operator T()
        {
            static_assert (std::is_base_of<CMatDataType,T>::value,"Assignment failed!");

            T data;
            if(-1 == index)
                (*(parent->matDataPtr))->Get(indexes,data);
            else
                (*(parent->matDataPtr))->Get(index,data);
            return data;
        }

    protected:
        const CMatDataType_Cell *parent;
        const int64_t index;
        const std::vector<mwSize> indexes;
    };

    CMatDataType_Cell(const CMatDataType_Cell &other);
    virtual ~CMatDataType_Cell();

    virtual mxClassID Type();

    virtual bool IsComplex();

    bool Retype(const mxClassID classID, bool isComplex = false,const std::vector<mwSize> &dims = {1,1});   //reset the cell data type

    bool Resize(const std::vector<mwSize> &dims);   //resize will not init the element,use the function carefully

    bool ResizeToIndexes(const std::vector<mwSize> &indexes);

    const std::vector<mwSize> &Dims();

    mwSize Size();

    mxArray *CreateMXArray();

    bool FromMXArray(mxArray *array);

//    CMatDataType* At(const std::vector<mwSize> &indexes);

    bool At(const std::vector<mwSize> &indexes,CMatDataType &data);

    //if resetType is true,expandSize will be treated as true
    template<mxClassID classID,bool isComplex,typename retType>
    retType At(const std::vector<mwSize> &indexes,bool resetType = true,bool expandSize = true);

//    template<mxClassID classID = mxDOUBLE_CLASS,bool isComplex = false>
//    auto AtTest(const std::vector<mwSize> &indexes = {0,0},bool resetType = true,bool expandSize = true) ->decltype (GET_REG_ARITHMETIC_TYPE2(classID,isComplex))
//    {
//        return At<classID,isComplex,GET_REG_ARITHMETIC_TYPE2(classID,isComplex) >(indexes,resetType,expandSize);
//    }

    template<mxClassID classID,bool isComplex = false>
    typename std::enable_if<classID == mxCELL_CLASS,CMatDataType_Cell>::type At(const std::vector<mwSize> &indexes,bool resetType = true,bool expandSize = true);

    template<mxClassID classID,bool isComplex = false>
    typename std::enable_if<classID == mxLOGICAL_CLASS,CMatDataType_Logical<isComplex> >::type At(const std::vector<mwSize> &indexes,bool resetType = true,bool expandSize = true);

    template<mxClassID classID,bool isComplex = false>
    typename std::enable_if<classID == mxCHAR_CLASS,CMatDataType_Char<isComplex> >::type At(const std::vector<mwSize> &indexes,bool resetType = true,bool expandSize = true);

    template<mxClassID classID,bool isComplex = true>
    typename std::enable_if<classID == mxDOUBLE_CLASS,CMatDataType_Double<isComplex> >::type At(const std::vector<mwSize> &indexes,bool resetType = true,bool expandSize = true);

    template<mxClassID classID,bool isComplex = true>
    typename std::enable_if<classID == mxSINGLE_CLASS,CMatDataType_Single<isComplex> >::type At(const std::vector<mwSize> &indexes,bool resetType = true,bool expandSize = true);

    template<mxClassID classID,bool isComplex = true>
    typename std::enable_if<classID == mxINT8_CLASS,CMatDataType_Int8<isComplex> >::type At(const std::vector<mwSize> &indexes,bool resetType = true,bool expandSize = true);

    template<mxClassID classID,bool isComplex = true>
    typename std::enable_if<classID == mxUINT8_CLASS,CMatDataType_UInt8<isComplex> >::type At(const std::vector<mwSize> &indexes,bool resetType = true,bool expandSize = true);

    template<mxClassID classID,bool isComplex = true>
    typename std::enable_if<classID == mxINT16_CLASS,CMatDataType_Int16<isComplex> >::type At(const std::vector<mwSize> &indexes,bool resetType = true,bool expandSize = true);

    template<mxClassID classID,bool isComplex = true>
    typename std::enable_if<classID == mxUINT16_CLASS,CMatDataType_UInt16<isComplex> >::type At(const std::vector<mwSize> &indexes,bool resetType = true,bool expandSize = true);

    template<mxClassID classID,bool isComplex = true>
    typename std::enable_if<classID == mxINT32_CLASS,CMatDataType_Int32<isComplex> >::type At(const std::vector<mwSize> &indexes,bool resetType = true,bool expandSize = true);

    template<mxClassID classID,bool isComplex = true>
    typename std::enable_if<classID == mxUINT32_CLASS,CMatDataType_UInt32<isComplex> >::type At(const std::vector<mwSize> &indexes,bool resetType = true,bool expandSize = true);

    template<mxClassID classID,bool isComplex = true>
    typename std::enable_if<classID == mxINT64_CLASS,CMatDataType_Int64<isComplex> >::type At(const std::vector<mwSize> &indexes,bool resetType = true,bool expandSize = true);

    template<mxClassID classID,bool isComplex = true>
    typename std::enable_if<classID == mxUINT64_CLASS,CMatDataType_UInt64<isComplex> >::type At(const std::vector<mwSize> &indexes,bool resetType = true,bool expandSize = true);

    CMatDataType_Cell& operator=(const CMatDataType_Cell &other);

    CellData_Proxy At(const std::vector<mwSize> &indexes);

    CellData_Proxy operator[](mwSize index);

private:
    CMatDataType_Cell();

    std::shared_ptr<CMatDataBase*>  matDataPtr;

    template<mxClassID classID,bool isComplex>
    friend class CMatData;
};

template<mxClassID classID,bool isComplex,typename retType>
retType CMatDataType_Cell::At(const std::vector<mwSize> &indexes,bool resetType,bool expandSize)
{
    if(resetType)
        expandSize = true;

    if(!*matDataPtr || classID != (*matDataPtr)->Type() || isComplex != (*matDataPtr)->IsComplex())
    {
        if(!resetType)
            throw CMatException_TypeDiff();
        else
        {
            Retype(classID,isComplex);
        }
    }

    retType data;
    if(expandSize)
    {
        try {
            At(indexes,data);
        }  catch (CMatException_DimsOutRange &) {
            ResizeToIndexes(indexes);
            At(indexes,data);
        } catch (CMatException_IndexOutRange &) {
            ResizeToIndexes(indexes);
            At(indexes,data);
        }
    }else
    {
        At(indexes,data);
    }

    return data;
}

template<mxClassID classID,bool isComplex>
typename std::enable_if<classID == mxCELL_CLASS,CMatDataType_Cell>::type CMatDataType_Cell::At(const std::vector<mwSize> &indexes,bool resetType,bool expandSize)
{
    return At<classID,isComplex,CMatDataType_Cell>(indexes,resetType,expandSize);
}

template<mxClassID classID,bool isComplex>
typename std::enable_if<classID == mxLOGICAL_CLASS,CMatDataType_Logical<isComplex> >::type CMatDataType_Cell::At(const std::vector<mwSize> &indexes,bool resetType,bool expandSize)
{
    return At<classID,isComplex,CMatDataType_Logical<isComplex> >(indexes,resetType,expandSize);
}

template<mxClassID classID,bool isComplex>
typename std::enable_if<classID == mxCHAR_CLASS,CMatDataType_Char<isComplex>>::type CMatDataType_Cell::At(const std::vector<mwSize> &indexes,bool resetType,bool expandSize)
{
    return At<classID,isComplex,CMatDataType_Char<isComplex> >(indexes,resetType,expandSize);
}

template<mxClassID classID,bool isComplex>
typename std::enable_if<classID == mxDOUBLE_CLASS,CMatDataType_Double<isComplex> >::type CMatDataType_Cell::At(const std::vector<mwSize> &indexes,bool resetType,bool expandSize)
{
    return At<classID,isComplex,CMatDataType_Double<isComplex> >(indexes,resetType,expandSize);
}

template<mxClassID classID,bool isComplex>
typename std::enable_if<classID == mxSINGLE_CLASS,CMatDataType_Single<isComplex> >::type CMatDataType_Cell::At(const std::vector<mwSize> &indexes,bool resetType,bool expandSize)
{
    return At<classID,isComplex,CMatDataType_Single<isComplex> >(indexes,resetType,expandSize);
}

template<mxClassID classID,bool isComplex>
typename std::enable_if<classID == mxINT8_CLASS,CMatDataType_Int8<isComplex> >::type CMatDataType_Cell::At(const std::vector<mwSize> &indexes,bool resetType,bool expandSize)
{
    return At<classID,isComplex,CMatDataType_Int8<isComplex> >(indexes,resetType,expandSize);
}

template<mxClassID classID,bool isComplex>
typename std::enable_if<classID == mxUINT8_CLASS,CMatDataType_UInt8<isComplex> >::type CMatDataType_Cell::At(const std::vector<mwSize> &indexes,bool resetType,bool expandSize)
{
    return At<classID,isComplex,CMatDataType_UInt8<isComplex> >(indexes,resetType,expandSize);
}

template<mxClassID classID,bool isComplex>
typename std::enable_if<classID == mxINT16_CLASS,CMatDataType_Int16<isComplex> >::type CMatDataType_Cell::At(const std::vector<mwSize> &indexes,bool resetType,bool expandSize)
{
    return At<classID,isComplex,CMatDataType_Int16<isComplex> >(indexes,resetType,expandSize);
}

template<mxClassID classID,bool isComplex>
typename std::enable_if<classID == mxUINT16_CLASS,CMatDataType_UInt16<isComplex> >::type CMatDataType_Cell::At(const std::vector<mwSize> &indexes,bool resetType,bool expandSize)
{
    return At<classID,isComplex,CMatDataType_UInt16<isComplex> >(indexes,resetType,expandSize);
}

template<mxClassID classID,bool isComplex>
typename std::enable_if<classID == mxINT32_CLASS,CMatDataType_Int32<isComplex> >::type CMatDataType_Cell::At(const std::vector<mwSize> &indexes,bool resetType,bool expandSize)
{
    return At<classID,isComplex,CMatDataType_Int32<isComplex> >(indexes,resetType,expandSize);
}

template<mxClassID classID,bool isComplex>
typename std::enable_if<classID == mxUINT32_CLASS,CMatDataType_UInt32<isComplex> >::type CMatDataType_Cell::At(const std::vector<mwSize> &indexes,bool resetType,bool expandSize)
{
    return At<classID,isComplex,CMatDataType_UInt32<isComplex> >(indexes,resetType,expandSize);
}

template<mxClassID classID,bool isComplex>
typename std::enable_if<classID == mxINT64_CLASS,CMatDataType_Int64<isComplex> >::type CMatDataType_Cell::At(const std::vector<mwSize> &indexes,bool resetType,bool expandSize)
{
    return At<classID,isComplex,CMatDataType_Int64<isComplex> >(indexes,resetType,expandSize);
}

template<mxClassID classID,bool isComplex>
typename std::enable_if<classID == mxUINT64_CLASS,CMatDataType_UInt64<isComplex> >::type CMatDataType_Cell::At(const std::vector<mwSize> &indexes,bool resetType,bool expandSize)
{
    return At<classID,isComplex,CMatDataType_UInt64<isComplex> >(indexes,resetType,expandSize);
}

#endif // CMATDATATYPE_CELL_H
