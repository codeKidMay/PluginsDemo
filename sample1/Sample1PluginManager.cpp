#include "Sample1PluginManager.h"
#include "Sample1Plugin.h"
#include "IJsonConvertPlugin.h"
#include "JsonConvertPlugin.h"

ARK_DECLARE_PLUGIN_DLL_FUNCTION(Sample1PluginManager)

void Sample1PluginManager::Install()
{
    ARK_REGISTER_MODULE(ISample1Module, Sample1Module);
    ARK_REGISTER_MODULE(IJsonConvertModule, JsonConvertModule);
}

void Sample1PluginManager::Uninstall()
{
    ARK_UNREGISTER_MODULE(ISample1Module, Sample1Module);
    ARK_UNREGISTER_MODULE(IJsonConvertModule, JsonConvertModule);
}
