#include "Sample2Plugin.h"
#include "ISample2Module.h"
#include "Sample2Module.h"

namespace ark {

ARK_DECLARE_PLUGIN_DLL_FUNCTION(Sample2Plugin)

void Sample2Plugin::Install()
{
    ARK_REGISTER_MODULE(ISample2Module, Sample2Module);
}

void Sample2Plugin::Uninstall()
{
    ARK_UNREGISTER_MODULE(ISample2Module, Sample2Module);
}

}
