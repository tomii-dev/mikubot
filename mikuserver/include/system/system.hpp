#pragma once
 
#include "resource.hpp"

#include <vector>
#include <memory>
#include <string>
#include <variant>

#include <httpserver.hpp>

class System
{
public:
    virtual void init() = 0;

    void gatherResources(std::vector<IResource*>& resources);
    
    struct Status
    {
        enum Code { OK, NOT_OK } code;
        const std::string msg;
    };

    template <typename ReturnType>
    struct MethodReturn : public Status
    {
        ReturnType data;
    };

protected:
    void addResource(std::unique_ptr<IResource> resource);

private:
    std::vector<std::unique_ptr<IResource>> m_resources;
};
