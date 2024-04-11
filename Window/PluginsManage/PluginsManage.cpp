#include <windows.h>

#include <thread>
#include <mutex>
#include "PluginsManage.h"
#include "interface.h"


typedef Iplugin* (*CreateInstanceFunc)(PluginManager* manage_);


PluginManager::PluginManager() 
{
	Run();
}
void PluginManager::add_plugin(Iplugin* plugin)
{
	plugins.push_back(plugin);

}
bool PluginManager::RegistSub(std::string strTopic, Iplugin* plugin, CallFun TopicFun)
{
	bool bAddResult = false;
	if (Funmaps.find(strTopic) != Funmaps.end())
	{
		if (Funmaps[strTopic].find(plugin) == Funmaps[strTopic].end())
		{
			Funmaps[strTopic][plugin] = TopicFun;
			bAddResult = true;
		}
	}
	else
	{
		std::map<Iplugin*, CallFun> fristMap;
		fristMap[plugin] = TopicFun;
		Funmaps[strTopic] = fristMap;
		bAddResult = true;
	}
	return bAddResult;
}

bool PluginManager::UnRegistSub(std::string strTopic, Iplugin* plugin)
{
	if (Funmaps.find(strTopic) != Funmaps.end())
	{
		if (Funmaps[strTopic].find(plugin) != Funmaps[strTopic].end())
		{
			Funmaps[strTopic].erase(plugin);
			return true;
		}
	}
	return false;

}

bool PluginManager::AsynPostMessage(const PlugMessage& message)
{
	std::lock_guard<std::mutex> lock(mutex);
	if (Funmaps.find(message.strTopic) == Funmaps.end())
		return false;
	QueueMessage.push(message);
	cv.notify_one();
	return true;
}

bool PluginManager::SynSendMessage(const PlugMessage& message)
{
	if (Funmaps.find(message.strTopic) == Funmaps.end())
		return false;
	for each (auto var in Funmaps[message.strTopic])
	{
		var.second(message);
	}
	return true;
}

void PluginManager::ProcessMessage()
{
	while (running)
	{
		std::unique_lock<std::mutex> lock(mutex);
		cv.wait(lock, [this]() { return !QueueMessage.empty(); });
		auto message = QueueMessage.front();	
		QueueMessage.pop();
		lock.unlock();

		for each (auto var in Funmaps[message.strTopic])
		{
			var.second(message);
		}
	}
}

void startThread(PluginManager& obj)
{
	obj.thread_ = std::thread(&PluginManager::ProcessMessage, &obj);
}

void PluginManager::Run()
{
	startThread(*this);
}

PluginManager* CreatePluginManager()
{

	return new PluginManager;
}

void LoadPlugins(PluginManager *manager, const char* pluginName)
{
	std::string spluginName(pluginName);
	spluginName += ".dll";
	HMODULE hModule = LoadLibraryA(spluginName.c_str());
	if (hModule){
		CreateInstanceFunc createInstance = (CreateInstanceFunc)GetProcAddress(hModule, "CreateMyplugin");
		if (createInstance) 
		{
			Iplugin* plugin = createInstance(manager);
			manager->add_plugin(plugin);
			manager->Reflect.insert(std::pair<std::string, Iplugin*>(plugin-> strPluginName, plugin));
		}
		FreeLibrary(hModule);
	}

}

void RunPlugin(PluginManager* manager,const char* Pluginname)
{
	std::map<std::string, Iplugin*>::iterator iter;
	iter = manager->Reflect.find(Pluginname);
	if (iter != manager->Reflect.end()) 
	{
		manager->Reflect[Pluginname]->MyPlugin1Run();
	}
}

void FreePluginManager(PluginManager* manager)
{
	if (manager!=nullptr) 
	{
		delete manager;
	}
}

