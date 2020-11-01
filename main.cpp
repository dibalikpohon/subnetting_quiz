#include <iostream>
#include <string>
#include <algorithm>

#include "wrapper.hpp"

void clean_input(std::istream& is);

int main()
{
    ip_address_prefix_length problem;
    ip_address solve, answer;
    char chr;
    while (true) {
        std::cout << "\n";
        problem = std::move(generate_problem());
        std::cout << problem << "? ";
        chr = std::cin.get();
        std::cin.get();
        if (chr == 'n') continue;
        if (chr == 'q') break;
        
        std::cout << "network: ";
        std::cin >> solve;
        answer = get_network(problem);
        if (solve != answer) std::cout << "FALSE: " << answer << std::endl;
        clean_input(std::cin);

        std::cout << "netmask: ";
        std::cin >> solve;
        answer = get_subnet_mask(problem.second);
        if (solve != answer) std::cout << "FALSE: " << answer << std::endl;
        clean_input(std::cin);

        std::cout << "broadcast: ";
        std::cin >> solve;
        answer = get_broadcast(problem);
        if (solve != answer) std::cout << "FALSE: " << answer << std::endl;
        clean_input(std::cin);
    }
}

void clean_input(std::istream& is)
{
    if (is.fail()) {
        is.clear();
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}