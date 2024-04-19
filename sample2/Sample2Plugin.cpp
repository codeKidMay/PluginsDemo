#include "Sample2Plugin.h"

bool Sample2Plugin::Init()
{
    std::cout << GET_CLASS_NAME(Sample2Plugin) << ", Init" << std::endl;
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
    MessageBox(NULL, "执行导入文件", "提示", MB_OK);
}
