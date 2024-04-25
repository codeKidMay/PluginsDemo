#pragma once

#include "ISample2Plugin.h"

class Sample2Plugin final : public ISample2Plugin
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
    void TestCommandWithParam(WPARAM wParam_, LPARAM lParam_);

private:
    int m_nTestParam;
};
