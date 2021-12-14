#include "NII/UI/Core/ChildPrimitive.hpp"


namespace nii::ui::core
{
    ChildPrimitive::ChildPrimitive()
        : child(nullptr)
        , align(AlignFill)
        , valign(VAlignFill)
    {}
    
    ChildPrimitive::ChildPrimitive(Primitive* parent, Primitive* newChild, Vec2f boundSize)
        : child(nullptr)
        , align(AlignFill)
        , valign(VAlignFill)
    {
        setChild(parent, newChild, boundSize);
    }

    ChildPrimitive::ChildPrimitive(ChildPrimitive&& other)
        : child(other.child)
        , align(other.align)
        , valign(other.valign)
    {
        other.child = nullptr;
    }

    ChildPrimitive::~ChildPrimitive()
    {}

    void ChildPrimitive::setChild(Primitive* parent, Primitive* newChild, Vec2f boundSize)
    {
        child = newChild;
        child->setBoundSize(boundSize);
        child->setParent(parent);
    }

    void ChildPrimitive::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (child) {
            auto [width, height] = child->getSize();
            auto [bwidth, bheight] = child->getBoundSize();
            switch (align) {
                case Align::Left:
                    break;
                case Align::Center:
                    states.transform.translate((bwidth-width) / 2.f, 0);
                    break;
                case Align::Right:
                    states.transform.translate(bwidth-width, 0);
                    break;
            }

            switch (valign) {
                case VAlign::Top:
                    break;
                case VAlign::Bottom:
                    states.transform.translate(0, bheight - height);
                    break;
                case VAlign::Center:
                    states.transform.translate(0, (bheight - height) / 2.f);
                    break;
            }
            target.draw(*child, states);
        }
    }

    void ChildPrimitive::setBoundSize(Vec2f bound)
    {
        if (child) {
            child->setBoundSize(bound);
        }
    }

    Vec2f ChildPrimitive::getShrinkedSize() const
    {
        if (child) {
            return child->getShrinkedSize();
        } else {
            return {0.f, 0.f};
        }
    }

    Vec2f ChildPrimitive::getSize() const
    {
        return child ? child->getSize() : Vec2f{0.f, 0.f};
    }


    void ChildPrimitive::setAlign(Align align)
    {
        this->align = align;
        if (child) {
            child->redraw();
        }
    }

    void ChildPrimitive::setVAlign(VAlign valign)
    {
        this->valign = valign;
        if (child) {
            child->redraw();
        }
    }



    const Primitive* ChildPrimitive::getChildPrimitive() const
    {
        return child;
    }

    Primitive* ChildPrimitive::getChildPrimitive()
    {
        return child;
    }

}