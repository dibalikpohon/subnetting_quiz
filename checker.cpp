#include <array>
#include <stdint.h>
#include <tuple>

#include <string>

typedef uint8_t ubyte;
typedef std::array<ubyte, 4> ip_address;
typedef std::pair<ip_address, ubyte> ip_address_prefix_length;

const ip_address get_wildcard_mask(ubyte suffix)
{
    // creates bits.
    ip_address wildcard_mask; 
    uint32_t bits(0);
    suffix = 32 - suffix;

    while (suffix > 0) {
        bits <<= 1;
        bits |= 1;
        suffix--;
    }

    wildcard_mask[0] = (bits & 0xFF000000) >> (8 * 3);
    wildcard_mask[1] = (bits & 0x00FF0000) >> (8 * 2);
    wildcard_mask[2] = (bits & 0x0000FF00) >> (8 * 1);
    wildcard_mask[3] = (bits & 0x000000FF) >> (8 * 0);

    return wildcard_mask;
}

const ip_address get_subnet_mask(ubyte suffix)
{
    ip_address subnet_mask = get_wildcard_mask(suffix);

    // subnet mask is a flipped wildcard mask.
    for (ubyte& u : subnet_mask) u = ~u;

    return subnet_mask;
}

const ip_address get_network(const ip_address_prefix_length& ipnm)
{
    ip_address subnet_mask = get_subnet_mask(ipnm.second);
    ip_address network;

    for (ubyte d = 0; d < network.max_size(); d++) 
        network[d] = subnet_mask[d] & ipnm.first[d];

    return network;
}

const ip_address get_broadcast(const ip_address_prefix_length& ipnm)
{
    ip_address network = get_network(ipnm);
    ip_address wildcard_mask = get_wildcard_mask(ipnm.second);
    ip_address broadcast;

    for (ubyte d = 0; d < broadcast.max_size(); d++)
        broadcast[d] = network[d] ^ wildcard_mask[d];

    return broadcast;
}
