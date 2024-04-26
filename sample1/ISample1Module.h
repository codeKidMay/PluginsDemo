#pragma once
#include <string>
#include "IModule.h"

class ISample1Module : public IModule
{
public:
    virtual void PartRecognition(const std::string& strFilePath_) = 0;
};