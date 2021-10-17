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
    { cout << "Border ()" << endl; }

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
            target.draw(*child, states);
        }
    }
}
