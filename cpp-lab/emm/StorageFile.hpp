#pragma once

#include <string>

namespace NVStorage
{
    class StorageFile
    {
    public:
        static int saveToFile(std::string content);
    };
}
