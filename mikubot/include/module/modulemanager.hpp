#pragma once

#include "module.hpp"

#include <map>
#include <memory>
#include <assert.h>
#include <type_traits>

class CommandRegistry;

class ModuleManager
{
public:
    ModuleManager(CommandRegistry* cmdReg);

    void setupModules();
    
    inline static const std::string moduleDesc(const std::string& module) { return s_modules.at(module)->desc(); }
    
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
