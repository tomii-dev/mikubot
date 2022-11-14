#pragma once

#include "module.hpp"

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
    
    template <typename ModuleType>
    struct ModuleCreator
    {
        inline ModuleCreator()
        {
            static_assert(std::is_base_of<Module, ModuleType>::value, "provided type is not a module!");

            ModuleManager::s_modules.push_back(std::make_unique<ModuleType>());
        }
    };

#define DEFINE_MODULE(module) ModuleManager::ModuleCreator<module> g_creator ##module;
private:
    CommandRegistry* m_cmdReg;

    static std::vector<std::unique_ptr<Module>> s_modules;
};
