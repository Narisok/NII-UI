#include <NII/UI/Border.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>

using std::cout;
using std::endl;


namespace nii::ui
{
     Border::Border()
        : Primitive()
        , child(nullptr)
        , shape()
    { 
        padding = {10, 10, 10, 10};
        cout << "Border ()" << endl; 
    }

    Border::Border(const Border& other)
        : Primitive()
        , child(nullptr)
        , shape()
    { 
        cout << "Border cp" << endl; 
    }

    Border::Border(Border&& other)
        : Primitive()
        , child(nullptr)
        , shape()
    { 
        cout << "Border mv" << endl; 
    }

    Border::~Border()
    { 
        cout << "Border ~~" << endl; 
    }

    void Border::setChild(Primitive* newChild)
    {
        child = newChild;
        child->setBoundSize(getChildBoundSize());
        child->setParent(this);
    }

    void Border::redraw()
    {
        if (shrinkToFit) {
            setSize(getShrinkedSize(), false);
        }

        needRedraw = false;
    }

    void Border::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (needRedraw) {
            const_cast<Border*>(this)->redraw();
        }

        target.draw(shape, states);
        if (child) {
            states.transform *= shape.getTransform();
            states.transform.translate(padding.left, padding.top);
            target.draw(*child, states);
        }
    }

    Vec2f Border::getChildBoundSize() const
    {
        auto [width, height] = shape.getSize();
        return {
            width - padding.left - padding.right, 
            height - padding.top - padding.bottom
        };
    }

    void Border::setSize(const Vec2f& size, bool withRedraw)
    {
        shape.setSize({size.x, size.y});
        if (child) {
            child->setBoundSize(getChildBoundSize());
        }
        if (withRedraw) {
            Primitive::redraw();
        }
    }

    Vec2f Border::getShrinkedSize() const
    {
        if(child) {
            auto [width, height] = child->getShrinkedSize();
            return {width + padding.right + padding.left, height + padding.bottom + padding.top};
        } else {
            return {padding.right + padding.left, padding.bottom + padding.top};
        }
    }

    const sf::Color& Border::getBorderColor() const
    {
        return shape.getFillColor();
    }

    float Border::getBorderRadius(float radius) const
    {
        return shape.getRadius();
    }

    void Border::setBorderColor(const sf::Color& color)
    {
        shape.setFillColor(color);
        Primitive::redraw();
    }

    void Border::setBorderRadius(float radius)
    {
        shape.setRadius(radius);
        Primitive::redraw();
    }


    void Border::setOutlineThickness(float thickness)
    {
        shape.setOutlineThickness(thickness);
        Primitive::redraw();
    }

    void Border::setOutlineColor(const sf::Color& color)
    {
        shape.setOutlineColor(color);
        Primitive::redraw();
    }

}
