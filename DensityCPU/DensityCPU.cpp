
#include "main3ddata.h"
#include <iostream>


float toFloat(char* s)
{
	return atof(s);
}

int main(int argc, char** argv)
{

	std::cout << "cudaDensity [原始文件] [半径] [间隔] [x拉伸] [y拉伸] [z拉伸]" << std::endl;
	if (argc < 2)
	{
		std::cout << "Filename:?" << std::endl;
		return -1;
	}
	float radius, granularity, xstretch, ystretch, zstretch;
	if (argc <= 2)
	{
		radius = 50.0;
	}
	else
	{
		radius = toFloat(argv[2]);
	}

	if (argc <= 3)
	{
		granularity = 10.0;
	}
	else
	{
		granularity = toFloat(argv[3]);
	}


	if (argc <= 4)
	{
		xstretch = 1.0;
	}
	else
	{
		xstretch = toFloat(argv[4]);
	}

	if (argc <= 5)
	{
		ystretch = 1.0;
	}
	else
	{
		ystretch = toFloat(argv[5]);
	}

	if (argc <= 6)
	{
		zstretch = 1.0;
	}
	else
	{
		zstretch = toFloat(argv[6]);
	}

	std::cout << argv[1] << " " << radius << " " << granularity << " " << xstretch << " " << ystretch << " " << zstretch << std::endl;
	main3DData(std::string(argv[1]), radius, granularity, xstretch, ystretch, zstretch);

	return 0;
}
