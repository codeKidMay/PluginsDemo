#include <iostream>
#include "Sample1Plugin.h"
#include "../sample2/ISample2Module.h"

bool Sample1Module::Init()
{
    std::cout << GET_CLASS_NAME(Sample1Module) << ", Init" << std::endl;
    m_pSample2Module = FindModule<ISample2Module>();

    ADD_COMMAND("TestSendMsg", &Sample1Module::TestCommand);
    ADD_COMMAND_MSG("TestSendMsg", &Sample1Module::TestSendMessage);
    ADD_NOTIFY_MSG("TestNotify", &Sample1Module::NotifyTest);

    return true;
}

bool Sample1Module::PostInit()
{
    return true;
}

bool Sample1Module::Update()
{
    return true;
}

bool Sample1Module::PreShut()
{
    return true;
}

bool Sample1Module::Shut()
{
    return true;
}

void Sample1Module::PartRecognition(const std::string& strFilePath_)
{
    m_pSample2Module->ImportFile(strFilePath_);

    MessageBox(NULL, "执行零件识别", "提示", MB_OK);
}

void Sample1Module::TestCommand()
{
    MessageBox(NULL, "Sample1测试命令", "提示", MB_OK);
}

bool Sample1Module::TestSendMessage(WPARAM wParam_, LPARAM lParam_)
{
    MessageBox(NULL, "Sample1测试消息", "提示", MB_OK);
    return true;
}

void Sample1Module::NotifyTest(WPARAM wParam_, LPARAM lParam_)
{
    MessageBox(NULL, "Sample1测试订阅", "提示", MB_OK);
}
