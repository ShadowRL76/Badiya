#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <vector>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class objLoader
{
public:
	std::vector<std::string> split(std::string line, std::string delimiter);
};

#endif 