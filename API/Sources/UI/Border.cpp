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
        , shape({100, 100})
    { 
        padding = {10, 10, 10, 10};
        cout << "Border ()" << endl; 
    }

    Border::Border(const Border& other)
        : Primitive()
        , child(nullptr)
        , shape({100, 100})
    { cout << "Border cp" << endl; }

    Border::Border(Border&& other)
        : Primitive()
        , child(nullptr)
        , shape({100, 100})
    { cout << "Border mv" << endl; }

    Border::~Border()
    { cout << "Border ~~" << endl; }

    void Border::setChild(Primitive* newChild)
    {
        child = newChild;
        child->setBoundSize(getChildSize());
        child->setParent(this);
    }

    void Border::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(shape, states);
        if(child) {
            states.transform *= shape.getTransform();
            states.transform.translate(padding.left, padding.top);
            target.draw(*child, states);
        }
    }

    Vec2f Border::getChildSize() const
    {
        auto [width, height] = shape.getSize();
        return {
            width - padding.left - padding.right, 
            height - padding.top - padding.bottom
        };
    }

    void Border::setSize(const Vec2f& size)
    {
        shape.setSize({size.x, size.y});
        if (child) {
            child->setBoundSize(getChildSize());
        }
        redraw();
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

}
