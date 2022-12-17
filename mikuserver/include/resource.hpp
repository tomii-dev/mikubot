#pragma once

#include "response.hpp"

#include <string>
#include <memory>

#include <httpserver.hpp>

class IResource : public httpserver::http_resource
{
public:
    virtual const std::string endpoint() const = 0;
};

#define RESOURCE(ep, system, name, type) class name##Resource : public IResource { public: name##Resource (system* _system) : m_system(_system){} \
    const std::string endpoint() const override { return ep; } std::shared_ptr<httpserver::http_response> render_ ##type(const httpserver::http_request&) override; \
    static std::unique_ptr<IResource> make(system* _system) { return std::make_unique<name##Resource>(_system); } private: system* m_system;}; \
    std::shared_ptr<httpserver::http_response> name##Resource::render_ ##type(const httpserver::http_request& req)

#define FIELD(field) if(!req.get_headers().count(#field)) return Response::badReq("missing '" #field "' field"); \
    const std::string& field = req.get_header(#field);

