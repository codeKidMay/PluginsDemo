#pragma once

#include "interface/AFIPlugin.hpp"
#include "base/AFPluginManager.hpp"

#include "Sample2PluginManager.h"
#include "ISample2Plugin.h"
#include "Sample2Plugin.h"


ARK_DECLARE_PLUGINMANAGER(Sample2PluginManager)

void Sample2PluginManager::Install()
{
    REGISTER_PLUGIN(ISample2Plugin, Sample2Plugin);
}

void Sample2PluginManager::Uninstall()
{
    UNREGISTER_PLUGIN(ISample2Plugin, Sample2Plugin);
}

