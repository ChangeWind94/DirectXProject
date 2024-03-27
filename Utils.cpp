#include "Utils.h"

Utils::Utils() {
    this->filepath = "C:\\test\\";
    this->filename = "test";
};

void Utils::createFolderA(std::string csPath)
{
    std::string csPrefix(""), csToken("");
    int nStart = 0, nEnd;

    while ((nEnd = csPath.find('\\', nStart)) >= 0)
    {
        std::string csToken = csPath.substr(nStart, nEnd - nStart);

        CreateDirectoryA(std::string(csPrefix + csToken).c_str(), NULL);

        csPrefix += csToken;
        csPrefix += "\\";
        nStart = nEnd + 1;
    }
    csToken = csPath.substr(nStart);
    CreateDirectoryA(std::string(csPrefix + csToken).c_str(), NULL);
}

template<typename ... Args>
std::string Utils::string_format(const std::string& format, Args ... args)
{
    size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0' 
    if (size <= 0) {
        throw std::runtime_error("Error during formatting.");
    }
    std::unique_ptr<char[]> buf(new char[size]);
    snprintf(buf.get(), size, format.c_str(), args ...);
    return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside }
}

void Utils::writeLogString(std::string text, std::string path, std::string name)
{
    
    createFolderA(path);
    SYSTEMTIME SystemTime;
    GetLocalTime(&SystemTime);

    std::string LogFullPath;

    if (path == "")
    {
        LogFullPath = string_format("%s %04d-%02d-%02d.log", name.c_str(), SystemTime.wYear, SystemTime.wMonth, SystemTime.wDay);
    }
    else
    {
        LogFullPath = string_format("%s\\%s %04d-%02d-%02d.log", path.c_str(), name.c_str(), SystemTime.wYear, SystemTime.wMonth, SystemTime.wDay);
    }

    

    std::ofstream file(LogFullPath, std::ios::out | std::ios::app);

    if (file.is_open()) {
        file << text << "\n";
        file.close();
    }
}

void Utils::logging(std::string text) {
    writeLogString(text, filepath, filename);
}