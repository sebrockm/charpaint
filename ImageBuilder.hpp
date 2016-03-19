#pragma once

#include <algorithm>
#include <boost/gil/gil_all.hpp>

#include "ImageData.hpp"
#include "CharacterMap.hpp"
#include "ImageCompare.hpp"

class ImageBuilder
{
private:
    ImageData _originalImage;
    CharacterMap _characterMap;
    NormDifference _comparator;
    //AverageDifference _comparator;
    //LowDifferenceCount _comparator;
    int _resultHeight;
    int _resultWidth;

public:
    ImageBuilder(std::string const& originalFile, std::string const& characterImageFile, std::string const& characterFile, bool invertCharacters)
        : _originalImage(originalFile), _characterMap(characterImageFile, characterFile, invertCharacters)
    {
        auto charHeight = _characterMap.GetCharacterImageHeight();
        auto charWidth = _characterMap.GetCharacterImageWidth();
        auto originalHeight = _originalImage.GetView().height();
        auto originalWidth = _originalImage.GetView().width();

        auto xTiles = originalWidth / charWidth;
        auto yTiles = originalHeight / charHeight;

        _resultHeight = yTiles * charHeight;
        _resultWidth = xTiles * charWidth;

        for (int y = 0; y < yTiles; ++y)
        {
            for (int x = 0; x < xTiles; ++x)
            {
                auto tileView = _originalImage.GetView(charWidth, charHeight, x, y);

                std::string bestChar;
                double bestValue = std::numeric_limits<double>::max();
                for (auto mb : _characterMap)
                {
                    double diff = _comparator(tileView, _characterMap[mb]);
                    if (diff < bestValue)
                    {
                        bestValue = diff;
                        bestChar = mb;
                    }
                }

                gil::copy_pixels(_characterMap[bestChar], tileView);
            }
        }
    }

    auto GetResultView() const
    {
        return _originalImage.GetView(_resultWidth, _resultHeight, 0, 0);
    }
};
