#pragma once

#include "system/systemmanager.hpp"

#include <memory>
#include <vector>

class MikuServer
{
public:
    static MikuServer& make();

    int start(uint16_t port = 6667);
private:
    SystemManager m_sysManager;

    static std::unique_ptr<MikuServer> s_instance;
    static constexpr const char* ENDPOINT_ROOT = "/miku/";

    MikuServer() {}
};
