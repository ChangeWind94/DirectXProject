#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <format>
#include "atlstr.h"

class Utils
{
	template<typename ... Args>
	std::string string_format(const std::string& format, Args ... args);

	void createFolderA(std::string csPath);

	void WriteLogString(std::string text, std::string path, std::string name);
};

