#ifndef CMATEXCEPTION_H
#define CMATEXCEPTION_H

#include <exception>
#include <string>

class CMatException : public std::exception
{
public:
    CMatException(const std::string &message);

    virtual char const * what() const noexcept override;

private:
    std::string msg;
};

class CMatException_DimsOutRange : public CMatException
{
public:
    CMatException_DimsOutRange();
};

class CMatException_IndexOutRange : public CMatException
{
public:
    CMatException_IndexOutRange();
};

class CMatException_TypeDiff : public CMatException
{
public:
    CMatException_TypeDiff();
};

class CMatException_UnknowType : public CMatException
{
public:
    CMatException_UnknowType();
};

class CMatException_OpenMatFileFailed : public CMatException
{
public:
    CMatException_OpenMatFileFailed();
};

#endif // CMATEXCEPTION_H
