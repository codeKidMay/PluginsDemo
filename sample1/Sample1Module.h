#pragma once

#include "ISample1Module.h"
#include "..\sample2\ISample2Module.h"

namespace ark {

class Sample1Module final : public ISample1Module
{
    ARK_DECLARE_MODULE_FUNCTIONS
public:
    bool Init() override;
    bool PostInit() override;
    bool Update() override;
    bool PreShut() override;
    bool Shut() override;

public:
    void PartRecognition(const std::string& strFilePath_) override;

private:
    ISample2Module* m_pSample2Module;
};

}
