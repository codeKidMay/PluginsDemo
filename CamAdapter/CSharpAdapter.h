#pragma once

using namespace System;

namespace CSharpAdapter
{
    public ref class NcAdapter
    {
    public:
        NcAdapter();

        // 公共方法
        bool SendMessage(String^ commandName);
    };
}