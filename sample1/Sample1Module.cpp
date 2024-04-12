#include <iostream>
#include "base/AFMacros.hpp"
#include "Sample1Module.h"

namespace ark {

bool Sample1Module::Init()
{
    m_pSample2Module = FindModule<ISample2Module>();

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

    std::cout << "执行零件识别" << std::endl;
}

}
