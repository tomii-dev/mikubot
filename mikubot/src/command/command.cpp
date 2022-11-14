#include "command/command.hpp"

#include "mikubot.hpp"

Command::Command(const std::string& name, const std::string& desc)
    : m_name(name)
    , m_cmd(name, desc, MikuBot::cluster().me.id)
{}
