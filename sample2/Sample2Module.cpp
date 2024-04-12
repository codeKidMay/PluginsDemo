#include "Sample2Module.h"

namespace ark {

bool Sample2Module::Init()
{
    std::cout << GET_CLASS_NAME(Sample2Module) << ", Init" << std::endl;
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

} // namespace ark
