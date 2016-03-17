#include "ImageData.hpp"
#include "CharacterMap.hpp"
#include "ImageCompare.hpp"

#include <iostream>
#include <fstream>

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cerr << "usage: " << argv[0] << " <image.png/jpg> <characters.txt>" << std::endl;
        return 1;
    }
    
    CharacterMap map(argv[1], argv[2]);

    auto a = map["a"];
    auto ae = map[" "];

    std::cout << NormDifference()(a, ae) << std::endl;

    return 0;
}
