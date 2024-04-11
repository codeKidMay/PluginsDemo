#define MYLIB_EXPORTS
#include <windows.h>
#include <thread>
#include "..\PluginsManage\PluginsManage.h"
#include "Myplugin1.h"

using namespace System;
using namespace System::Windows;
typedef void (*ptrCallFun)(bool, void*);
struct ResStruct
{
	double a1;
	double b1;
	double c1;
};
void callbackResult(bool res, void* resPtr)
{
	//cout << res << endl;
	ResStruct* res_ = (ResStruct*)resPtr;
	//cout << res_->a1 << "    " << res_->b1 << "    " << res_->c1 << endl;
	MessageBox::Show(res.ToString());
	MessageBox::Show(res_->a1.ToString());
	MessageBox::Show(res_->b1.ToString());
	MessageBox::Show(res_->c1.ToString());
	//MessageBox::Show("Hello, World!", "My Message Box");
}



MyPlugin1::MyPlugin1(const char* strName_, PluginManager* manager_)
	:Iplugin(strName_, manager_)
{
	//RegeditTopic("CalcVolume", CallFunction);
}

void MyPlugin1::MyPlugin1Run()
{

	Plugin1Window::MainWindow^ wd1 = gcnew Plugin1Window::MainWindow();
	wd1->ShowDialog();
	if (wd1->DialogResult) 
	{
		Plugin1Window::ModelData^ s1 = wd1->getUIData();
		this->plugin1data.a = s1->width;
		this->plugin1data.b = s1->height;
		this->plugin1data.c = s1->Area;

		//组织消息
		PlugMessage message;
		message.Sender = "plugin1";
		message.Receiver = "plugin2";
		message.strTopic = "CalcVolume";
		message.ptrMesContent->ptrContent = (void*)&plugin1data;
		message.Callback = (ptrCallFun*)callbackResult;
		this->manager->SynSendMessage(message);
	}
	else
		std::cout << "不发消息" << endl;


	
}


string MyPlugin1::GetPlugin()
{
	return strPluginName;
}



Iplugin* CreateMyplugin(PluginManager* manage_)
{

	return new MyPlugin1("plugin1", manage_);
}
