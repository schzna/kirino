#include <array>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>

#include "aes.hpp"
#include "arith.hpp"

int main()
{
    std::random_device seed_gen;
    std::default_random_engine engine(seed_gen());
    std::normal_distribution<> dist(0.0, 1.0);

    std::string keystr = "2b7e151628aed2a6abf7158809cf4f3c";
    std::string datastr = "3243f6a8885a308d313198a2e0370734";

    std::array<uint8_t, 16> key = {};
    std::array<uint8_t, 16> data = {};
    for (size_t i = 0; i < 16; i++)
    {
        key.at(i) = std::stoul(keystr.substr(i * 2, 2), nullptr, 16);
        data.at(i) = std::stoul(datastr.substr(i * 2, 2), nullptr, 16);
    }

    AES128<AEStype::AES128> aes(key);

    auto ciph = aes.encrypt(data);

    print_state(ciph);
    std::cout << "\n";
    print_state(aes.decrypt(ciph));

    return 0;
}