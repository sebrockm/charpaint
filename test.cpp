#include "ImageData.hpp"
#include "CharacterMap.hpp"

#include <boost/version.hpp>
#include <iostream>
#include <fstream>

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cerr << "usage: " << argv[0] << " <image.png/jpg> <characters.txt>" << std::endl;
        return 1;
    }
        
    //ImageData imageData(argv[1]);
    //imageData.Write(std::string("out_") + argv[1]);
    
    CharacterMap map(argv[1], argv[2]);

    auto pos = map["$"];
    std::cout << "Position of $: " << pos.x << "," << pos.y << std::endl;

    pos = map["Ü"];
    std::cout << "Position of Ü: " << pos.x << "," << pos.y << std::endl;

    return 0;
}
