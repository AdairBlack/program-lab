#include "StorageFile.hpp"

#include <string>
#include <iostream>
#include <fstream>

#define FILE_PATH "components"

namespace NVStorage
{
    int StorageFile::saveToFile(std::string content)
    {
        std::cout << "Write content: \"" << content << "\" to file: \"" << FILE_PATH << "\"" << std::endl;
        std::ofstream fout;
        fout.open(FILE_PATH, std::ios::app);
        std::cout << "test0 " << fout.is_open() << std::endl;
        fout << content << std::endl;

        fout.close();

        return 0;
    }
}
