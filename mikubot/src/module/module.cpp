#include "module/module.hpp"

const std::vector<const Command*> Module::commands() const
{
    std::vector<const Command*> commands;

    for(const std::unique_ptr<Command>& cmd : m_commands)
        commands.push_back(cmd.get());

    return commands;
}
