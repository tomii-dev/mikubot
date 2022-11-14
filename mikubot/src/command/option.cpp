#include "command/option.hpp"

#include <map>

Option::Option(const std::string& name, const std::string& desc, Type type)
    : m_name(name)
{
    static const std::map<Type, dpp::command_option_type> typeMap =
    {
        {STRING, dpp::co_string},
        {INT, dpp::co_integer},
        {BOOL, dpp::co_boolean},
        {USER, dpp::co_user},
        {CHANNEL, dpp::co_channel},
        {ROLE, dpp::co_role},
        {MENTIONABLE, dpp::co_mentionable},
        {DOUBLE, dpp::co_number},
        {ATTACHMENT, dpp::co_attachment}
    };

    m_opt = dpp::command_option(typeMap.at(type), name, desc);
}

void Option::addChoice(const std::string& name, const dpp::command_value& val)
{
   m_opt.add_choice(dpp::command_option_choice(name, val)); 
}