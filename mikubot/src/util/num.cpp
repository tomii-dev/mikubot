#include "util/num.hpp"

#include <random>

int num::random(int beg, int end)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(beg, end);

    return dist(rng);
}

const std::string num::randomStr(int beg, int end)
{
    return std::to_string(random(beg, end));
}
