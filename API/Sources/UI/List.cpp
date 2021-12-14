#include "NII/UI/List.hpp"

#include <SFML/Graphics.hpp>

namespace nii::ui
{
    List::List()
        : Primitive()
        , children()
        , plane(PlaneVertical)
    {}

    List::~List()
    {}

    void List::redraw()
    {
        if (shrinkToFit) {
            setSize(getShrinkedSize(), false);
        } else {
            setSize(getBoundSize(), false);
        }

        needRedraw = false;
    }

    void List::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // sf::RectangleShape shape(getSize());
        // shape.setFillColor({0,0,0,50});
        // shape.setOutlineColor({255,0,0,100});
        // shape.setOutlineThickness(1);
        // target.draw(shape, states);

        if (needRedraw) {
            const_cast<List*>(this)->redraw();
        }

        bool vr = plane == PlaneVertical;
        for (auto& a : children) {
            auto [width, height] = a.getSize();
            target.draw(a, states);
            states.transform.translate(vr ? 0.f : width, vr ? height : 0.f);
        }

        
    }

    void List::setSize(const Vec2f& size, bool withRedraw)
    {
        bool vr = plane == PlaneVertical;
        for (auto& a : children) {
            auto [width, height] = a.getShrinkedSize();
            a.setBoundSize({vr ? size.x : width, vr ? height : size.y});
        }

        if (withRedraw) {
            Primitive::redraw();
        }
    }

    Vec2f List::getShrinkedSize() const
    {
        float maxWidth = 0;
        float maxHeight = 0;
        bool vr = plane == PlaneVertical;
        for (auto& a : children) {
            auto [width, height] = a.getShrinkedSize();
            if (vr) {
                if (maxWidth < width) {
                    maxWidth = width;
                }
                maxHeight += height;
            } else {
                if (maxHeight < height) {
                    maxHeight = height;
                }
                maxWidth += width;
            }
        }
        return {maxWidth, maxHeight};
    }

    void List::addChild(core::Primitive* child)
    {
        auto [width, height] = getSize();
        auto [cWidth, cHeight] = child->getShrinkedSize();
        bool vr = plane == PlaneVertical;
        children.emplace_back(this, child, Vec2f{vr ? width : cWidth, vr ? cHeight : height});
    }

    // void List::removeChild(size_t idx)
    // {

    // }
    
    // Primitive* List::fetchChild(size_t idx)
    // {

    // }

    void List::setPlane(Plane newPlane)
    {
        plane = newPlane;

        Primitive::redraw();
    }



}
