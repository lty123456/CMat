#include "cmatvariable.h"

CMatDataBase* CreateMatVariableComplex(const std::string name, const mxClassID classID,const std::vector<mwSize> &dims)
{
    switch (classID) {
    case mxCELL_CLASS:
    {
//        return new CMatData<mxCELL_CLASS,true>(dims);
        throw CMatException_UnknowType();
    }break;
    case mxLOGICAL_CLASS:
    {
        return new CMatVariable<mxLOGICAL_CLASS,true>(name,dims);
    }break;
    case mxCHAR_CLASS:
    {
        return new CMatVariable<mxCHAR_CLASS,true>(name,dims);
    }break;
    case mxDOUBLE_CLASS:
    {
        return new CMatVariable<mxDOUBLE_CLASS,true>(name,dims);
    }break;
    case mxSINGLE_CLASS:
    {
        return new CMatVariable<mxSINGLE_CLASS,true>(name,dims);
    }break;
    case mxINT8_CLASS:
    {
        return new CMatVariable<mxINT8_CLASS,true>(name,dims);
    }break;
    case mxUINT8_CLASS:
    {
        return new CMatVariable<mxUINT8_CLASS,true>(name,dims);
    }break;
    case mxINT16_CLASS:
    {
        return new CMatVariable<mxINT16_CLASS,true>(name,dims);
    }break;
    case mxUINT16_CLASS:
    {
        return new CMatVariable<mxUINT16_CLASS,true>(name,dims);
    }break;
    case mxINT32_CLASS:
    {
        return new CMatVariable<mxINT32_CLASS,true>(name,dims);
    }break;
    case mxUINT32_CLASS:
    {
        return new CMatVariable<mxUINT32_CLASS,true>(name,dims);
    }break;
    case mxINT64_CLASS:
    {
        return new CMatVariable<mxINT64_CLASS,true>(name,dims);
    }break;
    case mxUINT64_CLASS:
    {
        return new CMatVariable<mxUINT64_CLASS,true>(name,dims);
    }break;
    default:
        throw CMatException_UnknowType();
        break;
    }

    return NULL;
}

CMatDataBase* CreateMatVariable(const std::string name, const mxClassID classID, bool isComplex, const std::vector<mwSize> &dims)
{
    if(isComplex)
        return CreateMatVariableComplex(name,classID,dims);

    switch (classID) {
    case mxCELL_CLASS:
    {
        return new CMatVariable<mxCELL_CLASS,false>(name,dims);
    }break;
    case mxLOGICAL_CLASS:
    {
        return new CMatVariable<mxLOGICAL_CLASS,false>(name,dims);
    }break;
    case mxCHAR_CLASS:
    {
        return new CMatVariable<mxCHAR_CLASS,false>(name,dims);
    }break;
    case mxDOUBLE_CLASS:
    {
        return new CMatVariable<mxDOUBLE_CLASS,false>(name,dims);
    }break;
    case mxSINGLE_CLASS:
    {
        return new CMatVariable<mxSINGLE_CLASS,false>(name,dims);
    }break;
    case mxINT8_CLASS:
    {
        return new CMatVariable<mxINT8_CLASS,false>(name,dims);
    }break;
    case mxUINT8_CLASS:
    {
        return new CMatVariable<mxUINT8_CLASS,false>(name,dims);
    }break;
    case mxINT16_CLASS:
    {
        return new CMatVariable<mxINT16_CLASS,false>(name,dims);
    }break;
    case mxUINT16_CLASS:
    {
        return new CMatVariable<mxUINT16_CLASS,false>(name,dims);
    }break;
    case mxINT32_CLASS:
    {
        return new CMatVariable<mxINT32_CLASS,false>(name,dims);
    }break;
    case mxUINT32_CLASS:
    {
        return new CMatVariable<mxUINT32_CLASS,false>(name,dims);
    }break;
    case mxINT64_CLASS:
    {
        return new CMatVariable<mxINT64_CLASS,false>(name,dims);
    }break;
    case mxUINT64_CLASS:
    {
        return new CMatVariable<mxUINT64_CLASS,false>(name,dims);
    }break;
    default:
        throw CMatException_UnknowType();
        break;
    }

    return NULL;
}
