#pragma once

using namespace System;

namespace CSharpAdapter
{
    public ref class NcAdapter
    {
    public:
        NcAdapter();

        // ��������
        bool SendMessage(String^ commandName);
    };
}