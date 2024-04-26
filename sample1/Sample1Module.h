#pragma once

#include "ISample1Module.h"

class ISample2Module;
class Sample1Module final : public ISample1Module
{
public:
    bool Init() override;
    bool PostInit() override;
    bool Update() override;
    bool PreShut() override;
    bool Shut() override;

public:
    void PartRecognition(const std::string& strFilePath_) override;

protected:
    void TestCommand();
    bool TestSendMessage(WPARAM wParam_, LPARAM lParam_);
    void NotifyTest(WPARAM wParam_, LPARAM lParam_);

private:
    ISample2Module* m_pSample2Module;
};
