#pragma once

#include "Core/Primitive.hpp"
#include "Traits.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

namespace nii::ui
{
    class Image: public core::Primitive
    {
    public:
        Image();
        Image(const Image& other);
        Image(Image&& other);
        ~Image();
    
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


        void setSize(const Vec2f& size) override;
        Vec2f getShrinkedSize() const override;

    // private:
        sf::RectangleShape shape;

        Vec2f size;
        
    };
}