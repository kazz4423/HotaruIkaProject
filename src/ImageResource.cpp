#include "ImageResource.h"


ImageResource::ImageResource(void)
{

}


ImageResource::~ImageResource(void)
{
	clear();
}

void ImageResource::setResource(std::string key, std::string file_name)
{
	ofImage image;
	image.loadImage(file_name);
	imageList[key] = image;
}

void ImageResource::clear(){
	imageList.clear();
}

ofImage* ImageResource::getResourcePtr(std::string key)
{
	return &imageList[key];
}