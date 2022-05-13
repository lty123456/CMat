#include "cmatdata.h"
#include "cmatdata_cell.h"
#include "cmatdata_arithmetic.h"

CMatDataBase* CreateMatDataComplex(const mxClassID classID,const std::vector<mwSize> &dims)
{    
    switch (classID) {
    case mxCELL_CLASS:
    {
//        return new CMatData<mxCELL_CLASS,true>(dims);
        throw CMatException_UnknowType();
    }break;
    case mxLOGICAL_CLASS:
    {
        return new CMatData<mxLOGICAL_CLASS,true>(dims);
    }break;
    case mxCHAR_CLASS:
    {
        return new CMatData<mxCHAR_CLASS,true>(dims);
    }break;
    case mxDOUBLE_CLASS:
    {
        return new CMatData<mxDOUBLE_CLASS,true>(dims);
    }break;
    case mxSINGLE_CLASS:
    {
        return new CMatData<mxSINGLE_CLASS,true>(dims);
    }break;
    case mxINT8_CLASS:
    {
        return new CMatData<mxINT8_CLASS,true>(dims);
    }break;
    case mxUINT8_CLASS:
    {
        return new CMatData<mxUINT8_CLASS,true>(dims);
    }break;
    case mxINT16_CLASS:
    {
        return new CMatData<mxINT16_CLASS,true>(dims);
    }break;
    case mxUINT16_CLASS:
    {
        return new CMatData<mxUINT16_CLASS,true>(dims);
    }break;
    case mxINT32_CLASS:
    {
        return new CMatData<mxINT32_CLASS,true>(dims);
    }break;
    case mxUINT32_CLASS:
    {
        return new CMatData<mxUINT32_CLASS,true>(dims);
    }break;
    case mxINT64_CLASS:
    {
        return new CMatData<mxINT64_CLASS,true>(dims);
    }break;
    case mxUINT64_CLASS:
    {
        return new CMatData<mxUINT64_CLASS,true>(dims);
    }break;
    default:
        throw CMatException_UnknowType();
        break;
    }

    return NULL;
}

CMatDataBase* CreateMatData(const mxClassID classID,bool isComplex,const std::vector<mwSize> &dims)
{
    if(isComplex)
        return CreateMatDataComplex(classID,dims);

    switch (classID) {
    case mxCELL_CLASS:
    {
        return new CMatData<mxCELL_CLASS,false>(dims);
    }break;
    case mxLOGICAL_CLASS:
    {
        return new CMatData<mxLOGICAL_CLASS,false>(dims);
    }break;
    case mxCHAR_CLASS:
    {
        return new CMatData<mxCHAR_CLASS,false>(dims);
    }break;
    case mxDOUBLE_CLASS:
    {
        return new CMatData<mxDOUBLE_CLASS,false>(dims);
    }break;
    case mxSINGLE_CLASS:
    {
        return new CMatData<mxSINGLE_CLASS,false>(dims);
    }break;
    case mxINT8_CLASS:
    {
        return new CMatData<mxINT8_CLASS,false>(dims);
    }break;
    case mxUINT8_CLASS:
    {
        return new CMatData<mxUINT8_CLASS,false>(dims);
    }break;
    case mxINT16_CLASS:
    {
        return new CMatData<mxINT16_CLASS,false>(dims);
    }break;
    case mxUINT16_CLASS:
    {
        return new CMatData<mxUINT16_CLASS,false>(dims);
    }break;
    case mxINT32_CLASS:
    {
        return new CMatData<mxINT32_CLASS,false>(dims);
    }break;
    case mxUINT32_CLASS:
    {
        return new CMatData<mxUINT32_CLASS,false>(dims);
    }break;
    case mxINT64_CLASS:
    {
        return new CMatData<mxINT64_CLASS,false>(dims);
    }break;
    case mxUINT64_CLASS:
    {
        return new CMatData<mxUINT64_CLASS,false>(dims);
    }break;
    default:
        throw CMatException_UnknowType();
        break;
    }

    return NULL;
}
