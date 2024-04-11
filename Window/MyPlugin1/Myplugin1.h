#pragma once

#ifdef MYLIB_EXPORTS
#define MYLIB_API __declspec(dllexport)
#else
#define MYLIB_API __declspec(dllimport)
#endif


#include <iostream>
#include <windows.h>

#include "..\PluginsManage\Interface.h"
using namespace std;


struct MYLIB_API Mydata 
{
	Mydata() 
		:a(0.)
		,b(0.)
		,c(0.)
	{
	}
	double a;
	double b;
	double c;
};

public class MYLIB_API MyPlugin1 :public Iplugin
{
	typedef void (callback)(void*, void*);
public:
	MyPlugin1(const char* strName_, PluginManager* manager_);
	virtual  void MyPlugin1Run();

	string GetPlugin();
private:
	Mydata plugin1data;
};

extern "C" __declspec(dllexport) Iplugin* CreateMyplugin(PluginManager* manage_);

