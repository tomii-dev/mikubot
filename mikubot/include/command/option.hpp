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

    Option(const std::string& name, const std::string& desc, Type type, bool required = false);

    Option& addChoice(const std::string& name, const dpp::command_value& val);
    
    inline const std::string& name() const { return m_name; }
    inline const std::string& desc() const { return m_desc; }
    inline const std::string& typeStr() const { return TYPE_STRS.at(m_type); }
    inline const std::vector<std::string>& choices() const { return m_choices; }
    inline const dpp::command_option& get() const { return m_opt; }

private:
    std::string m_name;
    std::string m_desc;
    Type m_type;

    std::vector<std::string> m_choices;

    static const std::map<Type, std::string> TYPE_STRS;

    dpp::command_option m_opt;
};
