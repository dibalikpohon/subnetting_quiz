#include <istream>
#include <ostream>

#include <array>
#include <utility>
#include <algorithm>

#include <cstring>

typedef std::uint8_t ubyte;
typedef std::array<ubyte, 4> ip_address;
typedef std::pair<ip_address, ubyte> ip_address_prefix_length;

typedef std::string::const_iterator string_ci;

std::ostream& operator<< (std::ostream& os, const ip_address& addr)
{
    for (ubyte d = 0; d < addr.max_size(); d++) {
        os << static_cast<uint16_t>(addr[d]);
        if (d != addr.max_size() - 1) os << '.';
    }

    return os;
}

std::ostream& operator<< (std::ostream& os, const ip_address_prefix_length& addr)
{
    os << addr.first << '/' << static_cast<uint16_t>(addr.second);

    return os;
}

std::istream& operator>> (std::istream& is, ip_address& addr)
{
    addr.fill(0);
    char* line = new char[16];
    is >> line;
    std::string input(line); // format: xxx.xxx.xxx.xxx (15 chars)

    unsigned long num = 0;
    const char *start, *end;

    // condition checking...

    // if the first character is found '.'
    if (input[0] == '.') {
        is.setstate(std::ios_base::failbit);
        goto cleanup;
    }

    // if the '.' is not counted 3
    if (std::count(input.cbegin(), input.cend(), '.') != 3) {
        is.setstate(std::ios_base::failbit);
        goto cleanup;
    }

    // if the string has consecutive dots or 
    // the string has something besides (digit |XOR| dot)
    for (string_ci ci = input.cbegin(); ci != input.cend(); ci++) {
        if (*ci == '.' && *(ci + 1) == '.') {
            is.setstate(std::ios_base::failbit);
            goto cleanup;
        } else if (!(std::isdigit(*ci) ^ (*ci == '.'))) {
            is.setstate(std::ios_base::failbit);
            goto cleanup;   
        }
    }

    start = input.data();
    for (ubyte d = 0; d < 4; d++) {
        num = 0;

        if (d < 3)
            end = strchr(start, '.');
        else 
            end = input.data() + input.length();

        for (const char* e = start; e < end; e++) {
                num *= 10;
                num += (*e) - '0';
        }
        if (num > 255) {
            is.setstate(std::ios_base::failbit);
            goto cleanup;
        }
        addr[d] = num;
        start = end + 1;
    }

cleanup:
    // perform cleanup...
    delete[] line;
    input.clear();
    input.resize(0);

    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return is;
}
