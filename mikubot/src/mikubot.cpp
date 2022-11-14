#include "mikubot.hpp"

#include <sstream>
#include <fstream>
#include <assert.h>

#include <dpp/dpp.h>

std::unique_ptr<MikuBot> MikuBot::s_instance;

/* static */ MikuBot& MikuBot::make()
{
    assert(!s_instance);
    s_instance = std::unique_ptr<MikuBot>(new MikuBot());

    return *s_instance.get();
}

MikuBot::MikuBot() : m_moduleMgr(&m_cmdReg)
{
    std::stringstream ss;
    std::ifstream ifs("token");
    ss << ifs.rdbuf();

    m_cluster = std::make_unique<dpp::cluster>("OTUwNzQ1MzM1MDA3OTQ0Nzg4.G3C6ZU.Q7rSdvxQA0D4crezfTLii6XqUJKEk4eWCFn9EY");

    m_cluster->on_slashcommand([this](const dpp::slashcommand_t& e){ m_cmdReg.handleCommand(e); });
    m_cluster->on_ready([this](const dpp::ready_t&){ m_moduleMgr.setupModules(); });

    m_cluster->start(dpp::st_wait);
}
