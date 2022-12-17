#include "mikubot.hpp"

#include "secrets.hpp"

#include <sstream>
#include <fstream>
#include <assert.h>

#include <dpp/dpp.h>
#include <curlpp/cURLpp.hpp>

std::unique_ptr<MikuBot> MikuBot::s_instance;

/* static */ MikuBot& MikuBot::make()
{
    assert(!s_instance);
    s_instance = std::unique_ptr<MikuBot>(new MikuBot());

    return *s_instance.get();
}

MikuBot::MikuBot() : m_moduleMgr(&m_cmdReg)
{
    cURLpp::initialize();

    m_cluster = std::make_unique<dpp::cluster>(BOT_TOKEN);

    m_cluster->on_log(dpp::utility::cout_logger());

    m_cluster->on_slashcommand([this](const dpp::slashcommand_t& e){ m_cmdReg.handleCommand(e); });
    m_cluster->on_ready([this](const dpp::ready_t&){ m_moduleMgr.setupModules(); });
}

int MikuBot::start()
{
    m_cluster->start(dpp::st_wait);

    return 0;
}
