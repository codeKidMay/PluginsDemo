#include "Sample2Plugin.h"

bool Sample2Plugin::Init()
{
    std::cout << GET_CLASS_NAME(Sample2Plugin) << ", Init" << std::endl;

    // �������
    AddCommand("TestCommandNoParam", &Sample2Plugin::TestAddCommand);
    AddMessageCommand("TestCommandNoParam", &Sample2Plugin::TestCommandWithParam);

    return true;
}

bool Sample2Plugin::PostInit()
{
    return true;
}

bool Sample2Plugin::PreShut()
{
    std::cout << GET_CLASS_NAME(Sample2Plugin) << ", PreShut" << std::endl;
    return true;
}

bool Sample2Plugin::Shut()
{
    std::cout << GET_CLASS_NAME(Sample2Plugin) << ", Shut" << std::endl;
    return true;
}

void Sample2Plugin::ImportFile(const std::string& strFilePath_)
{
    MessageBox(NULL, "ִ�е����ļ�", "��ʾ", MB_OK);
}

void Sample2Plugin::TestAddCommand()
{
    m_nTestParam = 100;
}

void Sample2Plugin::TestCommandWithParam(WPARAM wParam_, LPARAM lParam_)
{
    m_nTestParam = wParam_;
}
