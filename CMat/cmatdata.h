#ifndef CMATDATA_H
#define CMATDATA_H

#include "cmatdatabase.h"
#include "cmatdatatype_cell.h"
#include "cmatcomplexarray.h"

template<mxClassID classID,bool isComplex>
class CMatData
{
public:
    CMatData()
    {
        static_assert (true,"Not supported at the moment" );
    }
};

CMatDataBase* CreateMatDataComplex(const mxClassID classID,const std::vector<mwSize> &dims = {1,1});

CMatDataBase* CreateMatData(const mxClassID classID,bool isComplex,const std::vector<mwSize> &dims = {1,1});

#endif // CMATDATA_H
