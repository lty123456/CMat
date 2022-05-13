#include "cmatdatabase.h"

CMatDataBase::CMatDataBase()
{

}

std::vector<mwSize> CMatDataBase::GetDimsFromMxArray(mxArray *array)
{
    assert(array);

    mwSize nod = mxGetNumberOfDimensions(array);
    std::vector<mwSize> dims(nod);
    memcpy(dims.data(),mxGetDimensions(array),nod * sizeof(mwSize));
    return dims;
}
