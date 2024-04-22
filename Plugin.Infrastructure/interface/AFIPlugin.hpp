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

class AFPluginManager;

class AFIPlugin
{
public:
    virtual ~AFIPlugin() = default;
    virtual const std::string GetPluginName() = 0;

    virtual void Install() = 0;
    virtual void Uninstall() = 0;

    AFPluginManager* GetPluginManager() const { return plugin_manager_; }
    void SetPluginManager(AFPluginManager* p) { plugin_manager_ = p; }

    std::string const& GetPluginConf() const { return plugin_conf_; }
    void SetPluginConf(std::string const& value) { plugin_conf_ = value; }

protected:
    AFPluginManager* plugin_manager_{ nullptr };
    std::string plugin_conf_;
};
