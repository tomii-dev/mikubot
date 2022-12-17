#pragma once

#include "system/systemmanager.hpp"

#include <memory>
#include <vector>
#include <string>

#include <httpserver/http_utils.hpp>

class MikuServer
{
public:
    static MikuServer& make();

    int start(uint16_t port = 6667);

    static bool verifyRequest(const std::map<std::string, std::string, httpserver::http::header_comparator>& headers);

private:
    SystemManager m_sysManager;

    static std::unique_ptr<MikuServer> s_instance;
    static constexpr const char* ENDPOINT_ROOT = "/miku";

    MikuServer() {}
};
