#include "NII/UI/Widget.hpp"

#include <SFML/Graphics/Sprite.hpp>

namespace nii::ui
{
    void Widget::redraw()
    {
        renderer.clear();
        root->draw(renderer, sf::RenderStates::Default);
        renderer.display();

        Primitive::redraw();
    }

    void Widget::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(sf::Sprite(renderer.getTexture()), states);
    }



     void Widget::setSize(const Vec2f& size)
    {
        renderer.create(size.x, size.y);
        redraw();
    }

    Vec2f Widget::getShrinkedSize() const
    {
        auto [width, height] = renderer.getSize();
        return {width, height};
    }

    void Widget::setRoot(Primitive* newRoot)
    {
        root = newRoot;
        auto [width, height] = renderer.getSize();
        root->setBoundSize({width, height});
        root->setParent(this);
        // redraw();
    }


}