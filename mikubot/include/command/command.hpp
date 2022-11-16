#pragma once

#include "option.hpp"

#include <string>
#include <map>
#include <vector>

#include <dpp/dpp.h>

class Command
{
public:
    Command(const std::string& name, const std::string& desc);
    
    using Args = std::map<std::string, dpp::command_value>;
    using Context = const dpp::slashcommand_t&;

    virtual void call(const Args& args, Context ctx) = 0;

    inline const std::string& name() const { return m_name; }
    inline const std::string& desc() const { return m_desc; }
    inline const std::vector<Option>& options() const { return m_options; }
    
    // should only be called once, by CommandRegistry
    const dpp::slashcommand& get();

protected:
    Option& addOption(const std::string& name, const std::string& desc, Option::Type type);

private:
    std::string m_name;
    std::string m_desc;

    dpp::slashcommand m_cmd;

    std::vector<Option> m_options;
};

#define SETUP_COMMAND(name, module, str, desc) class name##Command : public Command { module* m_module; public: name##Command(module* mod); \
    void call(const Args&, Context) override; }; name##Command::name##Command(module* mod) : Command(str, desc), m_module(mod)

#define COMMAND(name) void name##Command::call(const Args& args, Context ctx)
