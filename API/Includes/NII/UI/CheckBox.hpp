#pragma once

#include "Border.hpp"
#include "Text.hpp"
#include "Image.hpp"


namespace nii::ui
{
    class CheckBox: public Border
    {
    public:
        struct Style
        {
            sf::Color color;
            sf::Color insideColor;
            sf::Color imageColor;
            sf::Texture* texture;
        };

        inline CheckBox()
            : Border()
            , normalStyle{{70, 70, 70, 255}, {200, 200, 200, 255}, {0, 0, 0, 0}, nullptr}
            , hoverStyle{{30, 30, 30, 255}, {200, 200, 200, 255}, {0, 0, 0, 0}, nullptr}
            , checkedStyle{{100, 100, 100, 255}, {255, 133, 51}, {200, 200, 200, 255}, nullptr}
            , checkedHoverStyle{{50, 50, 50, 255}, {255-20, 133-20, 51-20}, {200, 200, 200, 255}, nullptr}
            , checkedEvent()
            , imageShape(nullptr)
            , checked(false)
        {
            padding = IndentsFloat{2.5f};
            setBorderRadius(4.3f);
            imageShape = new Image;
            borderShape = new Border;
            borderShape->padding = IndentsFloat{0.f};
            borderShape->setBorderRadius(0.f);
            borderShape->setChild(imageShape);
            setChild(borderShape);
            setShrinkToFit(true);

            sf::Texture* textureTrash = new sf::Texture;
            textureTrash->loadFromFile("done-white-26.png");
            textureTrash->setSmooth(true);
            checkedStyle.texture = textureTrash;
            checkedHoverStyle.texture = textureTrash;
            // setBorderRadius(44.f/2.f);
            redraw();
        }

        inline virtual ~CheckBox()
        {

        }

        inline void redraw()
        {
            Style currentStyle;
            if (checked) {
                if (hovered) {
                    currentStyle = checkedHoverStyle;
                } else {
                    currentStyle = checkedStyle;
                }
            } else {
                if (hovered) {
                    currentStyle = hoverStyle;
                } else {
                    currentStyle = normalStyle;
                }
            }

            if (currentStyle.texture) {
                imageShape->setTexture(*currentStyle.texture, true);
            } else {
                imageShape->setUseTexture(false);   
            }
            shape.setFillColor(currentStyle.color);
            borderShape->shape.setFillColor(currentStyle.insideColor);

            imageShape->setFillColor(currentStyle.imageColor);
            
            imageShape->setViewSize({13.f, 13.f});
            imageShape->setShrinkToFit(true);

            Border::redraw();
        }

        inline core::Primitive* intersectNext(Vec2f pos)
        {
            return nullptr;
        }

        void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            if (needRedraw) {
                const_cast<CheckBox*>(this)->redraw();
            }
            target.draw(shape, states);

            if (child) {
                states.transform *= shape.getTransform();
                states.transform.translate(padding.left, padding.top);

                target.draw(child, states);
            }
        }

        inline void setIsChecked(bool check)
        {
            checked = check;
            Primitive::redraw();
        }

        inline void click() override
        {
            checked = !checked;

            checkedEvent.call(checked);
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

        inline void onCheck(nii::util::Event<bool>::Function calleable)
        {
            checkedEvent.addListener(std::move(calleable));
        }


        Style normalStyle;
        Style checkedStyle;
        Style hoverStyle;
        Style checkedHoverStyle;
        
        nii::util::Event<bool> checkedEvent;
        Border* borderShape;
        Image* imageShape;

        bool checked;
        
    };
}