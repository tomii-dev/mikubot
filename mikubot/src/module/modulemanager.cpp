#include "module/modulemanager.hpp"

#include "command/commandregistry.hpp"

ModuleManager::ModuleManager(CommandRegistry* cmdReg)
    : m_cmdReg(cmdReg)
{}

void ModuleManager::setupModules()
{
    for(const std::unique_ptr<Module>& module : m_modules)
    {
        module->init();
        for(const std::unique_ptr<Command>& cmd : module->m_commands)
            m_cmdReg->addCommand(cmd.get());
    }
}