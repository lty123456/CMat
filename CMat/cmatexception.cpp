#include "cmatexception.h"

CMatException::CMatException(const std::string &message) : msg(message)
{

}

char const * CMatException::what() const noexcept
{
    return msg.c_str();
}

CMatException_DimsOutRange::CMatException_DimsOutRange() : CMatException("Dims out of range")
{

}

CMatException_IndexOutRange::CMatException_IndexOutRange() : CMatException("Index out of range")
{

}

CMatException_TypeDiff::CMatException_TypeDiff() : CMatException("Can not conversation to same type")
{

}

CMatException_UnknowType::CMatException_UnknowType() : CMatException("Unkonw Type")
{

}

CMatException_OpenMatFileFailed::CMatException_OpenMatFileFailed() : CMatException("Open mat file failed")
{

}
