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
        ChildPrimitive(const ChildPrimitive&) = delete;
        ChildPrimitive(ChildPrimitive&& other);
        ChildPrimitive(Primitive* parent, std::unique_ptr<core::Primitive>&& newChild, Vec2f boundSize);
        virtual ~ChildPrimitive();

        ChildPrimitive& operator=(ChildPrimitive&&other);

        const Primitive* getChildPrimitive() const;
        Primitive* getChildPrimitive();

        inline operator bool()const { return static_cast<bool>(child); }

        void setAlign(Align align);
        void setVAlign(VAlign valign);

        core::Primitive* findByName(const std::string& name);
        void serialize(nii::json::entities::wrapper wrapper);

        Primitive* intersect(Vec2f pos);
        Primitive* intersectWith(Vec2f& pos);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        void setChild(Primitive* parent, std::unique_ptr<Primitive>&& newChild, Vec2f boundSize);
        void setBoundSize(Vec2f bound);
        std::unique_ptr<Primitive> extractChild();
        void removeChild();

        Vec2f getShrinkedSize() const;
        Vec2f getSize() const;
        Vec2f getBoundSize() const;
        

        

    // protected:
        std::unique_ptr<Primitive> child;

        Align align;
        VAlign valign;
    };
}