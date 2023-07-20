#pragma once

#include <vector>
#include <iostream>

namespace ControlPanelSpace
{
    class ControlPanel
    {
    public:
        static ControlPanel &getInstance();

        void showMainMenu();
        void showAllTheComponents(std::vector<std::string> &contents);

    private:
        ControlPanel() { std::cout << "Construct a ControlPanel singleton." << std::endl; };
        ~ControlPanel(){};
        ControlPanel(const ControlPanel &);
        ControlPanel &operator=(const ControlPanel &);
    };
}