#pragma once
#include <string>
#include "interface/AFIPlugin.hpp"
#include "interface/AFIModule.hpp"
#include "base/AFPluginManager.hpp"

class ISample2Plugin : public AFIModule
{
public:
    virtual void ImportFile(const std::string& strFilePath_) = 0;
};