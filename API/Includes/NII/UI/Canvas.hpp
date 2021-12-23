#pragma once

#include "Core/Primitive.hpp"
#include "Slots/CanvasSlot.hpp"
#include "Traits.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

namespace nii::ui
{
    class Canvas: public core::Primitive
    {
    public:
        inline static std::string GetDefaultName() { return "Canvas"; }

        Canvas(const std::string& name = {});
        virtual ~Canvas();

        Primitive* intersectNext(Vec2f pos) override;
    
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        void redraw() /* override */;

        void setSize(const Vec2f& size, bool withRedraw = true) override;
        Vec2f getShrinkedSize() const override;


        void setViewSize(const Vec2f& newSize);

        void addChild(Primitive* primitive, Vec2f size, Vec2f position);

    private:
        void restartRenderer(Vec2f size);
    public:


    // private:
        mutable sf::RenderTexture renderer;
        std::vector<slots::CanvasSlot> slots;
        Vec2f size;
        
    };
}