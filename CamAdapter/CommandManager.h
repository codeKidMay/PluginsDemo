#pragma once
#include <string>
#include <map>

class CPluginManager;
class CommandManager
{
public:
	CommandManager();
	~CommandManager();

	bool SendMessage(const std::string& strCommandName_);

private:
	void Plugin1();
	void Plugin2();
	void Plugin3();

private:
	//CPluginManager* m_pPluginManager;
};

