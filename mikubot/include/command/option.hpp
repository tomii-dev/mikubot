#pragma once

#include <string>

#include <dpp/appcommand.h>

class Option
{
public:
    enum Type
    {
        STRING,
        INT,
        BOOL,
        USER,
        CHANNEL,
        ROLE,
        MENTIONABLE,
        DOUBLE,
        ATTACHMENT
    };

    Option(const std::string& name, const std::string& desc, Type type);

    void addChoice(const std::string& name, const dpp::command_value& val);
    
    inline const std::string& name() const { return m_name; }
    inline const dpp::command_option& get() const { return m_opt; }

private:
    std::string m_name;

    dpp::command_option m_opt;
};
