#pragma once
#pragma once

#include "IJsonConvertPlugin.h"

class JsonConvertModule final : public IJsonConvertModule
{
public:
    void Serialize();

    void Deserialize();
};
