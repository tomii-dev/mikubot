#include "command/commandregistry.hpp"

#include "mikubot.hpp"

void CommandRegistry::handleCommand(const dpp::slashcommand_t& event)
{
    const std::string name = event.command.get_command_name();

    if(!m_commands.count(name))
        return;
    
    Command* cmd = m_commands.at(name);
    Command::Args args;

    for(const Option& opt : cmd->options())
    {
        const dpp::command_value& val = event.get_parameter(opt.name());
        if(val.index())
            args.emplace(opt.name(), val);
    }

    m_commands[name]->call(args, event);
}

void CommandRegistry::addCommand(Command* cmd)
{
    m_commands[cmd->name()] = cmd;
    
    MikuBot::cluster().global_command_create(cmd->get());
}
