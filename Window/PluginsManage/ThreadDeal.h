#pragma once
#include "interface.h"
#include "PluginsManage.h"
// 线程函数类型  
typedef void* (*ThreadFunc)(void*);

//为某个插件专门开辟线程
//// 
//// 线程数据  
//struct  __declspec(dllexport) ThreadData {
//    PluginManager* manager;
//    Plugin* plugin;
//
//    void create_and_ExcuteThread(ThreadFunc func, void* arg);
//};
//
