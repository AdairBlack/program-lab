#include "Machine.hpp"

#include <iostream>
#include <algorithm>

namespace MaterialManagerSpace
{

    Machine::Machine(int _id, std::string _description) : id(_id), description(_description)
    {
        std::cout << "construct a Machine, id: " << id << ",description: " << description << std::endl;
        return;
    }

    void Machine::addComponent(uint64_t id)
    {
        if (components.end() == std::find_if(components.begin(), components.end(),
                                             [id](auto compId)
                                             { return compId == id; }))
        {
            components.push_back(id);
        }

        return;
    }

    void Machine::removeComponent(uint64_t id)
    {
        for (auto iterComp = components.cbegin(); iterComp != components.cend(); iterComp++)
        {
            if (*iterComp == id)
            {
                components.erase(iterComp);
                break;
            }
        }

        return;
    }

}
