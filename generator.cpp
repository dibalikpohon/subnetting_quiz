#include <array>
#include <random>
#include <algorithm>

typedef std::uint8_t ubyte;
typedef std::array<ubyte, 4> ip_address;
typedef std::pair<ip_address, ubyte> ip_address_prefix_length;

static std::random_device rd;
static std::uniform_int_distribution<ubyte> byte_dist(0, 255);
static std::uniform_int_distribution<ubyte> mask_dist(0, 30);

const ip_address_prefix_length generate_problem()
{
    byte_dist.reset();
    mask_dist.reset();

    ip_address ip;
    ubyte nm = mask_dist(rd);
    
    std::generate(ip.begin(), ip.end(), [&]() -> ubyte { return byte_dist(rd); });

    return {ip, nm};
}
