#include "NII/UI/Canvas.hpp"

#include <iostream>
#include <algorithm>
#include <cmath>

using std::cout;
using std::endl;


namespace nii::ui
{
     Canvas::Canvas(const std::string& name)
        : Primitive(name.size() ? name : naming::GenerateName<Canvas>())
        , renderer()
        , slots()
        , size({64.f, 64.f})
    {
        renderer.create(64, 64);
        setSize({64.f, 64.f});
    }

    Canvas::~Canvas()
    {
    }

    core::Primitive* Canvas::intersectNext(Vec2f pos)
    {
        for (auto& slot : slots) {
            auto [width, height] = slot.getSize();
            auto [x, y] = slot.getPosition();
            if (sf::FloatRect(x, y, width, height).contains(pos.x, pos.y)) {
                return slot.intersect({pos.x - x, pos.y - y});
            }
        }

        return nullptr;
    }

    void Canvas::redraw()
    {
        auto states = sf::RenderStates::Default;

        // renderer.clear(sf::Color(0,0,0,0));

        // for (auto& slot : slots) {
        //     renderer.draw(slot, states);
        // }



        // renderer.display();


        needRedraw = false;
    }

    void Canvas::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {

        // sf::RectangleShape shape(getSize());
        // shape.setFillColor({0,250,0,50});
        // shape.setOutlineColor({0,0,250,100});
        // shape.setOutlineThickness(5);
        // target.draw(shape, states);

        if (needRedraw) {
            const_cast<Canvas*>(this)->redraw();
        }
        // target.draw(sf::Sprite(renderer.getTexture()), states);
        for (auto& slot : slots) {
            renderer.draw(slot, states);
        }
    }

    void Canvas::setSize(const Vec2f& newSize, bool withRedraw)
    {
        restartRenderer(newSize);

        if(withRedraw) {
            Primitive::redraw();
        }
    }

    void Canvas::restartRenderer(Vec2f size)
    {
        // renderer.create(std::ceil(size.x), std::ceil(size.y));
    }



    void Canvas::setViewSize(const Vec2f& newSize)
    {
        size = newSize;
        setSize(newSize);
    }


    Vec2f Canvas::getShrinkedSize() const
    {
        // auto [width, height] = renderer.getSize();
        // return {static_cast<float>(width), static_cast<float>(height)};
        return size;
    }

    void Canvas::addChild(Primitive* primitive, Vec2f size, Vec2f position)
    {
        slots.emplace_back();
        slots.back().setChild(this, primitive, size, position);
    }
}
