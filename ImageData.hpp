#pragma once

#include <stdexcept>

#include <boost/mpl/vector.hpp>
#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/io/jpeg_dynamic_io.hpp>
#include <boost/gil/extension/io/png_dynamic_io.hpp>

using namespace boost;

class ImageData
{
private:
    enum { jpg, png };
    using Image = gil::gray8_image_t;
    Image _image;

    static auto GetTypeOfFile(std::string const& fileName)
    {
        if (fileName.rfind(".jpg") == fileName.length() - 4 || fileName.rfind(".jpeg") == fileName.length() - 5)
            return jpg;

        if (fileName.rfind(".png") == fileName.length() - 4)
            return png;

        throw std::invalid_argument("'" + fileName + "' is neither a jpeg nor a png file");
    }

    struct InvertGray
    {
        template <class Pixel>
        void operator()(Pixel& pixel) const
        {
            pixel[0] = 255 - pixel[0];
        }
    };

public:
    ImageData(std::string const& fileName, bool inverted = false)
    {
        switch (GetTypeOfFile(fileName))
        {
        case jpg: gil::jpeg_read_and_convert_image(fileName, _image); break;
        case png: gil::png_read_and_convert_image(fileName, _image); break;
        }

        if (inverted)
            gil::for_each_pixel(gil::view(_image), InvertGray());
    }

    auto GetView() const
    {
        return gil::const_view(_image);
    }

    auto GetView()
    {
        return gil::view(_image);
    }

    auto GetView(int xTileSize, int yTileSize, int xIndex, int yIndex) const
    {
        return gil::subimage_view(GetView(), xTileSize * xIndex, yTileSize * yIndex, xTileSize, yTileSize);
    }

    auto GetView(int xTileSize, int yTileSize, int xIndex, int yIndex)
    {
        return gil::subimage_view(GetView(), xTileSize * xIndex, yTileSize * yIndex, xTileSize, yTileSize);
    }

    template <class View>
    static void Write(View const& view, std::string const& fileName)
    {
        switch (GetTypeOfFile(fileName))
        {
        case jpg: gil::jpeg_write_view(fileName, view); break;
        case png: gil::png_write_view(fileName, view); break;
        }
    }
};
