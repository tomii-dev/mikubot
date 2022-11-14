#pragma once

#include "module.hpp"

#include <vector>
#include <memory>

class CommandRegistry;

class ModuleManager
{
public:
    ModuleManager(CommandRegistry* cmdReg);

    void setupModules();
private:
    std::vector<std::unique_ptr<Module>> m_modules;
    
    CommandRegistry* m_cmdReg;
#define DEFINE_MODULE(type) m_modules.push_back(std::make_unique<type>())
};
