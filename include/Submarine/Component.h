#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include <string>

#include <nlohmann/json.hpp>

class Submarine;

class Component
{
	friend class Submarine;
	
protected:
	Submarine *submarine;
	
public:
	virtual std::string GetName() const = 0;
	
	virtual void HandleCommand(const nlohmann::json &json) = 0;
	
	virtual nlohmann::json ToJson() const = 0;
};

#endif
