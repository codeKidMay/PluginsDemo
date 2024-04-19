#pragma once

#include "ISample2Plugin.h"

class Sample2Plugin final : public ISample2Plugin
{
    ARK_DECLARE_MODULE_FUNCTIONS
public:
    explicit Sample2Plugin() = default;

    bool Init() override;
    bool PostInit() override;
    bool PreShut() override;
    bool Shut() override;

public:
    void ImportFile(const std::string& strFilePath_) override;
};
