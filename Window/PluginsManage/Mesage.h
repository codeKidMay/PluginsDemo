#pragma once
//定义一个数据包体
#include <vector>
#include <string>
typedef void (*ptrCallFun)(bool, void*);

#define CONTENTREADONLY    0x0
#define CONTENTREADWRITE    0x1
#define CONTENTNOCHANGE      0x00
#define CONTENGHASCHANGE     0x10

struct __declspec(dllexport) MesContent
{
    int nContentFlag;
    char ClassName[50]; //传递的类名称
    void* ptrContent;
};

struct __declspec(dllexport) PlugMessage
{
	const char* Sender;
    const char* Receiver;//每个插件可以给多个插件发消息
    const char* strTopic;
    const char* strGuid;
    MesContent* ptrMesContent;
    ptrCallFun* Callback;
};