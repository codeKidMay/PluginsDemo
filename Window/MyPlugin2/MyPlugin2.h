#pragma once



#include <iostream>
#include <windows.h>

#include "..\PluginsManage\Interface.h"
using namespace std;



public class __declspec(dllexport) MyPlugin2 :public Iplugin
{
	typedef void (callback)(void*, void*);
public:
	MyPlugin2(const char* strName_, PluginManager* manager_);

	virtual void MyPlugin1Run();
};

extern "C" __declspec(dllexport) Iplugin * CreateMyplugin(PluginManager * manage_);

