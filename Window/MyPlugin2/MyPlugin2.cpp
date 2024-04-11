#include "MyPlugin2.h"
using namespace System;
using namespace System::Windows;
typedef void (*ptrCallFun)(bool, void*);
struct  Mydata
{
	Mydata()
		:a(0.)
		, b(0.)
		, c(0.)
	{
	}
	double a;
	double b;
	double c;
};
struct ResStruct
{
	double a1;
	double b1;
	double c1;
};

void CallFunction(PlugMessage message)
{
	//MessageBox::Show("Hello, World!", "My Message Box");
	Mydata* revData = (Mydata*)message.ptrMesContent->ptrContent;
	ResStruct resp;
	resp.a1 = revData->a + 100;
	resp.b1 = revData->b + 100;
	resp.c1 = revData->c + 100;
	((ptrCallFun)message.Callback)(true, &resp);
}



MyPlugin2::MyPlugin2(const char* strName_, PluginManager* manager_)
	:Iplugin(strName_, manager_)
{
	RegeditTopic("CalcVolume", CallFunction);
}

void MyPlugin2::MyPlugin1Run()
{
}

Iplugin* CreateMyplugin(PluginManager* manage_) 
{
	return new MyPlugin2("plugin2", manage_);
}
