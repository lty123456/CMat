#ifndef CMATDATA_CELL_H
#define CMATDATA_CELL_H

#include "cmatdata.h"
#include "cmatdatatype_cell.h"

template<bool isComplex>
class CMatData<mxCELL_CLASS,isComplex> : public CMatDataBase, public CMatComplexArray<CMatDataType*,isComplex>
{
public:
    CMatData(const std::vector<mwSize> &dims,bool unbuffered = true) : CMatDataBase(), CMatComplexArray<CMatDataType*, isComplex> (dims,unbuffered)
    {
        static_assert (!isComplex,"Cell can not be complex" );
    }

    virtual ~CMatData()
    {
        for(mwSize i = 0;i < Size();++i)
        {
            CMatDataType*& ptr = CMatArrayBase<CMatDataType*>::operator[](i);
            if(ptr)
            {
                delete ptr;
                ptr = NULL;
            }
        }
    }

    virtual bool IsComplex() const
    {
        return isComplex;
    }

    virtual mxClassID Type()
    {
        return mxCELL_CLASS;
    }

    virtual const std::vector<mwSize> &Dims()
    {
        return CMatComplexArray<CMatDataType*,isComplex>::Dims();
    }

    virtual mwSize Size()
    {
        return CMatComplexArray<CMatDataType*,isComplex>::Size();
    }

    virtual bool Resize(const std::vector<mwSize> &dims)
    {
        return CMatComplexArray<CMatDataType*,isComplex>::Resize(dims);
    }

    virtual bool Get(const mwSize index, CMatDataType &data)
    {
        CMatDataType*& p = CMatArrayBase<CMatDataType*>::operator[](index);
        CMatDataType_Cell *cell = dynamic_cast<CMatDataType_Cell *>(p);
        if(!cell)
        {
            p = cell = new CMatDataType_Cell;
        }
        dynamic_cast<CMatDataType_Cell&>(data) = *cell;
        return true;
    }

    virtual bool Get(const std::vector<mwSize> &indexes, CMatDataType &data)
    {
        CMatDataType*& p = CMatArrayBase<CMatDataType*>::At(indexes);
        CMatDataType_Cell *cell = dynamic_cast<CMatDataType_Cell *>(p);
        if(!cell)
        {
            p = cell = new CMatDataType_Cell;
        }
        dynamic_cast<CMatDataType_Cell&>(data) = *cell;
        return true;
    }

    virtual mxArray* CreateMXArray()
    {
        const std::vector<mwSize> &dims = Dims();
        mxArray *array = mxCreateCellArray(dims.size(),dims.data());
        for(mwSize i = 0;i < Size();++i)
        {
            CMatDataType_Cell cell = operator[](i);
            mxSetCell(array,i,cell.CreateMXArray());
        }
        return array;
    }

    virtual bool FromMxArray(mxArray *array)
    {
        std::vector<mwSize> dims = GetDimsFromMxArray(array);
        Resize(dims);

        for(mwSize i = 0;i < Size();++i)
        {
            mxArray *cellArray = mxGetCell(array,i);
            CMatDataType_Cell cell = operator[](i);

            if(!cellArray)
                continue;

            if(!cell.FromMXArray(cellArray))
                return false;

//            mxDestroyArray(cellArray);
        }
        return true;
    }

    CMatDataType_Cell At(const std::vector<mwSize> &indexes)
    {
        CMatDataType_Cell cell;
        Get(indexes,cell);
        return cell;
    }

    CMatDataType_Cell operator[](size_t index)
    {
        CMatDataType_Cell cell;
        Get(index,cell);
        return cell;
    }
};

#endif // CMATDATA_CELL_H
