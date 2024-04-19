#include <iostream>
#include "CommandManager.h"
#include "../Plugin.Infrastructure/PluginManager.h"
#include "../sample1/ISample1Plugin.h"
#include "../sample1/IJsonConvertPlugin.h"
//#include "../Plugin.Infrastructure/data/TestJsonConvert.h"

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
	std::cout << "�������" << strCommandName_ << std::endl;
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