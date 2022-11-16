#include "command/command.hpp"

#include "mikubot.hpp"

Command::Command(const std::string& name, const std::string& desc)
    : m_name(name)
    , m_desc(desc)
    , m_cmd(name, desc, MikuBot::cluster().me.id)
{}

Option& Command::addOption(const std::string& name, const std::string& desc, Option::Type type)
{
    m_options.push_back(Option(name, desc, type));

    return m_options.back();
}

const dpp::slashcommand& Command::get()
{
    for(const Option& opt : m_options)
        m_cmd.add_option(opt.get());

    return m_cmd;
}
