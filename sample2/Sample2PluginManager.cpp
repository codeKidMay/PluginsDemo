#include "Sample2PluginManager.h"
#include "ISample2Plugin.h"
#include "Sample2Plugin.h"

ARK_DECLARE_PLUGIN_DLL_FUNCTION(Sample2PluginManager)

void Sample2PluginManager::Install()
{
    ARK_REGISTER_MODULE(ISample2Plugin, Sample2Plugin);
}

void Sample2PluginManager::Uninstall()
{
    ARK_UNREGISTER_MODULE(ISample2Plugin, Sample2Plugin);
}
