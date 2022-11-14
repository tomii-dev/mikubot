#pragma once

#include "command/command.hpp"

#include <memory>
#include <string>
#include <map>
#include <functional>

#include <dpp/appcommand.h>
#include <dpp/dispatcher.h>

class CommandRegistry
{
public:
    void handleCommand(const dpp::slashcommand_t& event);

    void addCommand(Command* cmd); 
private:
    using Action = std::function<void(Command::Args)>;
    std::map<std::string, Action> m_commands;
};
