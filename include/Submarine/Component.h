#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include <string>

#include <nlohmann/json.hpp>

class Component
{
public:
	virtual void HandleCommand(const nlohmann::json &json) = 0;
	
	virtual nlohmann::json ToJson() const = 0;
};

#endif
