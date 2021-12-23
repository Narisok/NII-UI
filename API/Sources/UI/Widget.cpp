#include "NII/UI/Widget.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <cmath>

namespace nii::ui
{

    Widget::Widget(Vec2f size)
        : renderer()
        , root()
        , size(size)
    { 
        setBoundSize(size);
        renderer.create(32,32);
        renderer.setSmooth(true);
        // printf("WIDGET %s\n", name.c_str());
    }

    Widget::~Widget()
    {
        // printf("~WIDGET %s\n", name.c_str());
    }


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

    void Widget::setRoot(core::Primitive* newRoot)
    {
        setRoot(std::unique_ptr<core::Primitive>(newRoot));
    }

    void Widget::setRoot(std::unique_ptr<core::Primitive>&& newRoot)
    {
        root = std::move(newRoot);
        auto [width, height] = size;// renderer.getSize();
        root->setBoundSize({static_cast<float>(width), static_cast<float>(height)});
        root->setParent(this);
        // redraw();
    }

    void Widget::removeRoot()
    {
        root.reset();
    }

    std::unique_ptr<core::Primitive> Widget::extractRoot()
    {
        if (root) {
            root->setParent(nullptr);
        }
        return std::move(root);
    }

    core::Primitive* Widget::findByName(const std::string& name)
    {
        if (this->name == name) {
            return this;
        }
        if (root) {
            return root->findByName(name);
        }
        return nullptr;
    }


}