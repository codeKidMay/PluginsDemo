#include <iostream>
#include "base/AFMacros.hpp"
#include "Sample1Plugin.h"

bool Sample1Module::Init()
{
    std::cout << GET_CLASS_NAME(Sample1Module) << ", Init" << std::endl;
    m_pSample2Module = FindModule<ISample2Plugin>();

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
