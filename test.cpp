#include "ImageData.hpp"
#include "CharacterMap.hpp"
#include "ImageCompare.hpp"
#include "ImageBuilder.hpp"

#include <iostream>
#include <fstream>

int main(int argc, char** argv)
{
    if (argc != 4)
    {
        std::cerr << "usage: " << argv[0] << " <original.png/jpg> <characterimage.png/jpg> <characters.txt>" << std::endl;
        return 1;
    }
    
    ImageData::Write(ImageBuilder(argv[1], argv[2], argv[3]).GetResultView(), std::string("out_") + argv[1]);

    return 0;
}
