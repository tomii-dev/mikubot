#pragma once

#include "system.hpp"

#include <vector>
#include <memory>
#include <type_traits>

#include <httpserver.hpp>

class IResource;


class SystemManager
{
public:
    void setupSystems(std::vector<IResource*>& resources);

    template <typename SystemType>
    struct SystemCreator
    {
        inline SystemCreator()
        {
            static_assert(std::is_base_of<System, SystemType>::value, "provided type is not a system!");

            SystemManager::s_systems.push_back(std::make_unique<SystemType>());
        }
    };

private:
    static std::vector<std::unique_ptr<System>> s_systems;
};

#define DEFINE_SYSTEM(system) SystemManager::SystemCreator<system> g_creator ##system;
