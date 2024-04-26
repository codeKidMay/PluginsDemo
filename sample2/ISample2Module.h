#pragma once
#include <string>
#include "IModule.h"

class ISample2Module : public IModule
{
public:
    virtual void ImportFile(const std::string& strFilePath_) = 0;
};