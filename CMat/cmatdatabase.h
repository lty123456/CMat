#ifndef CMATDATABASE_H
#define CMATDATABASE_H

#include "cmatdatatype.h"
#include <vector>

class CMatDataBase
{
public:
    CMatDataBase();

    virtual ~CMatDataBase(){}

    virtual bool IsComplex() const = 0;

    virtual mxClassID Type() = 0;

    virtual const std::vector<mwSize>& Dims() = 0;

    virtual mwSize Size() = 0;

    virtual bool Resize(const std::vector<mwSize> &dims) = 0;

    virtual bool Get(const mwSize index, CMatDataType &data) = 0;

    virtual bool Get(const std::vector<mwSize> &indexes, CMatDataType &data) = 0;

    virtual mxArray* CreateMXArray() = 0;

    virtual bool FromMxArray(mxArray *array) = 0;

    static std::vector<mwSize> GetDimsFromMxArray(mxArray *array);
};
#endif // CMATDATABASE_H
