#pragma once
#include "resource.h"
#include "ofApp.h"
class ShaderResource :
	public Resource
{
private:
	std::map<std::string, ofShader> shaderList;
public:
	ShaderResource(void);
	~ShaderResource(void);

	void setResource(std::string key, std::string file_name);
	void clear();

	ofShader* getResourcePtr(std::string key);

};

