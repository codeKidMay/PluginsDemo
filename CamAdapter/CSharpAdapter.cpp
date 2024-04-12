#include <msclr/marshal.h>
#include "CSharpAdapter.h"

using namespace System::Runtime::InteropServices;
namespace CSharpAdapter
{
	NcAdapter::NcAdapter()
	{
		m_pCommandManager = new CommandManager();
	}

	bool NcAdapter::SendMessage(String^ commandName)
	{
		IntPtr ptr = Marshal::StringToHGlobalAnsi(commandName);
		std::string strCommandName = reinterpret_cast<char*>(ptr.ToPointer());
		Marshal::FreeHGlobal(ptr);
		m_pCommandManager->SendMessage(strCommandName);

		return true;
	}
}

