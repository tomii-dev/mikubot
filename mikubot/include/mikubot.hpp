#pragma once

#include <memory>
#include <cassert>

namespace dpp
{
    class cluster;
}

class MikuBot
{
public:
    static void make();
    static void get();
private:
    MikuBot();
    
    std::unique_ptr<dpp::cluster> m_cluster;

    static std::unique_ptr<MikuBot> s_instance;
};
