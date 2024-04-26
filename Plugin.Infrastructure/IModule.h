#pragma once

#include "base/AFIModule.hpp"
#include "base/AFPluginManager.hpp"

/// <summary>
/// �ⲿģ����ࣺ
/// 1.��AFK��ܵĻ����Ϸḻ�˷������֪ͨ�Ĺ���
/// </summary>
class IModule : public AFIModule
{
public:
    // ��������
    void AddCommand(const std::string& strTopic_, const CommandCallBack& Callback_)
    {
        m_pPluginManager->AddCommand(strTopic_, Callback_);
    }

    void AddCommandMsg(const std::string& strTopic_, const MessageCallBack& Callback_)
    {
        m_pPluginManager->AddCommandMsg(strTopic_, Callback_);
    }

    void AddNotifyMsg(const std::string& strTopic_, const NotifyCallBack& Callback_)
    {
        m_pPluginManager->AddNotifyMsg(strTopic_, Callback_);
    }

    // ��������
    bool SendCommand(const std::string& strCommandName_)
    {
        return m_pPluginManager->SendCommand(strCommandName_);
    }

    // ���ʹ�����������
    bool SendCommandMsg(const std::string& strMsgName_, WPARAM wParam_, LPARAM lParam_)
    {
        return m_pPluginManager->SendCommandMsg(strMsgName_, wParam_, lParam_);
    }

    // ����֪ͨ��Ϣ
    bool SendNotifyMsg(const std::string& strNotifyMsgName_, WPARAM wParam_, LPARAM lParam_)
    {
        return m_pPluginManager->SendNotifyMsg(strNotifyMsgName_, wParam_, lParam_);
    }
};