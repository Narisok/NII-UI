#pragma once

#include "Agregates.hpp"
#include <iosfwd>

template<class T>
std::ostream& operator<<(std::ostream& stream, const nii::util::Indents<T> & indents)
{
    return stream << "top: " << indents.top << " buttom: " << indents.buttom << " left: " << indents.left << " right: " << indents.right << "\n";
}