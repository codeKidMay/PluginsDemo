#pragma once

#include "base/AFIPlugin.hpp"
#include "base/AFPluginManager.hpp"

#include "Sample2Plugin.h"
#include "Sample2Module.h"


ARK_DECLARE_PLUGINMANAGER(Sample2Plugin)

void Sample2Plugin::Install()
{
    REGISTER_PLUGIN(ISample2Module, Sample2Module);
}

void Sample2Plugin::Uninstall()
{
    UNREGISTER_PLUGIN(ISample2Module, Sample2Module);
}

