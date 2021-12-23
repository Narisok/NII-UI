#pragma once

#include "Border.hpp"
#include "Text.hpp"

#include <SFML/Graphics/Text.hpp>
#include <cmath>

namespace nii::ui
{
    class TextArea: public Border, public Focusable
    {
    public:

        inline static std::string GetDefaultName() { return "Text_area"; }

        struct Style
        {
            sf::Color baseColor;
            sf::Color baseOutlineColor;
            float     baseOutlineThickness;

            sf::Color inputColor;
            sf::Color inputOutlineColor;
            float     inputOutlineThickness;

            sf::Color baseTextColor;
            sf::Color inputTextColor;
        };

        inline TextArea(const std::string& name = {})
            : Border(name.size() ? name : naming::GenerateName<Button>())
            , Focusable()
            , inputString(L"")
            , previewString(L"Write text here...")
            , normalStyle{
                {200, 200, 200}, {}, 0.f, 
                {150, 150, 150, 100}, {255, 194, 153}, 4.f,
                {100, 100, 100}, {50, 50, 50}
            }
            , focusStyle{
                {200, 200, 200}, {}, 0.f, 
                {150, 150, 150, 100}, {255, 102, 0}, 4.f,
                {100, 100, 100}, {50, 50, 50}
            }
            , insideBorder(nullptr)
            , insideText(nullptr)
            , minimalSize{}
            , cursorPosition(0)
        {
            insideBorder = new Border();
            insideText = new Text(inputString);
            insideText->setWrapEnabled(true);
            insideText->setWrapAfter(1200.f);
            setChild(insideBorder);
            insideBorder->setChild(insideText);
            configureStyle();
            minimalSize = child.getShrinkedSize();
        }

        inline bool hasInput()
        {
            return inputString.getSize() > 0;
        }

        TextArea(const TextArea&) = delete;
        TextArea(TextArea&&) = delete;
        
        inline virtual ~TextArea()
        {

        }

        inline void configureStyle()
        {
            Style current;
            if (focused) {
                current = focusStyle;
            } else {
                current = normalStyle;
            }

            shape.setFillColor(current.baseColor);
            shape.setOutlineThickness(current.baseOutlineThickness);
            shape.setOutlineColor(current.baseOutlineColor);

            insideBorder->shape.setFillColor(current.inputColor);
            insideBorder->shape.setOutlineThickness(current.inputOutlineThickness);
            insideBorder->shape.setOutlineColor(current.inputOutlineColor);

            insideText->setFillColor(hasInput() ? current.inputTextColor : current.baseTextColor);
            insideText->setText(hasInput() ? inputString : previewString);
            if (!hasInput()) {
                insideText->setFontStyle(FontStyle::Italic);
            } else {
                insideText->setFontStyle(FontStyle::Regular);
            }

        }

        inline void redraw()
        {
            configureStyle();

            Border::redraw();
        }

        Vec2f getShrinkedSize() const
        {
            auto [width, height] = child.getShrinkedSize();

            return {std::max(minimalSize.x, width) + padding.right + padding.left, std::max(minimalSize.y, height) + padding.bottom + padding.top};
        }


        inline core::Primitive* intersectNext(Vec2f pos)
        {
            return nullptr;
        }

        inline void focus() override
        {
            Primitive::redraw();
        }

        inline void lostFocus() override
        {
           
            Primitive::redraw();
        }



        inline void textEntered(sf::Uint32 unicode) override
        {
            switch (unicode) {
                case 13:
                    inputString.insert(cursorPosition++, '\n');
                    break;
                case 8:
                    if (cursorPosition > 0) {
                        inputString.erase(cursorPosition-1);
                        cursorPosition--;
                    }
                    break;
                
                default:
                    inputString.insert(cursorPosition++, unicode);
            }
            cursorPosition = std::max(std::min(cursorPosition, (int)inputString.getSize()), 0);
            textEvent.call(inputString);
            redraw();
            Primitive::redraw();
        }

        void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            if (needRedraw) {
                const_cast<TextArea*>(this)->redraw();
            }
            target.draw(shape, states);
            if (child) {
                states.transform *= shape.getTransform();
                states.transform.translate(padding.left, padding.top);

                target.draw(child, states);
            }
        }

        inline void setInputString(const sf::String& str)
        {
            inputString = str;
            cursorPosition = inputString.getSize();
            Primitive::redraw();
        }


        sf::String inputString;
        sf::String previewString;
        
        Style normalStyle;
        Style focusStyle;


        nii::ui::Border* insideBorder;
        nii::ui::Text* insideText;

        Vec2f minimalSize;
        int cursorPosition;

    };
}