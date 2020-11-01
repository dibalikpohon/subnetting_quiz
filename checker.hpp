typedef std::uint8_t ubyte;
typedef std::array<ubyte, 4> ip_address;
typedef std::pair<ip_address, ubyte> ip_address_prefix_length;

extern const ip_address get_wildcard_mask(ubyte suffix);
extern const ip_address get_subnet_mask(ubyte suffix);

extern const ip_address get_network(const ip_address_prefix_length& ipnm);
extern const ip_address get_broadcast(const ip_address_prefix_length& ipnm);
