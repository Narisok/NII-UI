#pragma once

#include "Core/Primitive.hpp"
#include "Traits.hpp"

#include <SFML/Graphics.hpp>

namespace nii::ui
{
    class Text: public core::Primitive
    {
    public:
        Text();
        virtual ~Text();
    
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        void redraw() /* override */;

        void setSize(const nii::util::Vec2f& size, bool withRedraw = true) override;
        nii::util::Vec2f getShrinkedSize() const override;


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