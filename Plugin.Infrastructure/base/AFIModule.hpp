#pragma once

#include "base/AFMacros.hpp"

class AFPluginManager;

class AFIModule
{
public:
    AFIModule() = default;
    virtual ~AFIModule() = default;

    AFPluginManager* GetPluginManager() const { return m_pPluginManager; }
    void SetPluginManager(AFPluginManager* p) { m_pPluginManager = p; }

    const std::string& GetName() const { return m_strName; }
    void SetName(const std::string& value) { m_strName = value; }

public:
    virtual bool Init() { return true; }
    virtual bool PostInit() { return true; }
    virtual bool PreUpdate() { return true; }
    virtual bool Update() { return true; }
    virtual bool PreShut() { return true; }
    virtual bool Shut() { return true; }

protected:
    template<typename MODULE>
    MODULE* FindModule()
    {
        return GetPluginManager()->template FindModule<MODULE>();
    }

    AFPluginManager* m_pPluginManager{ nullptr };
    std::string m_strName;
};

