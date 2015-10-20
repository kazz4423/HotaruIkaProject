#include "ShaderResource.h"


ShaderResource::ShaderResource(void)
{
}


ShaderResource::~ShaderResource(void)
{
	clear();
}

void ShaderResource::setResource(std::string key, std::string file_name)
{
	ofShader shader;
	shader.load(file_name);
	shaderList [key] = shader;
}

void ShaderResource::clear()
{
	shaderList.clear();
}

ofShader* ShaderResource::getResourcePtr(std::string key)
{
	return &shaderList[key];
}
