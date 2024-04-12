#pragma once

#include "ISample2Module.h"

namespace ark {

class Sample2Module final : public ISample2Module
{
    ARK_DECLARE_MODULE_FUNCTIONS
public:
    explicit Sample2Module() = default;

    bool Init() override;
    bool PostInit() override;
    bool PreShut() override;
    bool Shut() override;

public:
    void ImportFile(const std::string& strFilePath_) override;
};

}
