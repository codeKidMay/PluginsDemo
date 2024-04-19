#pragma once
#include <string>
#include "base/AFPluginManager.hpp"
#include "interface/AFIPlugin.hpp"
#include "interface/AFIModule.hpp"

class ISample1Module : public AFIModule
{
public:
    virtual void PartRecognition(const std::string& strFilePath_) = 0;
};