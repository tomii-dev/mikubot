#pragma once

#include <string>
#include <map>
#include <vector>

#include <dpp/dpp.h>

class Command
{
public:
    Command(const std::string& name, const std::string& desc);
    
    using Args = const std::map<std::string, dpp::command_value>&;
    virtual void call(Args args) = 0;

    inline const std::string& name() const { return m_name; }
    
    inline const dpp::slashcommand& get() const { return m_cmd; }
private:
    std::string m_name;
    dpp::slashcommand m_cmd;
};
