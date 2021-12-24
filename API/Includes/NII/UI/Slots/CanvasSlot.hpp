#pragma once

#include "../Core/Primitive.hpp"
#include "../Core/ChildPrimitive.hpp"
#include "../Traits.hpp"

#include <SFML/Graphics/RenderTarget.hpp>


namespace nii::ui::slots
{

    class CanvasSlot: public nii::ui::core::ChildPrimitive, private sf::Transformable
    {
    public:
        inline void setPosition(Vec2f position)
        {
            sf::Transformable::setPosition(position);
            if (child) {
                child->redraw();
            }
        }

        inline void setSize(Vec2f size)
        {
            setBoundSize(size);
        }

        inline void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            states.transform *= getTransform();
            nii::ui::core::ChildPrimitive::draw(target, states);
        }

        inline void setChild(nii::ui::core::Primitive* parent, nii::ui::core::Primitive* newChild, Vec2f size, Vec2f position)
        {
            setChild(parent, std::unique_ptr<nii::ui::core::Primitive>(newChild), size, position);
        }

        inline void setChild(nii::ui::core::Primitive* parent, std::unique_ptr<nii::ui::core::Primitive>&& newChild, Vec2f size, Vec2f position)
        {
            sf::Transformable::setPosition(position);
            nii::ui::core::ChildPrimitive::setChild(parent, std::move(newChild), size);
        }

        inline void serialize(nii::json::entities::wrapper wrapper)
        {
            if (child) {
                wrapper["slot"]["position"]["x"] = getPosition().x;
                wrapper["slot"]["position"]["y"] = getPosition().y;

                wrapper["slot"]["size"]["x"] = child->boundSize.x;
                wrapper["slot"]["size"]["y"] = child->boundSize.y;
                
                child->serialize(wrapper);
            } else {
                wrapper = nullptr;
            }
        }

        using sf::Transformable::getPosition;

    private:
        using nii::ui::core::ChildPrimitive::setChild;
        using nii::ui::core::ChildPrimitive::serialize;
        using nii::ui::core::ChildPrimitive::draw;

        using sf::Transformable::setPosition;
    public:

    };
}