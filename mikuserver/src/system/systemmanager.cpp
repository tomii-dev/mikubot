#include "system/systemmanager.hpp"

#include <iostream>

std::vector<std::unique_ptr<System>> SystemManager::s_systems;

void SystemManager::setupSystems(std::vector<IResource*>& resources)
{
    for(const std::unique_ptr<System>& sys : s_systems)
    {
        sys->init();
        sys->gatherResources(resources);
    }
}
