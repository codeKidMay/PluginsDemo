#pragma once
#include "interface.h"
#include "PluginsManage.h"
// �̺߳�������  
typedef void* (*ThreadFunc)(void*);

//Ϊĳ�����ר�ſ����߳�
//// 
//// �߳�����  
//struct  __declspec(dllexport) ThreadData {
//    PluginManager* manager;
//    Plugin* plugin;
//
//    void create_and_ExcuteThread(ThreadFunc func, void* arg);
//};
//
