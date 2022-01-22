#pragma once
#include <fstream>

class FileService final
{
public:
    static std::ifstream Resolve (const std::string &fileName);
};
