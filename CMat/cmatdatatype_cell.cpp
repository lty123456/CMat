#include "cmatdatatype_cell.h"
#include "cmatdata.h"

void FreeCell(void *p)
{
    if(p)
    {
        CMatDataBase** matDataPtr = (CMatDataBase**)p;
        if(*matDataPtr)
            delete *matDataPtr;
        delete matDataPtr;
    }
}

CMatDataType_Cell::CMatDataType_Cell(const CMatDataType_Cell &other)
{
    *this = other;
}

CMatDataType_Cell::~CMatDataType_Cell()
{
//    FreeData();
}

mxClassID CMatDataType_Cell::Type()
{
    return mxCELL_CLASS;
}

bool CMatDataType_Cell::IsComplex()
{
    return false;
}

bool CMatDataType_Cell::Retype(const mxClassID classID,bool isComplex,const std::vector<mwSize> &dims)
{
//    FreeData();

//    if(!matDataPtr)
//        matDataPtr = new CMatDataBase*(NULL);

    if(*matDataPtr)
    {
        delete *matDataPtr;
        *matDataPtr = NULL;
    }

    *matDataPtr = CreateMatData(classID,isComplex,dims);
//    matData.reset(CreateMatData(classID,isComplex,dims));
    return !!*matDataPtr;
}

bool CMatDataType_Cell::Resize(const std::vector<mwSize> &dims)
{
    return (*matDataPtr)->Resize(dims);
}

bool CMatDataType_Cell::ResizeToIndexes(const std::vector<mwSize> &indexes)
{
    std::vector<mwSize> dims(indexes.size());
    for(mwSize i = 0;i < indexes.size();++i)
    {
        dims[i] = indexes[i] + 1;
    }
    return Resize(dims);
}

const std::vector<mwSize> & CMatDataType_Cell::Dims()
{
    return (*matDataPtr)->Dims();
}

mwSize CMatDataType_Cell::Size()
{
    return (*matDataPtr)->Size();
}

mxArray *CMatDataType_Cell::CreateMXArray()
{
    if(*matDataPtr)
        return (*matDataPtr)->CreateMXArray();

    return NULL;
}

bool CMatDataType_Cell::FromMXArray(mxArray *array)
{
    mxClassID classID = mxGetClassID(array);
    bool isComplex = mxIsComplex(array);
    *matDataPtr = CreateMatData(classID,isComplex);
    return (*matDataPtr)->FromMxArray(array);
}

//CMatDataType* CMatDataType_Cell::At(const std::vector<mwSize> &indexes)
//{
//    return matData->Ptr(indexes);
//}

bool CMatDataType_Cell::At(const std::vector<mwSize> &indexes,CMatDataType &data)
{
    (*matDataPtr)->Get(indexes,data);
    return true;
}

CMatDataType_Cell& CMatDataType_Cell::operator=(const CMatDataType_Cell &other)
{
    matDataPtr = other.matDataPtr;
    return *this;
}

CMatDataType_Cell::CellData_Proxy CMatDataType_Cell::operator[](mwSize index)
{
    return CellData_Proxy(this,index);
}


CMatDataType_Cell::CMatDataType_Cell() : matDataPtr(new CMatDataBase*(NULL),FreeCell)
{
//    CMatDataBase **pp = new CMatDataBase*;
//    *pp = new CMatData<mxDOUBLE_CLASS, true>({1});

//    matDataPtr = &p;
//    (*matDataPtr) = NULL;
//    matDataPtr = new CMatDataBase*(NULL);
//    matDataPtr.reset(new CMatDataBase*(NULL));
//    *matDataPtr = NULL;
}
