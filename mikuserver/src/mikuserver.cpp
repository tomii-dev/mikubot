#include "mikuserver.hpp"

#include "resource.hpp"
#include "secrets.hpp"

#include <assert.h>

std::unique_ptr<MikuServer> MikuServer::s_instance;

/* static */ MikuServer& MikuServer::make()
{
    assert(!s_instance);

    s_instance = std::unique_ptr<MikuServer>(new MikuServer());
    return *s_instance.get();
}

int MikuServer::start(uint16_t port)
{
    httpserver::webserver ws = httpserver::create_webserver(port);

    std::vector<IResource*> resources;
    m_sysManager.setupSystems(resources);
    for(IResource* res : resources)
        ws.register_resource(ENDPOINT_ROOT + res->endpoint(), res);

    ws.start(true);

    return 0;
}

/* static */ bool MikuServer::verifyRequest(const std::map<std::string, std::string, httpserver::http::header_comparator>& headers)
{
    if(!headers.count("authorization"))
        return false;

    if(headers.at("authorization") != BOT_TOKEN)
        return false;

    return true;
}
