#pragma once
#include <string>

class CPluginManager;
class CommandManager
{
public:
	CommandManager();
	~CommandManager();

	bool SendMessage(const std::string& strCommandName_);

private:
	CPluginManager* m_pPluginManager;
};

