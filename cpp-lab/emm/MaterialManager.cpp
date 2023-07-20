#include "MaterialManager.hpp"

#include <iostream>

namespace MaterialManagerSpace
{
    MaterialManager &MaterialManager::getInstance()
    {
        static MaterialManager instance;
        return instance;
    }

    void MaterialManager::addComponent(std::string pn, std::string qn, std::string desc)
    {
        components.push_back(Component{pn, qn, desc, id});
        id++;
        return;
    }

    void MaterialManager::removeComponent(uint64_t id)
    {
        for (auto iterComp = components.cbegin(); iterComp != components.cend(); iterComp++)
        {
            if (iterComp->id == id)
            {
                components.erase(iterComp);
                break;
            }
        }
        return;
    }

    std::string MaterialManager::getComponentInfo(uint64_t id)
    {
        for (auto i : components)
        {
            if (id == i.id)
            {
                // TODO 20230212
                return i.getStorageString();
            }
        }
        return "Error!!!";
    }

    std::vector<uint64_t> MaterialManager::getComponentsIdList()
    {
        std::vector<uint64_t> idList;
        for (auto &i : components)
        {
            // TODO
            idList.push_back(i.id);
        }
        return idList;
    }

}