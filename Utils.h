#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <format>
#include "atlstr.h"

class Utils
{
private:
	std::string filepath;
	std::string filename;
public:
	Utils();
	template<typename ... Args>
	std::string string_format(const std::string& format, Args ... args);

	void createFolderA(std::string csPath);

	void writeLogString(std::string text, std::string path, std::string name);

	void logging(std::string text);
};

