#include "MaterialManager.hpp"
#include "Component.hpp"
#include "ControlPanel.hpp"

#include <iostream>
#include <vector>

#define PROJECT_NAME "emm"

int main(int argc, char **argv)
{
    printf("This is project %s.\n", PROJECT_NAME);
    if (0)
    {
        argc = argc;
        argv = argv;
    }

    auto &materialManager = MaterialManagerSpace::MaterialManager::getInstance();

    for (int i = 0; i < 14; i++)
    {
        materialManager.addComponent("CompPN" + std::to_string(i), "QNsdfjksf123_" + std::to_string(i), "A simple component number" + std::to_string(i) + ".");
    }

    auto &controlPanel = ControlPanelSpace::ControlPanel::getInstance();

    auto idList = materialManager.getComponentsIdList();

    for (auto &i : idList)
    {
        std::cout << "id: " << i << std::endl;
    }

    controlPanel.showMainMenu();
    std::vector<std::string> contents;
    for (auto &i : idList)
    {
        contents.push_back(materialManager.getComponentInfo(i));
    }
    controlPanel.showAllTheComponents(contents);

    std::cout << "Thanks for using." << std::endl;

    return 0;
}
