#pragma once

#include <boost/gil/gil_all.hpp>

using namespace boost;

struct NormDifference
{
    template <class View>
    double operator()(View const& view1, View const& view2) const
    {
        int height = std::min(view1.height(), view2.height());
        int width = std::min(view1.width(), view2.width());
        const double maxDiff = 255.0 * height * width;

        double diffSum = 0.0;
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                double color1 = view1(x, y);
                double color2 = view2(x, y);
                double diff = std::abs(color1 - color2);
                diffSum += diff;
            }
        }

        return diffSum / maxDiff;
    }
};
