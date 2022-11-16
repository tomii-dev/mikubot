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

    // method to be called after all modules have been initialised,
    // helpful for modules such as Help that reference other modules
    virtual void postInit() {}

    virtual const std::string desc() const = 0;

    const std::vector<const Command*> commands() const;

protected:
    inline void addCommand(std::unique_ptr<Command> cmd) { m_commands.push_back(std::move(cmd)); };

private:
    std::vector<std::unique_ptr<Command>> m_commands;

    friend class ModuleManager;
};
