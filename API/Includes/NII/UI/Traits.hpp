#pragma once

#include <NII/Utility/AgregatesLiterals.hpp>
#include <NII/Utility/Event.hpp>

#include <SFML/Graphics/Text.hpp>

namespace nii::ui
{
    class Paddingable
    {
        // template<class U>
        // inline void setPadding(Indents<U> indents) {
        //     padding = indents;
        // }

    protected:
        IndentsFloat padding;
    };

    class Focusable
    {
    public:
        inline Focusable()
            : focused(false)
        {}

        inline void beginFocus()
        {
            if (!focused) {
                focused = true;
                focus();
            }
        }

        inline void endFocus()
        {
            if (focused) {
                focused = false;
                lostFocus();
            }
        }


        inline virtual void focus() {};
        inline virtual void lostFocus() {};

        inline virtual void textEntered(sf::Uint32 unicode) {};
        // template<class U>
        // inline void setPadding(Indents<U> indents) {
        //     padding = indents;
        // }

        inline void onText(nii::util::Event<sf::String>::Function calleable)
        {
            textEvent.addListener(std::move(calleable));
        }

    protected:
        nii::util::Event<sf::String> textEvent;
        bool focused;
    };

    enum class ObjectFit: char
    {
        Fill = 0x1,
        Contain = 0x2,
        Cover = 0x4,
    };

    enum class FontStyle: char
    {
        Regular         = sf::Text::Style::Regular,
        Bold            = sf::Text::Style::Bold,
        Italic          = sf::Text::Style::Italic,
        Underlined      = sf::Text::Style::Underlined,
        StrikeThrough   = sf::Text::Style::StrikeThrough,
    };

    enum class HorizontalAlignment: char
    {
        Left = 0x1,
        Center = 0x2,
        Right = 0x4,
        Fill = 0x8,
    };

    using Align = HorizontalAlignment;

    inline constexpr Align AlignLeft    = Align::Left;
    inline constexpr Align AlignCenter  = Align::Center;
    inline constexpr Align AlignRight   = Align::Right;
    inline constexpr Align AlignFill   = Align::Fill;

    enum class VerticalAlignment: char
    {
        Top = 0x1,
        Center = 0x2,
        Bottom = 0x4,
        Fill = 0x8,
    };


    using VAlign = VerticalAlignment;

    inline constexpr VAlign VAlignTop    = VAlign::Top;
    inline constexpr VAlign VAlignCenter = VAlign::Center;
    inline constexpr VAlign VAlignBottom = VAlign::Bottom;
    inline constexpr VAlign VAlignFill   = VAlign::Fill;


    enum class Plane: char
    {
        Vertical,
        Horizontal,
    };

    inline constexpr Plane PlaneVertical   = Plane::Vertical;
    inline constexpr Plane PlaneHorizontal = Plane::Horizontal;


    inline const sf::Font& GetDefaultFont()
    {
        static sf::Font font;
        static bool loaded = false;

        if (!loaded) {
            loaded = font.loadFromFile("Fonts/Hauora-Regular.ttf");
        }

        return font;
    }


}