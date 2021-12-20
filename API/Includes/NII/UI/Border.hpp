#pragma once

#include "Core/Primitive.hpp"
#include "Core/ChildPrimitive.hpp"
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
        virtual ~Border();

        Primitive* intersectNext(Vec2f pos) override;

        inline void hover() override
        {
            shape.setFillColor({255,0,0,50});
            Primitive::redraw();
        }
        inline void unhover() override
        {
            shape.setFillColor({0,255,0,50});
            Primitive::redraw();
        }

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
        core::ChildPrimitive child;
        nii::graphics::shapes::RoundedShape shape;
        
    };
}