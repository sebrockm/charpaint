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

public:
    ImageData(std::string const& fileName)
    {
        if (fileName.rfind(".jpg") == fileName.length() - 4 ||
                fileName.rfind(".jpeg") == fileName.length() - 5)
        {
            gil::jpeg_read_and_convert_image(fileName, _image);
            _type = jpg;
        }
        else if (fileName.rfind(".png") == fileName.length() - 4)
        {
            gil::png_read_and_convert_image(fileName, _image);
            _type = png;
        }
        else
        {
            throw std::invalid_argument(
                    "'" + fileName + "' is neither a jpeg nor a png file");
        }
    }

    void Write(std::string const& fileName) const
    {
        if (_type == jpg)
            gil::jpeg_write_view(fileName, gil::const_view(_image));
        else if (_type == png)
            gil::png_write_view(fileName, gil::const_view(_image));
    }

    auto GetView() const
    {
        return gil::const_view(_image);
    }
};
