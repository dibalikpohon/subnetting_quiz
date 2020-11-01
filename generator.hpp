typedef std::uint8_t ubyte;
typedef std::array<ubyte, 4> ip_address;
typedef std::pair<ip_address, ubyte> ip_address_prefix_length;

extern const ip_address_prefix_length generate_problem();
