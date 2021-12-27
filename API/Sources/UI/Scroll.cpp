#include "NII/UI/Scroll.hpp"

#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;


namespace nii::ui
{
     Scroll::Scroll(const std::string& name)
        : Primitive(name.size() ? name : naming::GenerateName<Scroll>())
        , size({200,200})
        , center({50, 50})
        , renderer()
        , child()
        , plane(PlaneVertical)
    {
        renderer.create(256, 256);
        renderer.setSmooth(true);
        // setSize({size.x, size.y});
        setViewSize({200.f, 200.f});
    }

    Scroll::~Scroll()
    {
    }

    core::Primitive* Scroll::intersectNext(Vec2f pos)
    {
        if (child) {
            auto tmp = renderer.getSize();
            float rx = tmp.x;
            float ry = tmp.y;

            auto [bx, by] = getSize();
            bx;
            by;
            auto childSize = child.getSize();
            childSize.x = bx > childSize.x ? bx : childSize.x;
            childSize.y = by > childSize.y ? by : childSize.y;
            center.x = std::clamp(center.x, bx / 2.f, childSize.x - bx / 2.f);
            center.y = std::clamp(center.y, by / 2.f, childSize.y - by / 2.f);

            return child.intersect({pos.x+(center.x - bx/2.f), pos.y+(center.y - by/2.f)});
        }

        return nullptr;
    }

    core::Primitive* Scroll::intersectNextWith(Vec2f& pos)
    {
        if (child) {
            auto tmp = renderer.getSize();
            float rx = tmp.x;
            float ry = tmp.y;

            auto [bx, by] = getSize();
            bx;
            by;
            auto childSize = child.getSize();
            childSize.x = bx > childSize.x ? bx : childSize.x;
            childSize.y = by > childSize.y ? by : childSize.y;
            center.x = std::clamp(center.x, bx / 2.f, childSize.x - bx / 2.f);
            center.y = std::clamp(center.y, by / 2.f, childSize.y - by / 2.f);

            pos.x += (center.x - bx/2.f);
            pos.y += (center.y - by/2.f);
            return child.intersectWith(pos);
        }

        return nullptr;
    }

    void Scroll::redraw()
    {
        auto states = sf::RenderStates::Default;



        renderer.clear(sf::Color(0,0,0,0));


        auto tmp = renderer.getSize();
        float rx = tmp.x;
        float ry = tmp.y;

        auto [bx, by] = getSize();
        bx;
        by;
        auto childSize = child.getSize();
        childSize.x = bx > childSize.x ? bx : childSize.x;
        childSize.y = by > childSize.y ? by : childSize.y;
        center.x = std::clamp(center.x, bx / 2.f, childSize.x - bx / 2.f);
        center.y = std::clamp(center.y, by / 2.f, childSize.y - by / 2.f);


        auto view = sf::View(center, {rx*(bx/rx), ry*(by/ry)});
        view.setViewport({0.f, 0.f, bx/rx, by/ry});
        renderer.setView(view);

        renderer.draw(child, states);


        bool needHor = (int)(bx / 2.f) !=  (int) (childSize.x - bx / 2.f);
        bool needVer = (int)(by / 2.f) !=  (int) (childSize.y - by / 2.f);
        if (needVer) {
            sf::RectangleShape s({10.f, needHor ? by-10.f : by});
            s.setPosition(center.x + bx/2.f - 10.f, center.y - by/2.f);
            s.setFillColor({50, 50, 50, 100});
            renderer.draw(s, states);
            s.setFillColor({50, 50, 50, 155});
            float hs =  by*(by/childSize.y);
            s.setSize({10.f, hs});
            auto ws = center.y / childSize.y;
            s.setPosition(center.x + bx/2.f - 10.f, (center.y - hs/2.f) - (by*(1.f-ws)) + by/2.f );
            renderer.draw(s, states);
        }

        if (needHor) {
            sf::RectangleShape s({bx, 10.f});
            s.setPosition(center.x - bx/2.f, center.y + by/2.f -10.f);
            s.setFillColor({50, 50, 50, 100});
            renderer.draw(s, states);
            s.setFillColor({50, 50, 50, 155});
            float ws =  bx*(bx/childSize.x);
            s.setSize({ws, 10.f});
            auto hs = center.x / childSize.x;
            s.setPosition((center.x - ws/2.f) - (bx*(1.f-hs)) + bx/2.f , center.y + by/2.f - 10.f );
            renderer.draw(s, states);
        }


        renderer.display();


        needRedraw = false;
    }

    void Scroll::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (outlined) {
            sf::RectangleShape shape(getSize());
            shape.setFillColor({0,250,0,0});
            shape.setOutlineColor({255, 128, 0, 220});
            shape.setOutlineThickness(4);
            target.draw(shape, states);
        } else {
        }
        

        if (needRedraw) {
            const_cast<Scroll*>(this)->redraw();
        }
        target.draw(sf::Sprite(renderer.getTexture()), states);
    }

    void Scroll::setSize(const Vec2f& newSize, bool withRedraw)
    {
        restartRenderer(newSize);
        // child.setBoundSize(child.getShrinkedSize());

        if(withRedraw) {
            Primitive::redraw();
        }
    }

    void Scroll::restartRenderer(Vec2f size)
    {
        auto [width, height] = renderer.getSize();
        if(size.x > width || size.y > height) {
            while (width < size.x) {
                width += 64;
            }
            while (height < size.y) {
                height += 64;
            }
            renderer.create(width, height);
        }
    }


    void Scroll::setChild(Primitive* newChild)
    {
        setChild(std::unique_ptr<core::Primitive>(newChild));
    }

    void Scroll::setChild(std::unique_ptr<core::Primitive>&& newChild)
    {
        newChild->setShrinkToFit(true);
        child.setChild(this, std::move(newChild), newChild->getShrinkedSize());
        Primitive::redraw();
    }


    void Scroll::setViewSize(const Vec2f& newSize)
    {
        size = newSize;
        center.x = (size.x /* - 10 */) / 2.f;
        center.y = (size.y /* - 10 */) / 2.f;
        setSize(size);
        setShrinkToFit(true);
    }

    void Scroll::move(Vec2f pos)
    {
        auto mySize = getSize();
        auto childSize = child.getSize();
        childSize.x = mySize.x > childSize.x ? mySize.x : childSize.x;
        childSize.y = mySize.y > childSize.y ? mySize.y : childSize.y;
        center.x = std::clamp(center.x + pos.x, mySize.x / 2.f, childSize.x - mySize.x / 2.f);
        center.y = std::clamp(center.y + pos.y, mySize.y / 2.f, childSize.y - mySize.y / 2.f);
        Primitive::redraw();
    }

    void Scroll::resetViewSize()
    {
        size   = {40.f, 40.f};
        auto newSize = shrinkToFit ? size : boundSize;
        center = {newSize.x / 2.f, newSize.y / 2.f};

        setSize(newSize);
    }


    Vec2f Scroll::getShrinkedSize() const
    {
        return size;
    }

    void Scroll::scroll(float delta)
    {
        move({0.f, 20.f * -delta});
    }

    void Scroll::scrollHorizontal(float delta)
    {
        move({20.f * -delta, 0.f});
    }

    core::Primitive* Scroll::findByName(const std::string& name)
    {
        if (this->name == name) {
            return this;
        }
        return child.findByName(name);
    }

    void Scroll::serialize(nii::json::entities::wrapper wrapper)
    {
        wrapper["name"] = name;
        wrapper["type"] = "scroll";

        auto details = wrapper["details"];
            details["shrink_to_fit"] = shrinkToFit;
            details["child_align"] = (int)child.align;
            details["child_valign"] = (int)child.valign;
            details["size"]["x"] = size.x;
            details["size"]["y"] = size.y;
            details["plane"] = (int) plane;

        child.serialize(wrapper["child"]);
    }

    core::Primitive* Scroll::deserialize(nii::json::entities::wrapper wrapper)
    {
        name = wrapper["name"]->string();

        auto details = wrapper["details"];
            shrinkToFit = details["shrink_to_fit"]->boolean();
            size.x = details["size"]["x"]->number();
            size.y = details["size"]["y"]->number();

            Align align = (Align)details["child_align"]->number();
            child.setAlign(align);
            VAlign valign = (VAlign)details["child_valign"]->number();
            child.setVAlign(valign);

            this->plane = (Plane)details["plane"]->number();
            

        if (wrapper["child"].valid() && wrapper["child"]->isObject()) {
            auto primitive = serialization::createPrimitiveFromType(wrapper["child"]["type"]);
            primitive->deserialize(wrapper["child"]);
            setChild(std::move(primitive));
        }
        Primitive::redraw();
        return this;
    }

}
