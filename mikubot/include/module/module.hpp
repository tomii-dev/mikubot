#pragma once

#include "command/command.hpp"

#include <memory>
#include <vector>
#include <string>

#include <dpp/appcommand.h>

class Module
{
public: 
    virtual void init() = 0;
    virtual const std::string desc() = 0;

protected:
    inline void addCommand(std::unique_ptr<Command> cmd) { m_commands.push_back(std::move(cmd)); };

private:
    std::vector<std::unique_ptr<Command>> m_commands;

    friend class ModuleManager;
};
