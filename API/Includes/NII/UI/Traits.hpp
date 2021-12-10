#pragma once

#include "NII/Utility/AgregatesLiterals.hpp"

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

    enum class HorizontalAlignment: char
    {
        Left = 0x1,
        Center = 0x2,
        Right = 0x4,
    };

    enum class VerticalAlignment: char
    {
        Top = 0x1,
        Center = 0x2,
        Bottom = 0x4,
    };

}