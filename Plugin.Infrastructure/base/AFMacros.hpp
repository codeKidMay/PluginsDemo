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

/*
 * Copy src to string dst of size siz.  At most siz-1 characters
 * will be copied.  Always NUL terminates (unless siz == 0).
 * Returns strlen(src); if retval >= siz, truncation occurred.
 */
inline size_t strlcpy(char* dst, const char* src, size_t siz)
{
    char* d = dst;
    const char* s = src;
    size_t n = siz;

    /* Copy as many bytes as will fit */
    if ((n != 0) && ((--n) != 0))
    {
        do
        {
            if ((*d++ = *s++) == 0)
                break;
        } while (--n != 0);
    }

    /* Not enough room in dst, add NUL and traverse rest of src */
    if (n == 0)
    {
        if (siz != 0)
            *d = '\0'; /* NUL-terminate dst */

        while (*s++)
            ;
    }

    return (s - src - 1); /* count does not include NUL */
}

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

#define ARK_ASSERT_RET_VAL_NO_EFFECT(exp_, val)                                                                        \
    do                                                                                                                 \
    {                                                                                                                  \
        if ((exp_))                                                                                                    \
            break;                                                                                                     \
        return val;                                                                                                    \
    } while (false)

#define ARK_ASSERT_BREAK(exp_)                                                                                         \
    if (!(exp_))                                                                                                       \
    {                                                                                                                  \
        assert(exp_);                                                                                                  \
        break;                                                                                                         \
    }

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
        int GetPluginVersion() override                                                                                \
        {                                                                                                              \
            return 0;                                                                                                  \
        }                                                                                                              \
        const std::string GetPluginName() override                                                                     \
        {                                                                                                              \
            return GET_CLASS_NAME(PLUGIN_CLASS);                                                                       \
        }                                                                                                              \
        void Install() override;                                                                                       \
        void Uninstall() override;                                                                                     \
                                                                                                                       \
    private:                                                                                                           \
        std::unordered_map<std::string, AFIModule*> modules_;                                                          \
    };

#define ARK_DECLARE_PLUGIN_DLL_FUNCTION(PLUGIN_CLASS)                                                                  \
    ARK_EXPORT_FUNC void DllEntryPlugin(                                                                               \
        AFPluginManager* pPluginManager, std::string const& plugin_name/*, AFLogger* logger*/)                         \
    {                                                                                                                  \
        /*AFLogger::Init(logger);*/                                                                                    \
        pPluginManager->Register<PLUGIN_CLASS>(plugin_name);                                                           \
    }                                                                                                                  \
    ARK_EXPORT_FUNC void DllExitPlugin(AFPluginManager* pPluginManager)                                                \
    {                                                                                                                  \
        pPluginManager->Unregister<PLUGIN_CLASS>();                                                                    \
    }

#define ARK_REGISTER_MODULE(MODULE, DERIVED_MODULE)                                                                    \
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

#define ARK_UNREGISTER_MODULE(MODULE, DERIVED_MODULE)                                                                  \
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

//////////////////////////////////////////////////////////////////////////
// Module macros
#define ARK_DECLARE_MODULE_FUNCTIONS                                                                                   \
public:                                                                                                                \
    AFPluginManager* GetPluginManager() const override                                                                 \
    {                                                                                                                  \
        return plugin_manager_;                                                                                        \
    }                                                                                                                  \
    void SetPluginManager(AFPluginManager* p) override                                                                 \
    {                                                                                                                  \
        ARK_ASSERT_RET_NONE(p != nullptr);                                                                             \
        plugin_manager_ = p;                                                                                           \
    }                                                                                                                  \
    const std::string& GetName() const override                                                                        \
    {                                                                                                                  \
        return name_;                                                                                                  \
    }                                                                                                                  \
    void SetName(const std::string& value) override                                                                    \
    {                                                                                                                  \
        name_ = value;                                                                                                 \
    }                                                                                                                  \
                                                                                                                       \
protected:                                                                                                             \
    template<typename MODULE>                                                                                          \
    MODULE* FindModule()                                                                                               \
    {                                                                                                                  \
        return GetPluginManager()->template FindModule<MODULE>();                                                      \
    }                                                                                                                  \
                                                                                                                       \
private:                                                                                                               \
    AFPluginManager* plugin_manager_{nullptr};                                                                         \
    std::string name_{};
////////////////////////////////////////////////////////////////////////////
#pragma endregion

