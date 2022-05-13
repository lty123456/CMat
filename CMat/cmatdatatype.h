#ifndef CMATDATATYPE_H
#define CMATDATATYPE_H

#include "mat.h"
#include <string>

class CMatDataType
{
public:
    CMatDataType();

    virtual ~CMatDataType();

    virtual mxClassID Type();

    virtual bool IsComplex() = 0;
};

#endif // CMATDATATYPE_H
