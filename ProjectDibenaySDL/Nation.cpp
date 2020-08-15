#include "Nation.h"
namespace Mer
{
	Nation::Nation()
	{

	}
	Nation::Nation(std::string name, std::string capitalProvince, int red, int green, int blue)
	{
		this->name = name; 
		this->capitalProvince = capitalProvince;
		this->red = red;
		this->green = green; 
		this->blue = blue;
	}

	int Nation::getRed()
	{
		return red;
	}
	int Nation::getGreen()
	{
		return green;
	}
	int Nation::getBlue()
	{
		return blue;
	}
	std::string Nation::getName()
	{
		return name;
	}
}