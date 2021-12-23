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
        inline static std::string GetDefaultName() { return "Border"; }

        Border(const std::string& name = {});
        Border(const Border& other) = delete;
        Border(Border&& other) = delete;
        virtual ~Border();

        Primitive* intersectNext(Vec2f pos) override;

        inline void setPadding(IndentsFloat newPadding)
        {
            padding = newPadding;
            Primitive::redraw();
        }

        inline IndentsFloat getPadding() const { return padding; }


        const sf::Color& getBorderColor() const;
        void setBorderColor(const sf::Color& color);

        float getBorderRadius(float radius) const;
        void setBorderRadius(float radius);
        
        void setOutlineThickness(float thickness);
        void setOutlineColor(const sf::Color& color);


        Vec2f getChildBoundSize() const;
        void setChild(core::Primitive* child);
        void setChild(std::unique_ptr<core::Primitive>&& child);
        std::unique_ptr<core::Primitive> extractRoot();

    
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void redraw() /* override */;

        void setSize(const Vec2f& size, bool withRedraw = true) override;
        Vec2f getShrinkedSize() const override;

        core::Primitive* findByName(const std::string& name) override;

    // private:
        core::ChildPrimitive child;
        mutable nii::graphics::shapes::RoundedShape shape;
        
    };
}