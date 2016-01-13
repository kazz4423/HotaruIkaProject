#pragma once
#include <iostream>

class Resource
{
public:
	Resource(void);
	~Resource(void);

	virtual void setResource(std::string key, std::string file) = 0 ;
	virtual void clear() = 0;

};

