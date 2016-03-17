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

    auto view = map["$"];
    ImageData::Write(view, "dollar.png");

    view = map["Ü"];
    ImageData::Write(view, "UE.png");

    view = map["A"];
    ImageData::Write(view, "A.png");

    view = map["a"];
    ImageData::Write(view, "a.png");

    view = map["B"];
    ImageData::Write(view, "B.png");

    view = map["b"];
    ImageData::Write(view, "b.png");

    view = map["Y"];
    ImageData::Write(view, "Y.png");

    view = map["y"];
    ImageData::Write(view, "y.png");

    view = map["+"];
    ImageData::Write(view, "plus.png");

    view = map["["];
    ImageData::Write(view, "rect1.png");

    return 0;
}
