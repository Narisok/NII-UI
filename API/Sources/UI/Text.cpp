#include "NII/UI/Text.hpp"

#include <iostream>

using std::cout;
using std::endl;


namespace nii::ui
{
    Text::Text(const sf::String& str, const std::string& name)
        : Primitive(name.size() ? name : naming::GenerateName<Text>())
        , color({255, 255, 255})
        , text(str, GetDefaultFont(), 16)
        , string(str)
        , renderer()
        , wrapAfter(500)
        , wrapEnabled(false)
    {
        // renderer.create(320, 32);
        // renderer.setSmooth(true);
    }

    Text::~Text()
    {
    }

    void Text::redraw()
    {
        // auto states = sf::RenderStates::Default;
        // renderer.clear(sf::Color(0,0,0,0));
        // renderer.draw(text, states);
        // renderer.display();


        needRedraw = false;
    }

    void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (outlined) {
            sf::RectangleShape shape(getSize());
            shape.setFillColor({0,250,0,0});
            shape.setOutlineColor({255, 128, 0, 220});
            shape.setOutlineThickness(4);
            target.draw(shape, states);
        }
        // sf::RectangleShape shape(getSize());
        // shape.setFillColor({0,250,0,50});
        // shape.setOutlineColor({0,0,250,100});
        // shape.setOutlineThickness(5);
        // target.draw(shape, states);

        if (needRedraw) {
            const_cast<Text*>(this)->redraw();
        }
        // target.draw(sf::Sprite(renderer.getTexture()), states);
        target.draw(text, states);
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
        // auto [width, height] = renderer.getSize();
        // if(size.x > width || size.y > height) {
        //     while (width < size.x) {
        //         width += 32;
        //     }
        //     while (height < size.y) {
        //         height += 32;
        //     }
        //     renderer.create(width, height);
        // }
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


    void Text::serialize(nii::json::entities::wrapper wrapper)
    {
        wrapper["name"] = name;
        wrapper["type"] = "text";

        auto details = wrapper["details"];
            details["shrink_to_fit"] = shrinkToFit;
            auto [r, g, b, a] = getFillColor();
            details["color"]["r"] = r;
            details["color"]["g"] = g;
            details["color"]["b"] = b;
            details["color"]["a"] = a;

            details["text"] = string.toAnsiString();

            details["wrap"]["after"] = wrapAfter;
            details["wrap"]["enabled"] = wrapEnabled;
            details["style"] = (int)getFontStyle();
            
    }

    core::Primitive* Text::deserialize(nii::json::entities::wrapper wrapper)
    {
        name = wrapper["name"]->string();

        auto details = wrapper["details"];
            shrinkToFit = details["shrink_to_fit"]->boolean();
            color.r = details["color"]["r"]->number();
            color.g = details["color"]["g"]->number();
            color.b = details["color"]["b"]->number();
            color.a = details["color"]["a"]->number();

            auto str = details["text"]->string();
            string = str;

            wrapAfter = details["wrap"]["after"]->number();
            wrapEnabled = details["wrap"]["enabled"]->boolean();
            setFontStyle((FontStyle) details["style"]->number());
            

        Primitive::redraw();
        return this;
    }
}
