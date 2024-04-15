#include <iostream>
#include "CommandManager.h"
#include "../Plugin.Infrastructure/PluginManager.h"
#include "../sample1/ISample1Module.h"
#include "../sample1/IJsonConvertModule.h"
#include "../Plugin.Infrastructure/data/TestJsonConvert.h"

using namespace ark;

CommandManager::CommandManager()
{
	m_pPluginManager = new CPluginManager();
	m_pPluginManager->Initialize();
	m_mapCommands["plugin1"] = std::bind(&CommandManager::Plugin1, this);
	m_mapCommands["plugin2"] = std::bind(&CommandManager::Plugin2, this);
	m_mapCommands["plugin3"] = std::bind(&CommandManager::Plugin3, this);
}

CommandManager::~CommandManager()
{
	delete m_pPluginManager;
	m_pPluginManager = nullptr;
}

bool CommandManager::SendMessage(const std::string& strCommandName_)
{
	Foo foo;
	std::string json_str;
	::json_helper::Marshal(foo, &json_str, true);
	std::cout << "============ with style ============" << std::endl;
	std::cout << json_str << std::endl;

	std::cout << "=========== without style ==========" << std::endl;
	::json_helper::Marshal(foo, &json_str);
	std::cout << json_str << std::endl;

	std::cout << "µ÷ÓÃÃüÁî£º" << strCommandName_ << std::endl;
	auto _commandIter = m_mapCommands.find(strCommandName_);
	if (_commandIter != m_mapCommands.end())
	{
		_commandIter->second();
	}

	return true;
}

void CommandManager::Plugin1()
{
	auto _pModule = m_pPluginManager->GetModule<ISample1Module>();
	ISample1Module* _pSample1Module = dynamic_cast<ISample1Module*>(_pModule);
	_pSample1Module->PartRecognition("file_path");
}

void CommandManager::Plugin2()
{
	auto _pModule = m_pPluginManager->GetModule<IJsonConvertModule>();
	IJsonConvertModule* _pJsonModule = dynamic_cast<IJsonConvertModule*>(_pModule);
	_pJsonModule->Serialize();
}

void CommandManager::Plugin3()
{
	auto _pModule = m_pPluginManager->GetModule<IJsonConvertModule>();
	IJsonConvertModule* _pJsonModule = dynamic_cast<IJsonConvertModule*>(_pModule);
	_pJsonModule->Deserialize();
}