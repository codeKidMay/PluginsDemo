#include "Sample1Plugin.h"
#include "Sample1Module.h"

namespace ark {

ARK_DECLARE_PLUGIN_DLL_FUNCTION(Sample1Plugin)

void Sample1Plugin::Install()
{
    ARK_REGISTER_MODULE(Sample1Module, Sample1Module);
}

void Sample1Plugin::Uninstall()
{
    ARK_UNREGISTER_MODULE(Sample1Module, Sample1Module);
}

} // namespace ark
