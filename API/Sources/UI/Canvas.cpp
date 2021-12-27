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

    core::Primitive* Canvas::intersectNextWith(Vec2f& pos)
    {
        for (auto& slot : slots) {
            auto [width, height] = slot.getSize();
            auto [x, y] = slot.getPosition();
            if (sf::FloatRect(x, y, width, height).contains(pos.x, pos.y)) {
                pos.x -= x;
                pos.y -= y;
                return slot.intersectWith(pos);
            }
        }

        return nullptr;
    }

    void Canvas::redraw()
    {
        // auto states = sf::RenderStates::Default;

        // renderer.clear(sf::Color(0,0,0,0));

        // for (auto& slot : slots) {
        //     renderer.draw(slot, states);
        // }



        // renderer.display();


        needRedraw = false;
    }

    void Canvas::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (outlined) {
            sf::RectangleShape shape(getSize());
            shape.setFillColor({255, 128, 0,40});
            shape.setOutlineColor({255, 128, 0, 220});
            shape.setOutlineThickness(4);
            target.draw(shape, states);
        }

        if (needRedraw) {
            const_cast<Canvas*>(this)->redraw();
        }
        // target.draw(sf::Sprite(renderer.getTexture()), states);
        for (auto& slot : slots) {
            target.draw(slot, states);
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
        addChild(std::unique_ptr<core::Primitive>(primitive), size, position);
    }

    void Canvas::addChild(std::unique_ptr<core::Primitive> primitive, Vec2f size, Vec2f position)
    {
        slots.emplace_back();
        slots.back().setChild(this, std::move(primitive), size, position);
        Primitive::redraw();
    }

    core::Primitive* Canvas::findByName(const std::string& name)
    {
        if (this->name == name) {
            return this;
        }
        for (auto &a : slots) {
            auto res = a.findByName(name);
            if (res) {
                return res;
            }
        }
        return nullptr;
    }

    void Canvas::serialize(nii::json::entities::wrapper wrapper)
    {
        wrapper["name"] = name;
        wrapper["type"] = "canvas";

        auto details = wrapper["details"];
            details["shrink_to_fit"] = shrinkToFit;
            details["size"]["x"] = size.x;
            details["size"]["y"] = size.y;

        auto wrapperChildren = wrapper["children"];
        int idx = 0;
        for (auto &a : slots) {
            a.serialize(wrapperChildren[idx++]);
        }
    }

    core::Primitive* Canvas::deserialize(nii::json::entities::wrapper wrapper)
    {
        name = wrapper["name"]->string();

        auto details = wrapper["details"];
            shrinkToFit = details["shrink_to_fit"]->boolean();
            size.x = details["size"]["x"]->number();
            size.y = details["size"]["y"]->number();

            

        if (wrapper["children"].valid() && wrapper["children"]->isArray()) {
            for (auto wrap : wrapper["children"]->array()) {
                auto primitive = serialization::createPrimitiveFromType(wrap["type"]);
                primitive->deserialize(wrap);

                Vec2f lSize{100,100};
                Vec2f lPos{100,100};
                lPos.x = wrap["slot"]["position"]["x"]->number();
                lPos.y = wrap["slot"]["position"]["y"]->number();

                lSize.x = wrap["slot"]["size"]["x"]->number();
                lSize.y = wrap["slot"]["size"]["y"]->number();

                
                addChild(std::move(primitive), lSize, lPos);
            }
        }
        Primitive::redraw();
        return this;
    }
}
