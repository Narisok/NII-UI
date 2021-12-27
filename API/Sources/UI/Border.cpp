#include "NII/UI/Border.hpp"


using std::cout;
using std::endl;


namespace nii::ui
{
     Border::Border(const std::string& name)
        : Primitive(name.size() ? name : naming::GenerateName<Border>())
        , child()
        , shape()
    { 
        padding = {10};
        // printf("Border %s\n", this->name.c_str());
        shape.setFillColor({200, 200, 200, 100});
    }

    Border::~Border()
    { 
        // printf("~Border %s\n", name.c_str());
    }

    core::Primitive* Border::intersectNext(Vec2f pos)
    {
        if (pos.x >= padding.left && pos.y >= padding.top) {
            return child.intersect({pos.x - padding.left, pos.y - padding.top});
        }
        return nullptr;
    }

    core::Primitive* Border::intersectNextWith(Vec2f& pos)
    {
        if (pos.x >= padding.left && pos.y >= padding.top) {
            pos.x -= padding.left;
            pos.y -= padding.top;
            return child.intersectWith(pos);
        }
        return nullptr;
    }

    Vec2f  Border::getLocalPosition(Vec2f pos)
    {
        pos.x + padding.left;
        pos.y + padding.top;
        return Primitive::getLocalPosition(pos);
    }

    void Border::setChild(Primitive* newChild)
    {
        setChild(std::unique_ptr<core::Primitive>(newChild));
    }

    void Border::setChild(std::unique_ptr<core::Primitive>&& newChild)
    {
        child.setChild(this, std::move(newChild), getChildBoundSize());
        Primitive::redraw();
    }

    std::unique_ptr<core::Primitive> Border::extractRoot()
    {
        return child.extractChild();
    }

    void Border::redraw()
    {
        if (shrinkToFit) {
            setSize(getShrinkedSize(), false);
        }

        needRedraw = false;
    }

    void Border::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (needRedraw) {
            const_cast<Border*>(this)->redraw();
        }

        if (outlined) {
            sf::RectangleShape shape(getSize());
            shape.setFillColor({0,250,0,0});
            shape.setOutlineColor({255, 128, 0, 220});
            shape.setOutlineThickness(4);
            target.draw(shape, states);
        } else {
        }

        target.draw(shape, states);
        if (child) {
            states.transform *= shape.getTransform();
            states.transform.translate(padding.left, padding.top);
            target.draw(child, states);
        }
    }

    Vec2f Border::getChildBoundSize() const
    {
        auto [width, height] = shape.getSize();
        return {
            width - padding.left - padding.right, 
            height - padding.top - padding.bottom
        };
    }

    void Border::setSize(const Vec2f& size, bool withRedraw)
    {
        shape.setSize({size.x, size.y});
        // if (child) {
            child.setBoundSize(getChildBoundSize());
        // }
        if (withRedraw) {
            Primitive::redraw();
        }
    }

    Vec2f Border::getShrinkedSize() const
    {
        // if(child) {
            auto [width, height] = child.getShrinkedSize();
            return {width + padding.right + padding.left, height + padding.bottom + padding.top};
        // } else {
        //     return {padding.right + padding.left, padding.bottom + padding.top};
        // }
    }

    const sf::Color& Border::getBorderColor() const
    {
        return shape.getFillColor();
    }

    float Border::getBorderRadius() const
    {
        return shape.getRadius();
    }

    void Border::setBorderColor(const sf::Color& color)
    {
        shape.setFillColor(color);
        Primitive::redraw();
    }

    void Border::setBorderRadius(float radius)
    {
        shape.setRadius(radius);
        Primitive::redraw();
    }


    void Border::setOutlineThickness(float thickness)
    {
        shape.setOutlineThickness(thickness);
        Primitive::redraw();
    }

    void Border::setOutlineColor(const sf::Color& color)
    {
        shape.setOutlineColor(color);
        Primitive::redraw();
    }

    core::Primitive* Border::findByName(const std::string& name)
    {
        if (this->name == name) {
            return this;
        }
        return child.findByName(name);
    }

    void Border::serialize(nii::json::entities::wrapper wrapper)
    {
        wrapper["name"] = name;
        wrapper["type"] = "border";

        auto details = wrapper["details"];
            details["shrink_to_fit"] = shrinkToFit;
            auto [r, g, b, a] = getBorderColor();
            details["border_color"]["r"] = r;
            details["border_color"]["g"] = g;
            details["border_color"]["b"] = b;
            details["border_color"]["a"] = a;
            details["border_radius"] = getBorderRadius();
            details["child_align"] = (int)child.align;
            details["child_valign"] = (int)child.valign;

            details["paddings"]["top"] = padding.top;
            details["paddings"]["bottom"] = padding.bottom;
            details["paddings"]["left"] = padding.left;
            details["paddings"]["right"] = padding.right;

        child.serialize(wrapper["child"]);
    }

    core::Primitive* Border::deserialize(nii::json::entities::wrapper wrapper)
    {
        name = wrapper["name"]->string();

        auto details = wrapper["details"];
            shrinkToFit = details["shrink_to_fit"]->boolean();
            sf::Color borderColor;
            borderColor.r = details["border_color"]["r"]->number();
            borderColor.g = details["border_color"]["g"]->number();
            borderColor.b = details["border_color"]["b"]->number();
            borderColor.a = details["border_color"]["a"]->number();
            setBorderColor(borderColor);
            setBorderRadius(details["border_radius"]->number());

            Align align = (Align)details["child_align"]->number();
            child.setAlign(align);
            VAlign valign = (VAlign)details["child_valign"]->number();
            child.setVAlign(valign);

            padding.top =    details["paddings"]["top"]->number();
            padding.bottom = details["paddings"]["bottom"]->number();
            padding.left =   details["paddings"]["left"]->number();
            padding.right =  details["paddings"]["right"]->number();
            

        if (wrapper["child"].valid() && wrapper["child"]->isObject()) {
            auto primitive = serialization::createPrimitiveFromType(wrapper["child"]["type"]);
            primitive->deserialize(wrapper["child"]);
            setChild(std::move(primitive));
        }
        Primitive::redraw();
        return this;
    }

}
