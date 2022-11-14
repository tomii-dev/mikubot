#pragma once

#include "module/modulemanager.hpp"
#include "command/commandregistry.hpp"

#include <memory>

#include <dpp/cluster.h>

class MikuBot
{
public:
    static MikuBot& make();
    
    static inline dpp::cluster& cluster() { return *s_instance->m_cluster.get(); }
private:
    MikuBot();
        
    CommandRegistry m_cmdReg;
    ModuleManager m_moduleMgr;

    std::unique_ptr<dpp::cluster> m_cluster;

    static std::unique_ptr<MikuBot> s_instance;
};
