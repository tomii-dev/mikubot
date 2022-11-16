#include "system/system.hpp"

#include <iostream>

void System::gatherResources(std::vector<IResource*>& resources)
{
    for(const std::unique_ptr<IResource>& res : m_resources)
        resources.push_back(res.get());
}

void System::addResource(std::unique_ptr<IResource> resource)
{
    m_resources.push_back(std::move(resource));
}
