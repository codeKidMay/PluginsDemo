/*
 * This source file is part of ARK
 * For the latest info, see https://github.com/ArkNX
 *
 * Copyright (c) 2013-2020 ArkNX authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"),
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#pragma once

#include "base/AFPlatform.hpp"

typedef std::function<void()> CommandCallBack;
typedef std::function<bool(WPARAM, LPARAM)> MessageCallBack;
typedef std::function<void(WPARAM, LPARAM)> NotifyCallBack;

#define ADD_COMMAND(name, func) AddCommand(name, std::bind(func, this));
#define ADD_COMMAND_MSG(name, func) AddCommandMsg(name, std::bind(func, this, std::placeholders::_1, std::placeholders::_2));
#define ADD_NOTIFY_MSG(name, func) AddNotifyMsg(name, std::bind(func, this, std::placeholders::_1, std::placeholders::_2));

#define ARK_EXPORT_FUNC extern "C" __declspec(dllexport)
#define ARK_EXPORT __declspec(dllexport)
#define ARK_IMPORT __declspec(dllimport)

#define DYNLIB_HANDLE hInstance
#define DYNLIB_LOAD(a) LoadLibraryEx((a), NULL, LOAD_WITH_ALTERED_SEARCH_PATH)
#define DYNLIB_GETSYM(a, b) GetProcAddress((a), (b))
#define DYNLIB_UNLOAD(a) FreeLibrary((a))

struct HINSTANCE__;
typedef struct HINSTANCE__* hInstance;

#define ARK_ASSERT_RET_VAL(exp_, val)                                                                                  \
    do                                                                                                                 \
    {                                                                                                                  \
        if ((exp_))                                                                                                    \
            break;                                                                                                     \
        assert(exp_);                                                                                                  \
        return val;                                                                                                    \
    } while (false)

#define ARK_ASSERT_CONTINUE(exp_)                                                                                      \
    if (!(exp_))                                                                                                       \
    {                                                                                                                  \
        assert(exp_);                                                                                                  \
        continue;                                                                                                      \
    }

#define ARK_ASSERT_RET_NONE(exp_)                                                                                      \
    do                                                                                                                 \
    {                                                                                                                  \
        if ((exp_))                                                                                                    \
            break;                                                                                                     \
        assert(exp_);                                                                                                  \
        return;                                                                                                        \
    } while (false)

#define ARK_ASSERT_NO_EFFECT(exp_)                                                                                     \
    do                                                                                                                 \
    {                                                                                                                  \
        if (exp_)                                                                                                      \
            break;                                                                                                     \
        assert(exp_);                                                                                                  \
    } while (false)

#define GET_CLASS_NAME(class_name) (typeid(class_name).name())
//////////////////////////////////////////////////////////////////////////
#pragma region Plugin macros
#define ARK_DECLARE_PLUGINMANAGER(PLUGIN_CLASS)                                                                               \
    class PLUGIN_CLASS final : public AFIPlugin                                                                        \
    {                                                                                                                  \
    public:                                                                                                            \
        const std::string GetPluginName() override                                                                     \
        {                                                                                                              \
            return GET_CLASS_NAME(PLUGIN_CLASS);                                                                       \
        }                                                                                                              \
        void Install() override;                                                                                       \
        void Uninstall() override;                                                                                     \
                                                                                                                       \
    private:                                                                                                           \
        std::unordered_map<std::string, AFIModule*> modules_;                                                          \
    };                                                                                                                 \
                                                                                                                       \
    ARK_EXPORT_FUNC void DllEntryPlugin(                                                                               \
        AFPluginManager* pPluginManager, std::string const& plugin_name)                                               \
    {                                                                                                                  \
        pPluginManager->Register<PLUGIN_CLASS>(plugin_name);                                                           \
    }                                                                                                                  \
    ARK_EXPORT_FUNC void DllExitPlugin(AFPluginManager* pPluginManager)                                                \
    {                                                                                                                  \
        pPluginManager->Unregister<PLUGIN_CLASS>();                                                                    \
    }

#define REGISTER_PLUGIN(MODULE, DERIVED_MODULE)                                                                    \
    do                                                                                                                 \
    {                                                                                                                  \
        ARK_ASSERT_RET_NONE((std::is_base_of<AFIModule, MODULE>::value));                                              \
        ARK_ASSERT_RET_NONE((std::is_base_of<MODULE, DERIVED_MODULE>::value));                                         \
        AFIModule* pRegModule = new DERIVED_MODULE();                                                                  \
        ARK_ASSERT_RET_NONE(pRegModule != nullptr);                                                                    \
        pRegModule->SetPluginManager(GetPluginManager());                                                              \
        pRegModule->SetName(GET_CLASS_NAME(MODULE));                                                                   \
        GetPluginManager()->AddModule(pRegModule->GetName(), pRegModule);                                              \
        modules_.insert(std::make_pair(pRegModule->GetName(), pRegModule));                                            \
        if (typeid(&AFIModule::Update) != typeid(&DERIVED_MODULE::Update))                                             \
        {                                                                                                              \
            GetPluginManager()->AddUpdateModule(pRegModule);                                                           \
        }                                                                                                              \
    } while (0)

#define UNREGISTER_PLUGIN(MODULE, DERIVED_MODULE)                                                                  \
    {                                                                                                                  \
        ARK_ASSERT_RET_NONE((std::is_base_of<AFIModule, MODULE>::value));                                              \
        ARK_ASSERT_RET_NONE((std::is_base_of<MODULE, DERIVED_MODULE>::value));                                         \
        AFIModule* pDeregModule = dynamic_cast<AFIModule*>(GetPluginManager()->template FindModule<MODULE>());         \
        ARK_ASSERT_RET_NONE(pDeregModule != nullptr);                                                                  \
        GetPluginManager()->RemoveModule(pDeregModule->GetName());                                                     \
        GetPluginManager()->RemoveUpdateModule(pDeregModule->GetName());                                               \
        modules_.erase(pDeregModule->GetName());                                                                       \
        delete pDeregModule;                                                                                           \
        pDeregModule = nullptr;                                                                                        \
    }
#pragma endregion

