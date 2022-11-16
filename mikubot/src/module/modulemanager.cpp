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

    for(auto& [name, module] : s_modules)
        module->postInit();
}

/* static */ const std::vector<std::string> ModuleManager::modules()
{
    std::vector<std::string> modules;

    for(const auto& kv : s_modules)
        modules.push_back(kv.first);

    return modules;
}

/* static */ const Module* ModuleManager::getModule(const std::string& name)
{
    if(!s_modules.count(name))
        return nullptr;

    return s_modules[name].get();
}
