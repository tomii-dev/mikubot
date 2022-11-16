#pragma once

#include "module.hpp"

#include <map>
#include <vector>
#include <memory>
#include <assert.h>
#include <type_traits>

class CommandRegistry;

class ModuleManager
{
public:
    ModuleManager(CommandRegistry* cmdReg);

    void setupModules();
    
    static const std::vector<std::string> modules();
    static const Module* getModule(const std::string& name);

    template <typename ModuleType>
    struct ModuleCreator
    {
        inline ModuleCreator(const std::string& name)
        {
            static_assert(std::is_base_of<Module, ModuleType>::value, "provided type is not a module!");

            ModuleManager::s_modules.emplace(name, std::make_unique<ModuleType>());
        }
    };

#define DEFINE_MODULE(module) ModuleManager::ModuleCreator<module> g_creator ##module (#module);

private:
    CommandRegistry* m_cmdReg;

    static std::map<std::string, std::unique_ptr<Module>> s_modules;
};
