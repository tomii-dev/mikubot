#include "mikuserver.hpp"

#include "resource.hpp"

#include <assert.h>

#include <httpserver.hpp>

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
