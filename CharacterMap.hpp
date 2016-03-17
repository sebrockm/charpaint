#pragma once

#include "ImageData.hpp"

#include <fstream>
#include <map>

using namespace boost;

class CharacterMap
{
private:
    struct Pos
    {
        size_t x, y;
    };

private:
    ImageData _data;
    std::map<std::string, Pos> _table;

public:
    CharacterMap(std::string const& imageFile, std::string const& characterFile)
        : _data(imageFile)
    {
        std::ifstream file(characterFile);
        if (!file)
            throw std::invalid_argument("Cannot open '" + characterFile + "'.");

        std::string line;
        for (size_t i = 0; std::getline(file, line); ++i)
        {
            size_t mbCount = 0;
            for (size_t j = 0; j < line.length(); ++j)
            {
                std::string mb;
                unsigned char c = line[j];

                mb += line[j];
                if (c >= 0xc2) 
                    mb += line[++j];
                if (c >= 0xe0)
                    mb += line[++j];
                if (c >= 0xf0)
                    mb += line[++j];

                std::cout << mb;

                if (_table.find(mb) != _table.end())
                    throw std::invalid_argument("'" + mb + "' appears twice in '" + characterFile + "'.");
                _table[mb] = { i, mbCount++ };
            }
            std::cout << std::endl;
        }
    }

    auto operator[](std::string const& mb)
    {
        auto pos = _table.at(mb);
        return pos;
    }
};
