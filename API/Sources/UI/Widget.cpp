#include "NII/UI/Widget.hpp"

#include <SFML/Graphics/Sprite.hpp>

namespace nii::ui
{
    void Widget::redraw()
    {
        renderer.clear();
        root->draw(renderer, sf::RenderStates::Default);
        renderer.display();

        needRedraw = false;
    }

    void Widget::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (needRedraw) {
            const_cast<Widget*>(this)->redraw();
        }

        target.draw(sf::Sprite(renderer.getTexture()), states);
    }



    void Widget::setSize(const Vec2f& size, bool withRedraw)
    {
        renderer.create(size.x, size.y);
        if (withRedraw) {
            redraw();
        }
    }

    Vec2f Widget::getShrinkedSize() const
    {
        auto [width, height] = renderer.getSize();
        return {static_cast<float>(width), static_cast<float>(height)};
    }

    void Widget::setRoot(Primitive* newRoot)
    {
        root = newRoot;
        auto [width, height] = renderer.getSize();
        root->setBoundSize({static_cast<float>(width), static_cast<float>(height)});
        root->setParent(this);
        // redraw();
    }


}