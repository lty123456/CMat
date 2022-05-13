#ifndef CMATFILE_H
#define CMATFILE_H

#include "cmatvariable.h"

#include <string>

class CMatFile
{
public:
    CMatFile(std::string file, const char *mode);
    ~CMatFile();

    void Close();

    CMatDataBase* Read(const char *name);

    CMatDataBase* ReadNext();

    template<mxClassID classID,bool isComplex>
    bool Write(CMatVariable<classID,isComplex> &v);

protected:
    MATFile *matFile;
};

template<mxClassID classID,bool isComplex>
bool CMatFile::Write(CMatVariable<classID,isComplex> &v)
{
    mxArray* array = v.CreateMXArray();
    matPutVariable(matFile,v.name.c_str(),array);
    mxDestroyArray(array);
    return true;
}

#endif // CMATFILE_H
