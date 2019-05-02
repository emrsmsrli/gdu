//
// Created by Emre Şimşirli on 2019-03-23.
//

#include <iostream>
#include <string>

#include "encrypted.h"
#include "range.h"

int main(int /*argc*/, char** /*argv*/)
{
    encrypted<int> ea = 4;
    encrypted<int> a = ea;
    auto aa = ea + 5;
    aa = ea + a;
    aa = ea;
    aa = encrypted<int>(4);
    aa = 456;

    encrypted<float> ef = 4.f;
    encrypted<float> e = 9.f;
    auto ee = ef + 5.f;
    ee = ef + e;
    ee = ef;
    ee = encrypted<float>(3.f);
    ee = 5.3f;

    std::string sx = "emreee";

    encrypted<std::string> str = sx;
    encrypted<std::string> str2 = "asda";
    encrypted<std::string> str3 = "this is a long string";
    str = str2;
    str = "asdad";

    std::cout << ef + e << '\n';
    std::cout << str << '\n';
    std::cout << str3 << '\n';

    std::cout << ea << '\n';

    for(const auto& i : range(4)) {
        std::cout << i << '\n';
    }

    for(const auto& c : range('a', 'z', true)) {
        std::cout << c << " ";
    }
    std::cout << '\n';

    std::cout << std::boolalpha << range(0, 4, true).contains(5) << '\n';

    return 0;
}
