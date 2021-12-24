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

        void setFillColor(sf::Color newColor);
        inline sf::Color getFillColor() const { return color; }

        void setText(const sf::String& text);
        inline sf::String getText() const { return string; }

        void setFont(const sf::Font& font);
        void setCharacterSize(unsigned int size);

        void setFontStyle(FontStyle style);
        inline FontStyle getFontStyle() const { return (FontStyle)text.getStyle(); }


        void setWrapEnabled(bool enable);
        void setWrapAfter(float wrap);


        void serialize(nii::json::entities::wrapper wrapper) override;
        core::Primitive* deserialize(nii::json::entities::wrapper wrapper) override;

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