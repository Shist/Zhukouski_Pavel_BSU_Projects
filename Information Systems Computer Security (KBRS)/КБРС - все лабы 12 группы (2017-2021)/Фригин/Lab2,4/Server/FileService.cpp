#include "FileService.hpp"

std::ifstream FileService::Resolve (const std::string &fileName)
{
    if (fileName.find ("..") != std::string::npos)
    {
        return {};
    }

    return std::ifstream {"./files/" + fileName, std::ifstream::binary};
}
