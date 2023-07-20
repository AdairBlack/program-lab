#include "ControlPanel.hpp"

namespace ControlPanelSpace
{
    ControlPanel &ControlPanel::getInstance()
    {
        static ControlPanel instance;
        return instance;
    }

    void ControlPanel::showMainMenu()
    {
        std::cout << "*********************************************" << std::endl;
        std::cout << "****      Edgar  Material Management     ****" << std::endl;
        std::cout << "*********************************************" << std::endl;
        std::cout << "****       1. show all the components    ****" << std::endl;
        std::cout << "****       2. add a component            ****" << std::endl;
        std::cout << "****       3. remove a component         ****" << std::endl;
        std::cout << "*********************************************" << std::endl;

        int input = 0;
        std::cin >> input;
        std::cout << "Input(number): " << input << std::endl;

        switch (input)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            break;
        }
    }

    void ControlPanel::showAllTheComponents(std::vector<std::string> &contents)
    {
        std::cout << "*********************************************" << std::endl;
        std::cout << "****        Show All the Components      ****" << std::endl;
        std::cout << "*********************************************" << std::endl;
        for (auto &i : contents)
        {
            std::cout << i << std::endl;
        }
        return;
    }
} // namespace ControlPanelSpace