#include "NII/UI/Core/ChildPrimitive.hpp"


namespace nii::ui::core
{
    ChildPrimitive::ChildPrimitive()
        : child()
        , align(AlignFill)
        , valign(VAlignFill)
    {}
    
    ChildPrimitive::ChildPrimitive(Primitive* parent, std::unique_ptr<core::Primitive>&& newChild, Vec2f boundSize)
        : child()
        , align(AlignFill)
        , valign(VAlignFill)
    {
        setChild(parent, std::move(newChild), boundSize);
    }

    ChildPrimitive::ChildPrimitive(ChildPrimitive&& other)
        : child(std::move(other.child))
        , align(other.align)
        , valign(other.valign)
    {    }

    ChildPrimitive::~ChildPrimitive()
    {}

    Primitive* ChildPrimitive::intersect(Vec2f pos)
    {
        

        if (child) {
            auto [width, height] = child->getSize();
            auto [bwidth, bheight] = child->getBoundSize();
            Vec2f bound {0.f, 0.f};
            switch (align) {
                case Align::Left:
                    break;
                case Align::Center:
                    bound.x = (bwidth-width) / 2.f;
                    break;
                case Align::Right:
                    bound.x = bwidth-width;
                    break;
            }

            switch (valign) {
                case VAlign::Top:
                    break;
                case VAlign::Bottom:
                    bound.y = bheight - height;
                    break;
                case VAlign::Center:
                    bound.y = (bheight - height) / 2.f;
                    break;
            }
            if (pos.x >= bound.x && pos.y >= bound.y) {
                return child->intersect({pos.x - bound.x, pos.y - bound.y});
            }
        }

        return nullptr;
    }

    void ChildPrimitive::setChild(Primitive* parent, std::unique_ptr<Primitive>&& newChild, Vec2f boundSize)
    {
        child = std::move(newChild);
        child->setBoundSize(boundSize);
        child->setParent(parent);
    }

    std::unique_ptr<core::Primitive> ChildPrimitive::extractChild()
    {
        if (child) {
            child->setParent(nullptr);
        }
        return std::move(child);
    }

    void ChildPrimitive::removeChild()
    {
        if (child) {
            child.reset();
        }
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

    Vec2f ChildPrimitive::getBoundSize() const
    {
        return child ? child->getBoundSize() : Vec2f{0.f, 0.f};
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
        return child.get();
    }

    Primitive* ChildPrimitive::getChildPrimitive()
    {
        return child.get();
    }

    core::Primitive* ChildPrimitive::findByName(const std::string& name)
    {
        if (child) {
            return child->findByName(name);
        }
        return nullptr;
    }

}