#include <NII/UI/Image.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>

using std::cout;
using std::endl;


namespace nii::ui
{
     Image::Image()
        : Primitive()
        , shape({100, 100})
        , size({30, 30})
    {
        cout << "Image ()" << endl; 
    }

    Image::Image(const Image& other)
        : Primitive()
        , shape({100, 100})
        , size({30, 30})
    {
        cout << "Image cp" << endl;
    }

    Image::Image(Image&& other)
        : Primitive()
        , shape({100, 100})
        , size({30, 30})
    {
        cout << "Image mv" << endl;
    }

    Image::~Image()
    {
        cout << "Image ~~" << endl;
    }

    void Image::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(shape, states);
    }

    void Image::setSize(const Vec2f& size)
    {
        shape.setSize({size.x, size.y});
        redraw();
    }

    Vec2f Image::getShrinkedSize() const
    {
        auto [left, top, width, height] = shape.getTextureRect();
        return {width, height};
    }

}
