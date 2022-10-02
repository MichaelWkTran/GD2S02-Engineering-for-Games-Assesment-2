#pragma once
#include <iostream>
class Level
{
private:
	std::string path;
public:
	Level(std::string _path);
	std::string GetPath() { return path; };
};

