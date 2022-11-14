#include "module/modulemanager.hpp"

#include "command/commandregistry.hpp"

std::map<std::string, std::unique_ptr<Module>> ModuleManager::s_modules;

ModuleManager::ModuleManager(CommandRegistry* cmdReg)
    : m_cmdReg(cmdReg)
{}

void ModuleManager::setupModules()
{
    for(auto& [name, module] : s_modules)
    {
        module->init();
        for(const std::unique_ptr<Command>& cmd : module->m_commands)
            m_cmdReg->addCommand(cmd.get());
    }
}
