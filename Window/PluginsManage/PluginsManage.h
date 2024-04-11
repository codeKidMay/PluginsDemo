#pragma once
#include <queue>
#include <map>
#include <string>
#include <mutex>
#include "Mesage.h"
class Iplugin;

typedef void (*CallFun)(PlugMessage);

public class __declspec(dllexport) PluginManager
{
public:
	PluginManager();
	friend void startThread(PluginManager& obj);

public:
	void Run();
	void add_plugin(Iplugin* plugin);
	bool AsynPostMessage(const PlugMessage& message);
	bool SynSendMessage(const PlugMessage& message);//同步消息
	void ProcessMessage();
	bool RegistSub(std::string strTopic, Iplugin* plugin, CallFun TopicFun);//注册消息响应函数
	bool UnRegistSub(std::string strTopic, Iplugin* plugin);
public:
	std::mutex mutex;
	std::condition_variable cv;
	bool running;
	std::queue<PlugMessage> QueueMessage;
	std::vector<Iplugin*> plugins;
	std::map<std::string, Iplugin*> Reflect;
	std::map<std::string, std::map<Iplugin*, CallFun>> Funmaps;
	std::thread thread_;
};


extern "C" __declspec(dllexport) PluginManager* CreatePluginManager();
extern "C" __declspec(dllexport) void LoadPlugins(PluginManager* manager,const char* Pluginname);
extern "C" __declspec(dllexport)  void RunPlugin(PluginManager * manager,const char* Pluginname);
extern "C" __declspec(dllexport)  void FreePluginManager(PluginManager * manager);