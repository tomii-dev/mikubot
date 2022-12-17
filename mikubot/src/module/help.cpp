#include "mikubot.hpp"
#include "command/command.hpp"
#include "module/modulemanager.hpp"

class Help;

SETUP_COMMAND(Help, Help, "help", "get help with command usage.")
{
    Option& moduleOpt = addOption("module", "the specific module to get help with", Option::STRING);
    for(const std::string& moduleName : ModuleManager::modules())
        moduleOpt.addChoice(moduleName, moduleName);
}

class Help : public Module
{
public:
    const std::string desc() const override { return "get help with mikubot commands."; }

    void init() override
    {
        addCommand(std::make_unique<HelpCommand>(this));
    }

    void postInit() override
    {
        // build help embeds for modules
        for(const std::string& moduleName : ModuleManager::modules())
        {
            const Module* module = ModuleManager::getModule(moduleName);

            dpp::embed embed = dpp::embed()
                .set_title(moduleName)
                .set_description(module->desc())
                .set_color(0x86cecb);
        
            for(const Command* cmd : module->commands())
            {
                std::string desc = cmd->desc() + "\n**options:**";
                for(const Option& opt : cmd->options())
                {
                    desc += "\n" + opt.name() + " - " + opt.desc() + " *(" + opt.typeStr() + ")*";
                    for(const std::string& choice : opt.choices())
                        desc += "\n- " + choice;
                }

                embed.add_field("/" + cmd->name(), desc);
            }
            m_helpEmbeds.emplace(moduleName, embed);
        }
    }

private:
    std::map<std::string, dpp::embed> m_helpEmbeds;

    friend class HelpCommand;
};

DEFINE_MODULE(Help);

COMMAND(Help)
{
    if(!args.count("module"))
    {
        for(const auto& kv : m_module->m_helpEmbeds)
            miku().message_create(dpp::message(ctx.command.channel_id, kv.second));

        return;
    }

    const std::string& module = std::get<std::string>(args.at("module"));
    ctx.reply(dpp::message(ctx.command.channel_id, m_module->m_helpEmbeds.at(module)));
}
