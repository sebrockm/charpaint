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
    enum { jpg, png } _type;
    using Image = gil::gray8_image_t; gil::gray8c_view_t a;
    Image _image;

    static auto GetTypeOfFile(std::string const& fileName)
    {
        if (fileName.rfind(".jpg") == fileName.length() - 4 || fileName.rfind(".jpeg") == fileName.length() - 5)
            return jpg;

        if (fileName.rfind(".png") == fileName.length() - 4)
            return png;

        throw std::invalid_argument("'" + fileName + "' is neither a jpeg nor a png file");
    }

public:
    ImageData(std::string const& fileName)
    {
        switch (GetTypeOfFile(fileName))
        {
        case jpg: gil::jpeg_read_and_convert_image(fileName, _image); break;
        case png: gil::png_read_and_convert_image(fileName, _image); break;
        }
    }

    auto GetView() const
    {
        return gil::const_view(_image);
    }

    auto GetView(int xTileSize, int yTileSize, int xIndex, int yIndex) const
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
