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
    std::vector<std::string> _utf8Chars;
    size_t _textWidth = 0;
    size_t _textHeight = 0;

    static std::string ExtractUtf8Char(char const* pString)
    {
        std::string mb;
        unsigned char c = *pString;

        mb += *pString;
        if (c >= 0xc2) 
            mb += *++pString;
        if (c >= 0xe0)
            mb += *++pString;
        if (c >= 0xf0)
            mb += *++pString;

        return mb;
    }

public:
    CharacterMap(std::string const& imageFile, std::string const& characterFile)
        : _data(imageFile)
    {
        std::ifstream file(characterFile);
        if (!file)
            throw std::invalid_argument("Cannot open '" + characterFile + "'.");

        std::string line;
        for (_textHeight = 0; std::getline(file, line); ++_textHeight)
        {
            size_t mbCount = 0;
            for (size_t pos = 0; pos < line.length();)
            {
                std::string mb = ExtractUtf8Char(&line[pos]);
                pos += mb.length();

                if (_table.find(mb) != _table.end())
                    throw std::invalid_argument("'" + mb + "' appears twice in '" + characterFile + "'.");

                _table[mb] = { mbCount++, _textHeight };
                _utf8Chars.push_back(mb);
            }

            if (mbCount > _textWidth)
                _textWidth = mbCount;
        }
    }

    auto operator[](std::string const& mb)
    {
        auto pos = _table.at(mb);
        auto width = _data.GetView().width();
        auto height = _data.GetView().height();

        return _data.GetView(width / _textWidth, height / _textHeight, pos.x, pos.y);
    }

    size_t GetCharacterCount() const
    {
        return _utf8Chars.size();
    }

    auto begin() const
    {
        return _utf8Chars.begin();
    }

    auto end() const
    {
        return _utf8Chars.end();
    }
};
