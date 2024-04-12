#pragma once
#include "base/AFPlatform.hpp"
#include "interface/AFIModule.hpp"

class PLUGIN_MANAGE_EXP CPluginManager
{
public:
	CPluginManager();
	bool Initialize();

	template<class IModule> ark::AFIModule* GetModule();
};