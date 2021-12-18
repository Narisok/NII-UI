#include "NII/UI/Canvas.hpp"

#include <iostream>
#include <algorithm>
#include <cmath>

using std::cout;
using std::endl;


namespace nii::ui
{
     Canvas::Canvas()
        : Primitive()
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

    void Canvas::redraw()
    {
        auto states = sf::RenderStates::Default;

        cout << "REDRAW" << endl;

        renderer.clear(sf::Color(0,0,0,0));
        sf::RectangleShape s(getSize());
        s.setFillColor({255, 0, 0, 100});
        
        renderer.draw(s, states);

        for (auto& slot : slots) {
            renderer.draw(slot, states);
        }


        // auto tmp = renderer.getSize();
        // float rx = tmp.x;
        // float ry = tmp.y;

        // auto [bx, by] = getSize();
        // bx;
        // by;
        // auto childSize = child.getSize();
        // childSize.x = bx > childSize.x ? bx : childSize.x;
        // childSize.y = by > childSize.y ? by : childSize.y;
        // center.x = std::clamp(center.x, bx / 2.f, childSize.x - bx / 2.f);
        // center.y = std::clamp(center.y, by / 2.f, childSize.y - by / 2.f);


        // auto view = sf::View(center, {rx*(bx/rx), ry*(by/ry)});
        // view.setViewport({0.f, 0.f, bx/rx, by/ry});
        // renderer.setView(view);

        // renderer.draw(child, states);


        // bool needHor = (int)(bx / 2.f) !=  (int) (childSize.x - bx / 2.f);
        // bool needVer = (int)(by / 2.f) !=  (int) (childSize.y - by / 2.f);
        // if (needVer) {
        //     sf::RectangleShape s({10.f, needHor ? by-10.f : by});
        //     s.setPosition(center.x + bx/2.f - 10.f, center.y - by/2.f);
        //     s.setFillColor({50, 50, 50, 100});
        //     renderer.draw(s, states);
        //     s.setFillColor({50, 50, 50, 155});
        //     float hs =  by*(by/childSize.y);
        //     s.setSize({10.f, hs});
        //     auto ws = center.y / childSize.y;
        //     s.setPosition(center.x + bx/2.f - 10.f, (center.y - hs/2.f) - (by*(1.f-ws)) + by/2.f );
        //     renderer.draw(s, states);
        // }

        // if (needHor) {
        //     sf::RectangleShape s({bx, 10.f});
        //     s.setPosition(center.x - bx/2.f, center.y + by/2.f -10.f);
        //     s.setFillColor({50, 50, 50, 100});
        //     renderer.draw(s, states);
        //     s.setFillColor({50, 50, 50, 155});
        //     float ws =  bx*(bx/childSize.x);
        //     s.setSize({ws, 10.f});
        //     auto hs = center.x / childSize.x;
        //     s.setPosition((center.x - ws/2.f) - (bx*(1.f-hs)) + bx/2.f , center.y + by/2.f - 10.f );
        //     renderer.draw(s, states);
        // }


        renderer.display();


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
        target.draw(sf::Sprite(renderer.getTexture()), states);
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
        renderer.create(std::ceil(size.x), std::ceil(size.y));
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
