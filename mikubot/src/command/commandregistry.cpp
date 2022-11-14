#include "command/commandregistry.hpp"

void CommandRegistry::handleCommand(const dpp::slashcommand_t& event)
{
    const std::string name = event.command.get_command_name();

    if(!m_commands.count(name))
        return;

    m_commands[name](std::map<std::string, dpp::command_value>());
}

void CommandRegistry::addCommand(Command* cmd)
{
    m_commands[cmd->name()] = [cmd](Command::Args args) {
        cmd->call(args);
    };
}
