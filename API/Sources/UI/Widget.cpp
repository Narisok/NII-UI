#include "NII/UI/Widget.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <cmath>

namespace nii::ui
{
    void Widget::redraw()
    {
        renderer.clear();
        
        if (root) {
            root->draw(renderer, sf::RenderStates::Default);
        }
        renderer.display();

        needRedraw = false;
    }

    core::Primitive* Widget::intersectNext(Vec2f pos)
    {
        if (root) {
            return root->intersect(pos);
        }
        return nullptr;
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
        renderer.create(ceil(size.x), ceil(size.y));
        if (root) {
            root->setBoundSize({size.x, size.y});
        }
        if (withRedraw) {
            Primitive::redraw();
        }
    }

    Vec2f Widget::getShrinkedSize() const
    {
        auto [width, height] = size; //renderer.getSize();
        return {static_cast<float>(width), static_cast<float>(height)};
    }

    void Widget::setRoot(Primitive* newRoot)
    {
        root = newRoot;
        auto [width, height] = size;// renderer.getSize();
        root->setBoundSize({static_cast<float>(width), static_cast<float>(height)});
        root->setParent(this);
        // redraw();
    }


}