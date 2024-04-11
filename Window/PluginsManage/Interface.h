// ²å¼þ½Ó¿Ú  
#pragma once


#include <string>
#include "Mesage.h"
#include "PluginsManage.h"
class PluginManager;

typedef void (*CallFun)(PlugMessage);

typedef void(*Callback)();
public class __declspec(dllexport) Iplugin
{
public:
	Iplugin(const char* strName_, PluginManager* manager_) 
	{
		strPluginName = strName_;
		manager = manager_;
	}

	virtual void MyPlugin1Run() = 0;

	bool RegeditTopic(std::string topic, CallFun ptr_callFun)
	{
		return manager->RegistSub(topic, this, ptr_callFun);
	}

	bool UnRegeditTopic(std::string topic) 
	{
		return manager->UnRegistSub(topic, this);
	}
public:
	std::string strPluginName;
public:
	PluginManager* manager;
};


