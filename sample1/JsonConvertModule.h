#pragma once
#pragma once

#include "IJsonConvertModule.h"

namespace ark {

    class JsonConvertModule final : public IJsonConvertModule
    {
        ARK_DECLARE_MODULE_FUNCTIONS
    public:
        void Serialize();

        void Deserialize();
    };

}
