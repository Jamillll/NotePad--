#define CATCH_CONFIG_RUNNER 
#include "catch.hpp"
#include "TextFile.h"

#include <iostream>

int main(int argc, char* const argv[]) {
    int result = Catch::Session().run(argc, argv);

    std::cin.get();

    return result;
}

TEST_CASE("idk man just testing rn") 
{
    using namespace TextLibrary;

    TextFile file("C:\\Programs\\NotePad--\\Tests\\TestContent.txt");

    REQUIRE(file.GetPath() == "C:\\Programs\\NotePad--\\Tests\\TestContent.txt");
}