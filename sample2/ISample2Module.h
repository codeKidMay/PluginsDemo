#pragma once
#include <string>
#include "interface/AFIPlugin.hpp"
#include "interface/AFIModule.hpp"
#include "base/AFPluginManager.hpp"

namespace ark
{
    class ISample2Module : public AFIModule
    {
    public:
        explicit ISample2Module() = default;

        virtual void ImportFile(const std::string& strFilePath_) = 0;
    };
}