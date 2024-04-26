#pragma once

#include "ISample2Module.h"

class Sample2Module final : public ISample2Module
{
public:
    bool Init() override;
    bool PostInit() override;
    bool PreShut() override;
    bool Shut() override;

public:
    void ImportFile(const std::string& strFilePath_) override;

protected:
    void TestAddCommand();
    bool TestCommandWithParam(WPARAM wParam_, LPARAM lParam_);

private:
    int m_nTestParam;
};
