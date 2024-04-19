#pragma once
#pragma once

#include "IJsonConvertPlugin.h"

class JsonConvertModule final : public IJsonConvertModule
{
    ARK_DECLARE_MODULE_FUNCTIONS
public:
    void Serialize();

    void Deserialize();
};
