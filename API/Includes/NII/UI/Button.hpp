#pragma once

#include "Border.hpp"
#include "Text.hpp"
#include "Image.hpp"


namespace nii::ui
{
    class Button: public Border
    {
    public:
        inline static std::string GetDefaultName() { return "button"; }
        struct Style
        {
            IndentsFloat padding = {10.f, 10.f, 10.f, 10.f};
            sf::Color color = {200, 200, 200, 200};
            sf::Texture* texture = nullptr;
        };

        inline Button(const std::string& name = {}, const sf::String& buttonText = {L"press"})
            : Border(name.size() ? name : naming::GenerateName<Button>())
            , normalStyle{{10.f, 10.f, 10.f, 10.f}, {200, 200, 200, 200},                nullptr}
            , hoverStyle{{10.f, 10.f, 10.f, 10.f},  {200 - 20, 200 - 20, 200 - 20, 255}, nullptr}
            , pressStyle{{12.f, 8.f, 12.f, 8.f},    {200 - 50, 200 - 50, 200 - 50, 255}, nullptr}
            , currentStyle{}
        {
            auto text = new Text(buttonText);
            text->setFillColor({0, 0, 0});
            setChild(text);

            // auto l = new List;
            // l->setPlane(PlaneHorizontal);
            // sf::Texture* textureTrash = new sf::Texture;
            // textureTrash->loadFromFile("delete-white-24.png");
            // auto img = new Image;
            // img->setTexture(*textureTrash);
            // img->setFillColor({100, 70, 70});
            // img->setViewSize({32.f, 32.f});
            // l->addChild(img);
            // l->addChild(text);
            // l->setShrinkToFit(true);
            // setChild(l);

               Primitive::redraw();

        }

        Button(const Button&) = delete;
        Button(Button&&) = delete;

        inline virtual ~Button()
        {

        }

        inline void redraw()
        {
            if (pressed) {
                currentStyle = pressStyle;
            } else {
                if (hovered) {
                    currentStyle = hoverStyle;
                } else {
                    currentStyle = normalStyle;
                }
            }


            padding = currentStyle.padding;
            shape.setFillColor(currentStyle.color);
            shape.setTexture(currentStyle.texture);

            Border::redraw();
        }

        inline core::Primitive* intersectNext(Vec2f pos)
        {
            return nullptr;
        }

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override
        {
            if (needRedraw) {
                const_cast<Button*>(this)->redraw();
            }
            if (outlined) {
                shape.setOutlineColor({255, 128, 0, 220});
                shape.setOutlineThickness(4);
            } else {
                 shape.setOutlineColor({255, 166, 77, 0});
                shape.setOutlineThickness(0);
            }
            target.draw(shape, states);


            if (child) {
                states.transform *= shape.getTransform();
                states.transform.translate(padding.left, padding.top);

                target.draw(child, states);
            }
        }

        

        inline void press() override
        {
            redraw();
            Primitive::redraw();
        }

        inline void release() override
        {
            redraw();
            Primitive::redraw();
        }

        inline void hover() override
        {
            redraw();
            Primitive::redraw();
        }

        inline void unhover() override
        {
            redraw();
            Primitive::redraw();
        }


        inline void setNormalStylePadding(IndentsFloat padding)
        {
            normalStyle.padding = padding;
            Primitive::redraw();
        }

        inline void setNormalStyleColor(sf::Color color)
        {
            normalStyle.color = color;
            Primitive::redraw();
        }

        inline void setNormalStyle(Style style)
        {
            normalStyle = style;
            Primitive::redraw();
        }

        inline Style getNormalStyle() const { return normalStyle; }



        inline void setHoverStylePadding(IndentsFloat padding)
        {
            hoverStyle.padding = padding;
            Primitive::redraw();
        }

        inline void setHoverStyleColor(sf::Color color)
        {
            hoverStyle.color = color;
            Primitive::redraw();
        }

        inline void setHoverStyle(Style style)
        {
            hoverStyle = style;
            Primitive::redraw();
        }

        inline Style getHoverStyle() const { return hoverStyle; }



        inline void setPressStylePadding(IndentsFloat padding)
        {
            pressStyle.padding = padding;
            Primitive::redraw();
        }

        inline void setPressStyleColor(sf::Color color)
        {
            pressStyle.color = color;
            Primitive::redraw();
        }

        inline void setPressStyle(Style style)
        {
            pressStyle = style;
            Primitive::redraw();
        }

        inline Style getPressStyle() const { return pressStyle; }


        inline void serialize(nii::json::entities::wrapper wrapper) override
        {
            wrapper["name"] = name;
            wrapper["type"] = "button";

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

                auto style = details["styles"];
                style["normal"]["paddings"]["top"] = normalStyle.padding.top;
                style["normal"]["paddings"]["bottom"] = normalStyle.padding.bottom;
                style["normal"]["paddings"]["left"] = normalStyle.padding.left;
                style["normal"]["paddings"]["right"] = normalStyle.padding.right;
                style["normal"]["color"]["r"] = normalStyle.color.r;
                style["normal"]["color"]["g"] = normalStyle.color.g;
                style["normal"]["color"]["b"] = normalStyle.color.b;
                style["normal"]["color"]["a"] = normalStyle.color.a;

                style["hover"]["paddings"]["top"] = hoverStyle.padding.top;
                style["hover"]["paddings"]["bottom"] = hoverStyle.padding.bottom;
                style["hover"]["paddings"]["left"] = hoverStyle.padding.left;
                style["hover"]["paddings"]["right"] = hoverStyle.padding.right;
                style["hover"]["color"]["r"] = hoverStyle.color.r;
                style["hover"]["color"]["g"] = hoverStyle.color.g;
                style["hover"]["color"]["b"] = hoverStyle.color.b;
                style["hover"]["color"]["a"] = hoverStyle.color.a;

                style["press"]["paddings"]["top"] = pressStyle.padding.top;
                style["press"]["paddings"]["bottom"] = pressStyle.padding.bottom;
                style["press"]["paddings"]["left"] = pressStyle.padding.left;
                style["press"]["paddings"]["right"] = pressStyle.padding.right;
                style["press"]["color"]["r"] = pressStyle.color.r;
                style["press"]["color"]["g"] = pressStyle.color.g;
                style["press"]["color"]["b"] = pressStyle.color.b;
                style["press"]["color"]["a"] = pressStyle.color.a;

            child.serialize(wrapper["child"]);
        }
        
        inline core::Primitive* deserialize(nii::json::entities::wrapper wrapper) override
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

                auto style = details["styles"];
                normalStyle.padding.top = style["normal"]["paddings"]["top"]->number();
                normalStyle.padding.bottom = style["normal"]["paddings"]["bottom"]->number();
                normalStyle.padding.left = style["normal"]["paddings"]["left"]->number();
                normalStyle.padding.right = style["normal"]["paddings"]["right"]->number();
                normalStyle.color.r = style["normal"]["color"]["r"]->number();
                normalStyle.color.g = style["normal"]["color"]["g"]->number();
                normalStyle.color.b = style["normal"]["color"]["b"]->number();
                normalStyle.color.a = style["normal"]["color"]["a"]->number();

                hoverStyle.padding.top = style["hover"]["paddings"]["top"]->number();
                hoverStyle.padding.bottom = style["hover"]["paddings"]["bottom"]->number();
                hoverStyle.padding.left = style["hover"]["paddings"]["left"]->number();
                hoverStyle.padding.right = style["hover"]["paddings"]["right"]->number();
                hoverStyle.color.r = style["hover"]["color"]["r"]->number();
                hoverStyle.color.g = style["hover"]["color"]["g"]->number();
                hoverStyle.color.b = style["hover"]["color"]["b"]->number();
                hoverStyle.color.a = style["hover"]["color"]["a"]->number();

                pressStyle.padding.top = style["press"]["paddings"]["top"]->number();
                pressStyle.padding.bottom = style["press"]["paddings"]["bottom"]->number();
                pressStyle.padding.left = style["press"]["paddings"]["left"]->number();
                pressStyle.padding.right = style["press"]["paddings"]["right"]->number();
                pressStyle.color.r = style["press"]["color"]["r"]->number();
                pressStyle.color.g = style["press"]["color"]["g"]->number();
                pressStyle.color.b = style["press"]["color"]["b"]->number();
                pressStyle.color.a = style["press"]["color"]["a"]->number();

                redraw();
                

            if (wrapper["child"].valid() && wrapper["child"]->isObject()) {
                auto primitive = serialization::createPrimitiveFromType(wrapper["child"]["type"]);
                primitive->deserialize(wrapper["child"]);
                setChild(std::move(primitive));
            }
            Primitive::redraw();
            return this;
        }


        Style normalStyle;
        Style hoverStyle;
        Style pressStyle;

        Style currentStyle;
        
    };
}