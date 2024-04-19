#pragma once
#include "base/AFPluginManager.hpp"
#include "interface/AFIPlugin.hpp"
#include "interface/AFIModule.hpp"

class IJsonConvertModule : public AFIModule
{
public:
	virtual void Serialize() = 0;

	virtual void Deserialize() = 0;
};
