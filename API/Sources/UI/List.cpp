#include "NII/UI/List.hpp"

#include <SFML/Graphics.hpp>

namespace nii::ui
{
    List::List(const std::string& name)
        : Primitive(name.size() ? name : naming::GenerateName<List>())
        , children()
        , plane(PlaneVertical)
    {}

    List::~List()
    {}

    core::Primitive* List::intersectNext(Vec2f pos)
    {
        bool vr = plane == PlaneVertical;
        for (auto& a : children) {
            auto [width, height] = a.getSize();
            if (pos.x <= width && pos.y <= height) {
                return a.intersect(pos);
            } else {
                if (vr) {
                    pos.y -= height;
                } else {
                    pos.x -= width;
                }
            }
        }
        return nullptr;
    }

    void List::redraw()
    {
        if (shrinkToFit) {
            setSize(getShrinkedSize(), false);
        } else {
            setSize(getBoundSize(), false);
        }

        needRedraw = false;
    }

    void List::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // sf::RectangleShape shape(getSize());
        // shape.setFillColor({0,0,0,50});
        // shape.setOutlineColor({255,0,0,100});
        // shape.setOutlineThickness(1);
        // target.draw(shape, states);

        if (needRedraw) {
            const_cast<List*>(this)->redraw();
        }

        bool vr = plane == PlaneVertical;
        for (auto& a : children) {
            auto [width, height] = a.getSize();
            target.draw(a, states);
            states.transform.translate(vr ? 0.f : width, vr ? height : 0.f);
        }

        
    }

    void List::setSize(const Vec2f& size, bool withRedraw)
    {
        bool vr = plane == PlaneVertical;
        for (auto& a : children) {
            auto [width, height] = a.getShrinkedSize();
            a.setBoundSize({vr ? size.x : width, vr ? height : size.y});
        }

        if (withRedraw) {
            Primitive::redraw();
        }
    }

    Vec2f List::getShrinkedSize() const
    {
        float maxWidth = 0;
        float maxHeight = 0;
        bool vr = plane == PlaneVertical;
        for (auto& a : children) {
            auto [width, height] = a.getShrinkedSize();
            if (vr) {
                if (width > maxWidth) {
                    maxWidth = width;
                }
                maxHeight += height;
            } else {
                if (maxHeight < height) {
                    maxHeight = height;
                }
                maxWidth += width;
            }
        }
        return {maxWidth, maxHeight};
    }

    void List::addChild(core::Primitive* child)
    {
        addChild(std::unique_ptr<core::Primitive>(child));
    }

    void List::addChild(std::unique_ptr<core::Primitive>&& child)
    {
        auto [width, height] = getSize();
        auto [cWidth, cHeight] = child->getShrinkedSize();
        bool vr = plane == PlaneVertical;
        children.emplace_back(this, std::move(child), Vec2f{vr ? width : cWidth, vr ? cHeight : height});
    }

    // void List::removeChild(size_t idx)
    // {

    // }
    
    // Primitive* List::fetchChild(size_t idx)
    // {

    // }

    void List::setPlane(Plane newPlane)
    {
        plane = newPlane;

        Primitive::redraw();
    }


    core::Primitive* List::findByName(const std::string& name)
    {
        if (this->name == name) {
            return this;
        }
        for (auto &a : children) {
            auto res = a.findByName(name);
            if (res) {
                return res;
            }
        }
        return nullptr;
    }


    void List::serialize(nii::json::entities::wrapper wrapper)
    {
        wrapper["name"] = name;
        wrapper["type"] = "list";

        auto details = wrapper["details"];
            details["shrink_to_fit"] = shrinkToFit;
            details["plane"] = (int)plane;

        auto wrapperChildren = wrapper["children"];
        int idx = 0;
        for (auto &a : children) {
            a.serialize(wrapperChildren[idx++]);
        }
    }

    core::Primitive* List::deserialize(nii::json::entities::wrapper wrapper)
    {
        name = wrapper["name"]->string();

        auto details = wrapper["details"];
            shrinkToFit = details["shrink_to_fit"]->boolean();
            plane = (Plane)details["plane"]->number();

        if (wrapper["children"].valid() && wrapper["children"]->isArray()) {
            for (auto wrap : wrapper["children"]->array()) {
                auto primitive = serialization::createPrimitiveFromType(wrap["type"]);
                primitive->deserialize(wrap);
                addChild(std::move(primitive));
            }
        }
        Primitive::redraw();
        return this;
    }



}
