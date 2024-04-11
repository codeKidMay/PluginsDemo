#pragma once
//����һ�����ݰ���
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
    char ClassName[50]; //���ݵ�������
    void* ptrContent;
};

struct __declspec(dllexport) PlugMessage
{
	const char* Sender;
    const char* Receiver;//ÿ��������Ը�����������Ϣ
    const char* strTopic;
    const char* strGuid;
    MesContent* ptrMesContent;
    ptrCallFun* Callback;
};