#define CATCH_CONFIG_RUNNER 
#include "catch.hpp"
#include <iostream>

int main(int argc, char* const argv[]) {
    int result = Catch::Session().run(argc, argv);

    std::cin.get();

    return result;
}

unsigned int Factorial(unsigned int number) {
    return number <= 1 ? number : Factorial(number - 1) * number;
}

TEST_CASE("Factorials are computed", "[factorial]") {
    REQUIRE(Factorial(1) == 1);
    REQUIRE(Factorial(2) == 2);
    REQUIRE(Factorial(3) == 6);
    REQUIRE(Factorial(10) == 3628800);
}