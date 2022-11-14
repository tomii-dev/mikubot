#include "module.hpp"

class HelpModule : public Module
{
public:
    void init() override;

    inline const std::string desc() override
    {
        return "";
    }
};
