#include "NII/UI/Text.hpp"

#include <iostream>

using std::cout;
using std::endl;


namespace nii::ui
{
    Text::Text()
        : Primitive()
        , color({255, 255, 255})
        , text()
        , string()
        , renderer()
        , wrapAfter(100)
        , wrapEnabled(false)
    {
        renderer.create(32, 32);
        // setSize(size);
        cout << "Text ()" << endl;
    }

    Text::~Text()
    {
        cout << "Text ~~" << endl;
    }

    void Text::redraw()
    {
        auto states = sf::RenderStates::Default;
        renderer.clear(sf::Color(0,0,0,0));
        // text.setString(string);
        // if (wrapEnabled) {
        //     float startPos = text.getGlobalBounds().left;
        //     auto prevString = text.getString();
        //     sf::String newStr;
            
        //     float current = 0;
        //     for (auto i = 0u; i < text.getString().getSize(); i++) {
        //         newStr += prevString[i];
        //         if (prevString[i] == '\n') {
        //             current = 0;
        //             startPos = text.getGlobalBounds().left;
        //             continue;
        //         }
        //         current += text.findCharacterPos(i).x - startPos;
        //         if (current >= wrapAfter) {
        //             newStr += '\n';
        //             current = 0;
        //             startPos = text.findCharacterPos(i).x;
        //         }
        //     }

        //     text.setString(newStr);
        //     renderer.draw(text, states);
        // } else {
        // }
            renderer.draw(text, states);
        renderer.display();


        needRedraw = false;
    }

    void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (needRedraw) {
            const_cast<Text*>(this)->redraw();
        }
        target.draw(sf::Sprite(renderer.getTexture()), states);
    }

    void Text::setSize(const Vec2f& newSize, bool withRedraw)
    {
        // vertexesBuffer[0].position = {0,0};
        // vertexesBuffer[1].position = {newSize.x,0};
        // vertexesBuffer[2].position = newSize;
        // vertexesBuffer[3].position = {0,newSize.y};
        restartRenderer(newSize);
        recalculateWrappedText();

        if(withRedraw) {
            Primitive::redraw();
        }
    }

    void Text::restartRenderer(Vec2f size)
    {
        auto [width, height] = renderer.getSize();
        if(size.x > width || size.y > height) {
            while (width < size.x) {
                width *= 2;
            }
            while (height < size.y) {
                height *= 2;
            }
            renderer.create(width, height);
        }
    }


    Vec2f Text::getShrinkedSize() const
    {
        auto [left, top, width, height] = text.getLocalBounds();
        return {width, height};
    }



    void Text::setFillColor(sf::Color newColor)
    {
        color = newColor;
        text.setFillColor(newColor);
        Primitive::redraw();
    }

    void Text::setText(const sf::String& string)
    {
        this->string = string;
        // text.setString(string);
        recalculateWrappedText();
        Primitive::redraw();
    }

    void Text::setCharacterSize(unsigned int size)
    {
        text.setCharacterSize(size);
        recalculateWrappedText();
        Primitive::redraw();
    }

    void Text::setFont(const sf::Font& font)
    {
        text.setFont(font);
        recalculateWrappedText();
        Primitive::redraw();
    }

    void Text::setFontStyle(FontStyle style)
    {
        text.setStyle(static_cast<sf::Uint32>(style));
        recalculateWrappedText();
        Primitive::redraw();
    }

    void Text::setWrapEnabled(bool enable)
    {
        wrapEnabled = enable;
        recalculateWrappedText();
        Primitive::redraw();
    }

    void Text::setWrapAfter(float wrap)
    {
        wrapAfter = wrap;
        recalculateWrappedText();
        Primitive::redraw();
    }

    void Text::recalculateWrappedText()
    {
        text.setString(string);
        if (wrapEnabled) {
            float startPos = text.getGlobalBounds().left;
            auto prevString = text.getString();
            sf::String newStr;
            
            float current = 0;
            for (auto i = 0u; i < text.getString().getSize(); i++) {
                newStr += prevString[i];
                if (prevString[i] == '\n') {
                    current = 0;
                    startPos = text.getGlobalBounds().left;
                    continue;
                }
                current += text.findCharacterPos(i).x - startPos;
                if (current >= wrapAfter) {
                    newStr += '\n';
                    current = 0;
                    startPos = text.findCharacterPos(i).x;
                }
            }
            text.setString(newStr);
        }
    }
}
