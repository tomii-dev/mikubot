#pragma once

#include <string>
#include <memory>

#include <httpserver.hpp>

class IResource : public httpserver::http_resource
{
public:
    virtual const std::string endpoint() const = 0;
};

using namespace httpserver;

#define RESOURCE(ep, system, name, type) class name : public IResource { public: name (system* _system) : m_system(_system){} \
    const std::string endpoint() const override { return ep; } std::shared_ptr<http_response> render_ ##type(const http_request&) override; \
    static std::unique_ptr<IResource> make(system* _system) { return std::make_unique<name>(_system); } private: system* m_system;}; \
    std::shared_ptr<http_response> name::render_ ##type(const http_request& req)
