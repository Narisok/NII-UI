#pragma once

#include "Core/Primitive.hpp"
#include "Traits.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

namespace nii::ui
{
    class Border: public core::Primitive, public Paddingable
    {
    public:
        Border();
        Border(const Border& other);
        Border(Border&& other);
        ~Border();

        void setChild(core::Primitive* child);

        Vec2f getChildSize() const;
    
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


        void setSize(const Vec2f& size) override;
        Vec2f getShrinkedSize() const override;

    // private:
        core::Primitive* child;
        sf::RectangleShape shape;
        
    };
}