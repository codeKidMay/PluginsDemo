#pragma once
#include "base/AFPlatform.hpp"
#include "interface/AFIModule.hpp"
#include "base/AFPluginManager.hpp"

class PLUGIN_MANAGE_EXP CPluginManager
{
public:
	CPluginManager();
	bool Initialize();

	template<class IModule> ark::AFIModule* GetModule();

private:
	ark::AFPluginManager* m_pPluginManager;
};

template<class IModule>
inline ark::AFIModule* CPluginManager::GetModule()
{
	return m_pPluginManager->FindModule<IModule>();
}
