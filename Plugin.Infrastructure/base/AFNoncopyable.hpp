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

namespace ark {

class AFNoncopyable
{
protected:
    AFNoncopyable() = default;
    ~AFNoncopyable() = default;

public:
    AFNoncopyable(const AFNoncopyable&) = delete;
    AFNoncopyable& operator=(const AFNoncopyable&) = delete;
    AFNoncopyable(AFNoncopyable&&) = delete;
    AFNoncopyable& operator=(AFNoncopyable&&) = delete;
};

} // namespace ark