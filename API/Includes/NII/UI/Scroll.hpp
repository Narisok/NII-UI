#pragma once

#include "Core/Primitive.hpp"
#include "Core/ChildPrimitive.hpp"
#include "Traits.hpp"

#include <SFML/Graphics.hpp>

namespace nii::ui
{
    class Scroll: public core::Primitive
    {
    public:
        Scroll();
        virtual ~Scroll();
    
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        void redraw() /* override */;

        void setSize(const Vec2f& size, bool withRedraw = true) override;
        Vec2f getShrinkedSize() const override;

        void setChild(core::Primitive* child);

        void setViewSize(const Vec2f& newSize);
        void resetViewSize();
        void move(Vec2f pos);


    private:
        void restartRenderer(Vec2f size);
    public:


    // private:
        // sf::RectangleShape shape;
        Vec2f size;
        Vec2f center;
        mutable sf::RenderTexture renderer;
        core::ChildPrimitive child;
        Plane plane;
        
    };
}