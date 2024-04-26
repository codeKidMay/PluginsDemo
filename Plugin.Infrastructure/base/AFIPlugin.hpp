#pragma once

#include "base/AFPlatform.hpp"

class AFPluginManager;

class AFIPlugin
{
public:
    virtual ~AFIPlugin() = default;
    virtual const std::string GetPluginName() = 0;

    virtual void Install() = 0;
    virtual void Uninstall() = 0;

    AFPluginManager* GetPluginManager() const { return plugin_manager_; }
    void SetPluginManager(AFPluginManager* p) { plugin_manager_ = p; }

protected:
    AFPluginManager* plugin_manager_{ nullptr };
};
