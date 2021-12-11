#pragma once

#include "Core/Primitive.hpp"
#include "Traits.hpp"

#include <NII/Graphics/Shapes/RoundedShape.hpp>

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


        const sf::Color& getBorderColor() const;
        void setBorderColor(const sf::Color& color);

        float getBorderRadius(float radius) const;
        void setBorderRadius(float radius);
        
        void setOutlineThickness(float thickness);
        void setOutlineColor(const sf::Color& color);


        Vec2f getChildBoundSize() const;
        void setChild(core::Primitive* child);
    
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void redraw() /* override */;

        void setSize(const Vec2f& size, bool withRedraw = true) override;
        Vec2f getShrinkedSize() const override;

    // private:
        core::Primitive* child;
        nii::graphics::shapes::RoundedShape shape;
        
    };
}