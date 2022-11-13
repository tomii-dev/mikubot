#include "mikubot.hpp"

#include <sstream>
#include <fstream>

MikuBot::MikuBot()
{
    std::stringstream ss;
    std::ifstream ifs("token");
    ss << ifs;

    m_cluster = std::make_unique<dpp::cluster>(ss.str());
}
