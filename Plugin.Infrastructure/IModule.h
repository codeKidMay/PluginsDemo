#pragma once

#include "base/AFIModule.hpp"
#include "base/AFPluginManager.hpp"

/// <summary>
/// 外部模块基类：
/// 1.在AFK框架的基础上丰富了发送命令、通知的功能
/// </summary>
class IModule : public AFIModule
{
public:
    // 订阅主题
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

    // 发送命令
    bool SendCommand(const std::string& strCommandName_)
    {
        return m_pPluginManager->SendCommand(strCommandName_);
    }

    // 发送带参数的命令
    bool SendCommandMsg(const std::string& strMsgName_, WPARAM wParam_, LPARAM lParam_)
    {
        return m_pPluginManager->SendCommandMsg(strMsgName_, wParam_, lParam_);
    }

    // 发送通知消息
    bool SendNotifyMsg(const std::string& strNotifyMsgName_, WPARAM wParam_, LPARAM lParam_)
    {
        return m_pPluginManager->SendNotifyMsg(strNotifyMsgName_, wParam_, lParam_);
    }
};