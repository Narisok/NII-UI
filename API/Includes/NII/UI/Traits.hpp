#pragma once

#include <NII/Utility/AgregatesLiterals.hpp>

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
}