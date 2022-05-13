#ifndef CMATVARIABLE_H
#define CMATVARIABLE_H

#include <string>

#include "cmatdata_cell.h"
#include "cmatdata_arithmetic.h"

template<mxClassID classID,bool isComplex>
class CMatVariable : public CMatData<classID,isComplex>
{
public:
    CMatVariable(std::string name,const std::vector<mwSize> &dims = {1,1},bool unbuffered = true) : CMatData<classID, isComplex> (dims,unbuffered),name(name)
    {

    }

    virtual ~CMatVariable()
    {

    }

    std::string name;
};

CMatDataBase* CreateMatVariableComplex(const std::string name, const mxClassID classID, const std::vector<mwSize> &dims = {1,1});

CMatDataBase* CreateMatVariable(const std::string name, const mxClassID classID, bool isComplex, const std::vector<mwSize> &dims = {1,1});

#endif // CMATVARIABLE_H
