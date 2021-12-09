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
        , shape({150, 100})
    { 
        padding = {10, 10, 10, 10};
        cout << "Border ()" << endl; 
    }

    Border::Border(const Border& other)
        : Primitive()
        , child(nullptr)
        , shape({150, 100})
    { cout << "Border cp" << endl; }

    Border::Border(Border&& other)
        : Primitive()
        , child(nullptr)
        , shape({150, 100})
    { cout << "Border mv" << endl; }

    Border::~Border()
    { cout << "Border ~~" << endl; }

    void Border::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(shape, states);
        if(child) {
            states.transform *= shape.getTransform();
            target.draw(*child, states);
        }
    }

    void Border::setBound(const IndentsFloat& bound)
    {
        shape.setPosition(bound.left, bound.top);
        shape.setSize({bound.right - bound.left, bound.bottom - bound.top});

        if (child) {
            child->setBound({
                bound.top + padding.top,
                bound.bottom - padding.bottom,
                bound.left + padding.left,
                bound.right - padding.right,
            });
        }
    }

    IndentsFloat Border::getBound() const
    {
        return {
            shape.getPosition().x, 
            shape.getPosition().y, 
            shape.getSize().x + shape.getPosition().x, 
            shape.getSize().y + shape.getPosition().y
        };
    }

}
