#include <iostream>
#include "CommandManager.h"
#include "../Plugin.Infrastructure/PluginManager.h"
#include "../sample1/ISample1Module.h"

using namespace ark;

CommandManager::CommandManager()
{
	m_pPluginManager = new CPluginManager();
	m_pPluginManager->Initialize();
}

CommandManager::~CommandManager()
{
	delete m_pPluginManager;
	m_pPluginManager = nullptr;
}

bool CommandManager::SendMessage(const std::string& strCommandName_)
{
	std::cout << "µ÷ÓÃÃüÁî£º" << strCommandName_ << std::endl;
	auto _pModule = m_pPluginManager->GetModule<ISample1Module>();
	ISample1Module* _pSample1Module = dynamic_cast<ISample1Module*>(_pModule);
	_pSample1Module->PartRecognition("file_path");

	return true;
}
