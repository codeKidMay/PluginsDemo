#pragma once
#include "CommandManager.h"

using namespace System;

namespace CSharpAdapter
{
    public ref class NcAdapter
    {
    public:
        NcAdapter();

        // ��������
        bool SendMessage(String^ commandName);

    private:
        CommandManager* m_pCommandManager;
    };
}