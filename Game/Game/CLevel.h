#pragma once
#include <iostream>
class CLevel
{
private:
	std::string path;
public:
	CLevel(std::string _path);
	std::string GetPath() { return path; };
};

