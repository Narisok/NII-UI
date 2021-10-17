#include <NII/UI/Widget.hpp>

#include <SFML/Graphics/Sprite.hpp>

namespace nii::ui
{
    void Widget::redraw()
    {
        needRedraw = true;
        Primitive::redraw();
    }

    void Widget::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if(needRedraw) {
            renderer.clear();
            root->draw(renderer, sf::RenderStates::Default);
            renderer.display();
            needRedraw = false;
        }

        target.draw(sf::Sprite(renderer.getTexture()), states);
    }

}