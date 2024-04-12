#include <iostream>
#include "base/AFPluginManager.hpp"
#include "PluginManager.h"

using namespace ark;

static std::filesystem::path getExeDirectory() {
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::filesystem::path exePath(buffer);
	return exePath.parent_path();
}

static bool CollectPlugins(std::filesystem::path& strPluginDir_, std::unordered_map<std::string, std::string>& mapPlugins_)
{
	for (const auto& entry : std::filesystem::directory_iterator(strPluginDir_))
	{
		if (entry.is_regular_file() && entry.path().extension() == ".dll" &&
			entry.path().filename().string().find("Plugin.") == 0) 
		{
			std::string _strPluginName = entry.path().filename().string().substr(0, entry.path().filename().string().size() - 4);
			mapPlugins_.insert(std::make_pair(_strPluginName, entry.path().filename().string()));
		}
	}

	return true;
}

CPluginManager::CPluginManager()
{
	m_pPluginManager = ark::AFPluginManager::instance();
}

bool CPluginManager::Initialize()
{
	std::string plugin_conf_dir;
	std::unordered_map<std::string, std::string> _mapPlugins;
	std::filesystem::path strPluginDir_ = getExeDirectory();
	strPluginDir_ /= "Plugins\\";
	CollectPlugins(strPluginDir_, _mapPlugins);
	m_pPluginManager->Start(0, strPluginDir_.string(), plugin_conf_dir, _mapPlugins);

	return true;
}
