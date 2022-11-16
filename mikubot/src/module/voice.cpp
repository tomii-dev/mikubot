#include "module/voice.hpp"

#include "command/command.hpp"
#include "module/modulemanager.hpp"

DEFINE_MODULE(Voice)

class TestCommand : public Command
{
public:
    TestCommand() : Command("test", "test command")
    {
        addOption("option1", "does stuff 1", Option::STRING);
        addOption("option2", "does stuff 2", Option::INT);
        addOption("option3", "does stuff 3", Option::ATTACHMENT);
    }

    void call(const Args& args, Context ctx)
    {}
};

void Voice::init()
{
    addCommand(std::make_unique<TestCommand>());
}
