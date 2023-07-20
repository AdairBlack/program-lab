#include "Component.hpp"

#include "StorageFile.hpp"

#include <iostream>

namespace MaterialManagerSpace
{

    Component::Component(std::string _pn, std::string _qn, std::string _desc, uint64_t _id) : pn(_pn), qn(_qn), desc(_desc), id(_id)
    {
        std::cout << "Construct a component: pn: " << pn << ", qn: " << qn << ", desc: " << desc << std::endl;
        saveToNVStorate();
        return;
    }

    std::string Component::getStorageString()
    {
        return this->pn + " " + this->qn + " " + this->desc + " " + std::to_string(this->id);
    }

    int Component::saveToNVStorate()
    {
        NVStorage::StorageFile::saveToFile(getStorageString());
        return 0;
    }

}
