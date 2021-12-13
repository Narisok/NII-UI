#pragma once

#include <NII/Utility/AgregatesLiterals.hpp>

#include <SFML/Graphics/Text.hpp>

namespace nii::ui
{
    class Paddingable
    {
        template<class U>
        inline void setPadding(Indents<U> indents) {
            padding = indents;
        }

    protected:
        IndentsFloat padding;
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

}