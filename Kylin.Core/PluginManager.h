#pragma once
#include "base/AFPlatform.hpp"
#include "base/AFIModule.hpp"
#include "base/AFPluginManager.hpp"

class CPluginManager
{
public:
	CPluginManager();
	bool Initialize();

	template<class IModule> AFIModule* GetModule();

private:
	AFPluginManager* m_pPluginManager;
};

template<class IModule>
inline AFIModule* CPluginManager::GetModule()
{
	return m_pPluginManager->FindModule<IModule>();
}
