#include "module.hpp"

class Help : public Module
{
public:
    void init() override;
    void postInit() override;
    inline const std::string desc() const override { return "get help with mikubot commands."; }

private:
    std::map<std::string, dpp::embed> m_helpEmbeds;

    friend class HelpCommand;
};
