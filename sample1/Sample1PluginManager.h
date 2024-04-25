#pragma once

#include "interface/AFIPlugin.hpp"
#include "base/AFPluginManager.hpp"

#include "Sample1Plugin.h"
#include "IJsonConvertPlugin.h"
#include "JsonConvertPlugin.h"

ARK_DECLARE_PLUGINMANAGER(Sample1PluginManager)

void Sample1PluginManager::Install()
{
    REGISTER_PLUGIN(ISample1Module, Sample1Module);
    REGISTER_PLUGIN(IJsonConvertModule, JsonConvertModule);
}

void Sample1PluginManager::Uninstall()
{
    UNREGISTER_PLUGIN(ISample1Module, Sample1Module);
    UNREGISTER_PLUGIN(IJsonConvertModule, JsonConvertModule);
}
