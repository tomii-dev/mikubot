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

    Option(Type type);

    void addChoice(const std::string& name, const dpp::command_value& val);

    inline const dpp::command_option& get() const { return m_opt; }
private:
    dpp::command_option m_opt;
};
