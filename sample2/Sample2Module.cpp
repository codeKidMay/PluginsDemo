#include "Sample2Plugin.h"

bool Sample2Module::Init()
{
    std::cout << GET_CLASS_NAME(Sample2Module) << ", Init" << std::endl;

    // 添加命令
    ADD_COMMAND("TestCommandNoParam", &Sample2Module::TestAddCommand);
    ADD_COMMAND_MSG("TestCommandNoParam", &Sample2Module::TestCommandWithParam);

    return true;
}

bool Sample2Module::PostInit()
{
    return true;
}

bool Sample2Module::PreShut()
{
    std::cout << GET_CLASS_NAME(Sample2Module) << ", PreShut" << std::endl;
    return true;
}

bool Sample2Module::Shut()
{
    std::cout << GET_CLASS_NAME(Sample2Module) << ", Shut" << std::endl;
    return true;
}

void Sample2Module::ImportFile(const std::string& strFilePath_)
{
    MessageBox(NULL, "执行导入文件", "提示", MB_OK);
}

void Sample2Module::TestAddCommand()
{
    m_nTestParam = 100;
}

bool Sample2Module::TestCommandWithParam(WPARAM wParam_, LPARAM lParam_)
{
    m_nTestParam = (int)wParam_;
    return true;
}
