#pragma once

#include "base/AFIPlugin.hpp"
#include "base/AFPluginManager.hpp"

#include "Sample1Module.h"

ARK_DECLARE_PLUGINMANAGER(Sample1Plugin)

void Sample1Plugin::Install()
{
    REGISTER_PLUGIN(ISample1Module, Sample1Module);
}

void Sample1Plugin::Uninstall()
{
    UNREGISTER_PLUGIN(ISample1Module, Sample1Module);
}
