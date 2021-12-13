#pragma once

#include "Primitive.hpp"
#include "../Traits.hpp"

#include <SFML/Graphics/RenderTarget.hpp>


namespace nii::ui::core
{

    class ChildPrimitive: public sf::Drawable
    {
    public:

        ChildPrimitive();
        virtual ~ChildPrimitive();

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        void setChild(Primitive* parent, Primitive* newChild, Vec2f boundSize);
        void setBoundSize(Vec2f bound);
        Vec2f getShrinkedSize() const;

        const Primitive* getChildPrimitive() const;
        Primitive* getChildPrimitive();

        inline operator bool()const { return static_cast<bool>(child); }

        void setAlign(Align align);
        void setVAlign(VAlign valign);

    protected:
        Primitive* child;

        Align align;
        VAlign valign;
    };
}