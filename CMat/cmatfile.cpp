#include "cmatfile.h"

CMatFile::CMatFile(std::string file,const char *mode) : matFile(NULL)
{
    if(!(matFile = matOpen(file.c_str(),mode)))
        throw CMatException_OpenMatFileFailed();

}

CMatFile::~CMatFile()
{
    Close();
}

void CMatFile::Close()
{
    if(matFile)
    {
        matClose(matFile);
        matFile = NULL;
    }
}

CMatDataBase* CMatFile::Read(const char *name)
{
    mxArray *array = matGetVariable(matFile,name);
    if(!array)
        return NULL;

    mxClassID classID = mxGetClassID(array);
    bool isComplex = mxIsComplex(array);
//    std::vector<mwSize> dims = CMatDataBase::GetDimsFromMxArray(array);

    CMatDataBase* next = CreateMatVariable(name,classID,isComplex/*,dims*/);

    if(!next->FromMxArray(array))
    {
        delete next;
        next = NULL;
    }
    mxDestroyArray(array);
    return next;
}

CMatDataBase* CMatFile::ReadNext()
{
    const char *name;
    mxArray *array = matGetNextVariable(matFile,&name);
    if(!array)
        return NULL;

    mxClassID classID = mxGetClassID(array);
    bool isComplex = mxIsComplex(array);
//    std::vector<mwSize> dims = CMatDataBase::GetDimsFromMxArray(array);

    CMatDataBase* next = CreateMatVariable(name,classID,isComplex/*,dims*/);

    if(!next->FromMxArray(array))
    {
        delete next;
        next = NULL;
    }
    mxDestroyArray(array);
    return next;
}
