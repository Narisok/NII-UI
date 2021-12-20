#pragma once

#include "Border.hpp"
#include "Text.hpp"
#include "Image.hpp"


namespace nii::ui
{
    class Button: public Border
    {
    public:
        struct Style
        {
            IndentsFloat padding;
            sf::Color color;
            sf::Texture* texture;
        };

        inline Button()
            : Border()
            , normalStyle{{10.f, 10.f, 10.f, 10.f}, {200, 200, 200, 200},                nullptr}
            , hoverStyle{{10.f, 10.f, 10.f, 10.f},  {200 - 20, 200 - 20, 200 - 20, 255}, nullptr}
            , pressStyle{{12.f, 8.f, 12.f, 8.f},    {200 - 50, 200 - 50, 200 - 50, 255}, nullptr}
            , currentStyle{}
        {
            auto text = new Text(L"press");
            text->setFillColor({0, 0, 0});
            // setChild(text);
            auto l = new List;
            l->setPlane(PlaneHorizontal);
            sf::Texture* textureTrash = new sf::Texture;
            textureTrash->loadFromFile("delete-white-24.png");
            auto img = new Image;
            img->setTexture(*textureTrash);
            img->setFillColor({100, 70, 70});
            img->setViewSize({32.f, 32.f});
            l->addChild(img);
            l->addChild(text);
            l->setShrinkToFit(true);
            setChild(l);

        }

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

        void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            if (needRedraw) {
                const_cast<Button*>(this)->redraw();
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
            Primitive::redraw();
        }

        inline void release() override
        {
            Primitive::redraw();
        }

        inline void hover() override
        {
            Primitive::redraw();
        }

        inline void unhover() override
        {
            Primitive::redraw();
        }


        Style normalStyle;
        Style hoverStyle;
        Style pressStyle;

        Style currentStyle;
        
    };
}