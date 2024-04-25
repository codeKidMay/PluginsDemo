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
#include "base/AFMacros.hpp"

class AFPluginManager;

class AFIModule
{
public:
    AFIModule() = default;
    virtual ~AFIModule() = default;

    AFPluginManager* GetPluginManager() const { return m_pPluginManager; }
    void SetPluginManager(AFPluginManager* p) { m_pPluginManager = p; }

    const std::string& GetName() const { return m_strName; }
    void SetName(const std::string& value) { m_strName = value; }

public:
    virtual bool Init()
    {
        return true;
    }

    virtual bool PostInit()
    {
        return true;
    }

    virtual bool CheckConfig()
    {
        return true;
    }

    virtual bool PreUpdate()
    {
        return true;
    }

    virtual bool Update()
    {
        return true;
    }

    virtual bool PreShut()
    {
        return true;
    }

    virtual bool Shut()
    {
        return true;
    }

protected:
    template<typename MODULE>
    MODULE* FindModule()
    {
        return GetPluginManager()->template FindModule<MODULE>();
    }

    AFPluginManager* m_pPluginManager{ nullptr };
    std::string m_strName;
};

