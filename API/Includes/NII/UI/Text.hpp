#pragma once

#include "Core/Primitive.hpp"
#include "Traits.hpp"

#include <SFML/Graphics.hpp>

namespace nii::ui
{
    class Text: public core::Primitive
    {
    public:
        inline static std::string GetDefaultName() { return "Text"; }

        Text(const sf::String& str = sf::String(), const std::string& name = {});
        virtual ~Text();
    
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        void redraw() /* override */;

        void setSize(const nii::util::Vec2f& size, bool withRedraw = true) override;
        nii::util::Vec2f getShrinkedSize() const override;

        inline void hover() override
        {
            setFillColor({0,220,30, 255});
        }
        
        inline void unhover() override
        {
            setFillColor({0,30,30, 50});
        }

        inline void press() override
        {
            setFillColor({255,255,240,140});
        }

        inline void release() override
        {
            setFillColor({255,255,240,255});
        }


        void setFillColor(sf::Color newColor);

        void setText(const sf::String& text);

        void setFont(const sf::Font& font);
        void setCharacterSize(unsigned int size);
        // void setStyl

        void setFontStyle(FontStyle style);


        void setWrapEnabled(bool enable);
        void setWrapAfter(float wrap);

    private:
        void restartRenderer(nii::util::Vec2f size);
        void recalculateWrappedText();
    public:


    // private:
        sf::Color color;
        sf::Text text;
        sf::String string;

        mutable sf::RenderTexture renderer;
        float wrapAfter;
        bool wrapEnabled;
        
    };
}