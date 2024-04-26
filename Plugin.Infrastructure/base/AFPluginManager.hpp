#pragma once

#include "base/AFDynLib.hpp"
#include "base/AFIPlugin.hpp"
#include "base/AFIModule.hpp"

class AFPluginManager
{
public:
    static auto instance() -> AFPluginManager*
    {
        static AFPluginManager* instance_ = nullptr;
        if (instance_ == nullptr)
        {
            instance_ = new AFPluginManager();
        }

        return instance_;
    }

    auto Start(int64_t const timestamp, std::string const& lib_dir, std::string const& conf_dir,
        std::unordered_map<std::string, std::string> const& plugins) -> bool
    {
        plugin_library_dir_ = lib_dir;
        plugins_ = plugins;

        ARK_ASSERT_RET_VAL(Init(), false);
        ARK_ASSERT_RET_VAL(PostInit(), false);
        ARK_ASSERT_RET_VAL(PreUpdate(), false);

        return true;
    }

    auto Stop(const int64_t timestamp) -> bool
    {
        PreShut();
        Shut();

        return true;
    }

    auto Update(const int64_t timestamp) -> bool
    {
        // Just loop the modules which have update function.
        for (const auto& iter : module_updates_)
        {
            AFIModule* pModule = iter.second;
            ARK_ASSERT_CONTINUE(pModule != nullptr);

            pModule->Update();
        }

        return true;
    }

    template<typename DerivedModule>
    auto FindModule() -> DerivedModule*
    {
        AFIModule* pLogicModule = FindModule(GET_CLASS_NAME(DerivedModule));
        ARK_ASSERT_RET_VAL(pLogicModule != nullptr, nullptr);

        using derived_type =
            typename std::enable_if<std::is_base_of<AFIModule, DerivedModule>::value, DerivedModule>::type;

        auto derived_module = dynamic_cast<derived_type*>(pLogicModule);
        ARK_ASSERT_RET_VAL(derived_module != nullptr, nullptr);

        return derived_module;
    }

    template<typename PLUGIN_TYPE>
    void Register(std::string const& plugin_name)
    {
        AFIPlugin* pNewPlugin = new PLUGIN_TYPE();
        std::string runtime_plugin_name = GET_CLASS_NAME(PLUGIN_TYPE);
        Register(pNewPlugin, plugin_name, runtime_plugin_name);
    }

    template<typename PLUGIN_TYPE>
    void Unregister()
    {
        //! Delete plugin memory in Unregister
        Unregister(GET_CLASS_NAME(PLUGIN_TYPE));
    }

    auto AddModule(const std::string& module_name, AFIModule* module_ptr) -> bool
    {
        ARK_ASSERT_RET_VAL(!module_name.empty(), false);
        ARK_ASSERT_RET_VAL(FindModule(module_name) == nullptr, false);
        return module_instances_.insert(std::make_pair(module_name, module_ptr)).second;
    }

    void RemoveModule(const std::string& module_name)
    {
        auto iter = module_instances_.find(module_name);
        if (iter == module_instances_.end())
        {
            return;
        }

        module_instances_.erase(module_name);
    }

    auto AddUpdateModule(AFIModule* pModule) -> bool
    {
        ARK_ASSERT_RET_VAL(pModule != nullptr, false);
        return module_updates_.insert(std::make_pair(pModule->GetName(), pModule)).second;
    }

    void RemoveUpdateModule(const std::string& module_name)
    {
        module_updates_.erase(module_name);
    }

public:
    void AddCommand(const std::string& strTopic_, const CommandCallBack& Callback_)
    {
        m_mapCommands.insert(std::make_pair(strTopic_, Callback_));
    }

    void AddCommandMsg(const std::string& strTopic_, const MessageCallBack& Callback_)
    {
        m_mapFunctions.insert(std::make_pair(strTopic_, Callback_));
    }

    void AddNotifyMsg(const std::string& strTopic_, const NotifyCallBack& Callback_)
    {
        m_mapNotifyFunctions[strTopic_].push_back(Callback_);
    }

    // 发送命令
    bool SendCommand(const std::string& strCommandName_)
    {
        auto _iter = m_mapCommands.find(strCommandName_);
        if (_iter != m_mapCommands.end())
        {
            m_mapCommands[strCommandName_]();
            return true;
        }

        return false;
    }

    // 发送带参数的命令
    bool SendCommandMsg(const std::string& strMsgName_, WPARAM wParam_, LPARAM lParam_)
    {
        auto _iter = m_mapFunctions.find(strMsgName_);
        if (_iter != m_mapFunctions.end())
        {
            return m_mapFunctions[strMsgName_](wParam_, lParam_);
        }

        return false;
    }

    // 发送通知消息
    bool SendNotifyMsg(const std::string& strNotifyMsgName_, WPARAM wParam_, LPARAM lParam_)
    {
        auto _iter = m_mapNotifyFunctions.find(strNotifyMsgName_);
        if (_iter != m_mapNotifyFunctions.end())
        {
            for (auto& _NotifyCallback : _iter->second)
            {
                _NotifyCallback(wParam_, lParam_);
            }
            return true;
        }

        return false;
    }

protected:
    void Register(AFIPlugin* plugin, std::string const& plugin_name, std::string const& runtime_plugin_name)
    {
        // e.g. plugin_name = class AFKernelPlugin
        // It's a runtime name, so we cannot use it to find the plugin.conf file.
        //std::string plugin_name = plugin->GetPluginName();

        ARK_ASSERT_RET_NONE(FindPlugin(plugin_name) == nullptr);

        auto iter = plugins_.find(plugin_name);
        ARK_ASSERT_NO_EFFECT(iter != plugins_.end());

        plugin->SetPluginManager(this);
        // Install modules
        plugin->Install();
        // manage this plugin
        plugin_instances_.insert(std::make_pair(runtime_plugin_name, plugin));
    }

    void Unregister(const std::string& plugin_name)
    {
        ARK_ASSERT_RET_NONE(!plugin_name.empty());

        auto plugin = FindPlugin(plugin_name);
        ARK_ASSERT_RET_NONE(plugin != nullptr);

        plugin->Uninstall();
        plugin_instances_.erase(plugin_name);
        delete plugin;
        plugin = nullptr;
    }

    auto FindPlugin(const std::string& plugin_name) -> AFIPlugin*
    {
        auto iter = plugin_instances_.find(plugin_name);
        if (iter != plugin_instances_.end())
        {
            return iter->second;
        }
        else
        {
            return nullptr;
        }
    }

    template<typename PLUGIN_TYPE>
    auto FindPlugin() -> AFIPlugin*
    {
        using derived_type = typename std::enable_if<std::is_base_of<AFIPlugin, PLUGIN_TYPE>::value, PLUGIN_TYPE>::type;
        auto plugin_name = GET_CLASS_NAME(derived_type);
        auto iter = plugin_instances_.find(plugin_name);
        if (iter != plugin_instances_.end())
        {
            return iter->second;
        }
        else
        {
            return nullptr;
        }
    }

    auto FindModule(const std::string& module_name) -> AFIModule*
    {
        auto iter = module_instances_.find(module_name);
        return ((iter != module_instances_.end()) ? iter->second : nullptr);
    }

    auto Init() -> bool
    {
        // load plugin dynamic libraries
        for (auto const& iter : plugins_)
        {
            bool ret = LoadPluginLibrary(iter.first);
            ARK_ASSERT_RET_VAL(ret, false);
        }

        // initialize all modules
        for (auto const& iter : module_instances_)
        {
            AFIModule* pModule = iter.second;
            ARK_ASSERT_CONTINUE(pModule != nullptr);

            pModule->Init();
        }

        return true;
    }

    auto PostInit() -> bool
    {
        for (auto const& iter : module_instances_)
        {
            AFIModule* pModule = iter.second;
            ARK_ASSERT_CONTINUE(pModule != nullptr);

            pModule->PostInit();
        }

        return true;
    }

    auto PreUpdate() -> bool
    {
        for (auto const& iter : module_instances_)
        {
            AFIModule* pModule = iter.second;
            ARK_ASSERT_CONTINUE(pModule != nullptr);

            pModule->PreUpdate();
        }

        return true;
    }

    auto PreShut() -> bool
    {
        for (auto const& iter : module_instances_)
        {
            AFIModule* pModule = iter.second;
            ARK_ASSERT_CONTINUE(pModule != nullptr);

            pModule->PreShut();
        }

        return true;
    }

    auto Shut() -> bool
    {
        for (auto const& iter : module_instances_)
        {
            AFIModule* pModule = iter.second;
            ARK_ASSERT_CONTINUE(pModule != nullptr);

            pModule->Shut();
        }

        for (auto& it : plugins_)
        {
            UnloadPluginLibrary(it.first);
        }

        for (auto& iter : plugin_libs_)
        {
            iter.second->UnLoad();
            delete iter.second;
            iter.second = nullptr;
        }

        return true;
    }

    auto LoadPluginLibrary(const std::string& plugin_name) -> bool
    {
        auto iter = plugin_libs_.find(plugin_name);
        ARK_ASSERT_RET_VAL(iter == plugin_libs_.end(), false);

        auto* pLib = new AFDynLib(plugin_name);
        ARK_ASSERT_RET_VAL(pLib != nullptr, false);

        bool load_ret = pLib->Load(plugin_library_dir_);
        if (load_ret)
        {
            plugin_libs_.insert(std::make_pair(plugin_name, pLib));
            auto func = reinterpret_cast<DLL_ENTRY_PLUGIN_FUNC>(pLib->GetSymbol("DllEntryPlugin"));
            ARK_ASSERT_RET_VAL(func != nullptr, false);
            func(this, plugin_name);

            return true;
        }
        else
        {
#ifdef ARK_PLATFORM_WIN
            auto error = GetLastError();
#else
            auto error = dlerror();
#endif
            ARK_ASSERT_RET_VAL(0, false);
        }

        return true;
    }

    auto UnloadPluginLibrary(const std::string& plugin_name) -> bool
    {
        auto iter = plugin_libs_.find(plugin_name);
        ARK_ASSERT_RET_VAL(iter != plugin_libs_.end(), false);

        AFDynLib* pDynLib = iter->second;
        ARK_ASSERT_RET_VAL(pDynLib != nullptr, false);

        auto func = reinterpret_cast<DLL_EXIT_PLUGIN_FUNC>(pDynLib->GetSymbol("DllExitPlugin"));
        ARK_ASSERT_RET_VAL(func != nullptr, false);
        func(this);

        return true;
    }

private:
    // plugin so/dll file dir
    std::string plugin_library_dir_{};

    using DLL_ENTRY_PLUGIN_FUNC = void (*)(AFPluginManager*, std::string const& /*, AFLogger */ );
    using DLL_EXIT_PLUGIN_FUNC = void (*)(AFPluginManager*);

    // plugin_code_name -> plugin_config
    std::unordered_map<std::string, std::string> plugins_;
    // plugin_code_name -> AFDynLib*
    std::unordered_map<std::string, AFDynLib*> plugin_libs_;
    // plugin_code_name -> AFIPlugin*
    std::unordered_map<std::string, AFIPlugin*> plugin_instances_;
    // module_runtime_name -> AFIModule*
    std::unordered_map<std::string, AFIModule*> module_instances_;
    // Only include the module with self Update function. module_runtime_name -> AFIModule*
    std::unordered_map<std::string, AFIModule*> module_updates_;

    // 无参命令路由表
    std::map<std::string, CommandCallBack> m_mapCommands;
    // 有参命令路由表
    std::map<std::string, MessageCallBack> m_mapFunctions;
    // 通知消息路由表
    std::unordered_map<std::string, std::list<NotifyCallBack>> m_mapNotifyFunctions;
};
