#include "Sample1Plugin.h"
#include "Sample1Module.h"
#include "IJsonConvertModule.h"
#include "JsonConvertModule.h"

namespace ark {

ARK_DECLARE_PLUGIN_DLL_FUNCTION(Sample1Plugin)

void Sample1Plugin::Install()
{
    ARK_REGISTER_MODULE(ISample1Module, Sample1Module);
    ARK_REGISTER_MODULE(IJsonConvertModule, JsonConvertModule);
}

void Sample1Plugin::Uninstall()
{
    ARK_UNREGISTER_MODULE(ISample1Module, Sample1Module);
    ARK_UNREGISTER_MODULE(IJsonConvertModule, JsonConvertModule);
}

} // namespace ark
