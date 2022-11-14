#include "module/help.hpp"

#include "command/command.hpp"
#include "module/modulemanager.hpp"

DEFINE_MODULE(HelpModule)

class HelpCommand : public Command
{
public:
    HelpCommand() : Command("help", "get help with command usage")
    {
        addOption("module", "the specific module to get help with", Option::STRING)
            .addChoice("voice", "VoiceModule");
    }

    void call(const Args& args, Context ctx) override 
    {
        if(!args.count("module"))
        {
            ctx.reply("test lol");
            return;
        }

        ctx.reply("you provided module: " + std::get<std::string>(args.at("module")));
    }
};

void HelpModule::init()
{
   addCommand(std::make_unique<HelpCommand>());
}
