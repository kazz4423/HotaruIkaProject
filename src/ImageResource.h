#pragma once
#include "resource.h"
#include "ofMain.h"
class ImageResource :
	public Resource
{
private:
	std::map<std::string,ofImage> imageList; //�摜���X�g

public:
	ImageResource(void);
	~ImageResource(void);

	void setResource(std::string key, std::string file_name);
	void clear();

	ofImage* getResourcePtr(std::string key);

};

