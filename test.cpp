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
    ImageData::Write(view, "dollar.jpg");

    view = map["Ü"];
    ImageData::Write(view, "UE.jpg");

    view = map["A"];
    ImageData::Write(view, "A.jpg");

    view = map["a"];
    ImageData::Write(view, "a.jpg");

    view = map["B"];
    ImageData::Write(view, "B.jpg");

    view = map["b"];
    ImageData::Write(view, "b.jpg");

    view = map["Y"];
    ImageData::Write(view, "Y.jpg");

    view = map["y"];
    ImageData::Write(view, "y.jpg");

    view = map["+"];
    ImageData::Write(view, "plus.jpg");

    view = map["["];
    ImageData::Write(view, "rect1.jpg");

    return 0;
}
