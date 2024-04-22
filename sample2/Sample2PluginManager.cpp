#include "Sample2PluginManager.h"

#include "Sample2Plugin.h"

void Sample2PluginManager::Install()
{
    ARK_REGISTER_MODULE(ISample2Plugin, Sample2Plugin);
}

void Sample2PluginManager::Uninstall()
{
    ARK_UNREGISTER_MODULE(ISample2Plugin, Sample2Plugin);
}