#pragma once

#include <string>

namespace MaterialManagerSpace
{

    class Component
    {
    public:
        Component(std::string _pn, std::string _qn, std::string _desc, uint64_t _id);
        std::string pn;
        std::string qn;
        std::string desc;
        uint64_t id;
        std::string getStorageString();

    private:
        int saveToNVStorate();
    };

}
