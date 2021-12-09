#pragma once
#include <cstddef>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

namespace nii::util
{
    template<class T, size_t DIMENSIONS>
    struct Vector
    {
        T values[DIMENSIONS];

        inline T& operator[](size_t pos) {
            values[pos];
        }
    };

    template<class T>
    struct Vector<T, 2>
    {
        T x, y;

        inline operator sf::Vector2<T>() const
        {
            return sf::Vector2<T>(x, y);
        }
    };

    template<class T>
    struct Vector<T, 3>
    {
        T x, y, z;

        inline operator sf::Vector3<T>() const
        {
            return sf::Vector3<T>(x, y, z);
        }
    };

    template<class T>
    struct Vector<T, 4>
    {
        T x, y, z, w;
    };

    using Vec2i = Vector<int, 2>;
    using Vec3i = Vector<int, 3>;
    using Vec4i = Vector<int, 4>;

    using Vec2u = Vector<unsigned int, 2>;
    using Vec3u = Vector<unsigned int, 3>;
    using Vec4u = Vector<unsigned int, 4>;

    using Vec2s = Vector<size_t, 2>;
    using Vec3s = Vector<size_t, 3>;
    using Vec4s = Vector<size_t, 4>;    

    using Vec2f = Vector<float, 2>;
    using Vec3f = Vector<float, 3>;
    using Vec4f = Vector<float, 4>;


    template<class T>
    struct Indents
    {
        Indents() 
            : top(0)
            , bottom(0)
            , left(0)
            , right(0)
        {}

        Indents(T all) 
            : top(all)
            , bottom(all)
            , left(all)
            , right(all)
        {}

        Indents(T topBottom, T leftRight) 
            : top(topBottom)
            , bottom(topBottom)
            , left(leftRight)
            , right(leftRight)
        {}

        Indents(T top, T leftRight, T bottom) 
            : top(top)
            , bottom(bottom)
            , left(leftRight)
            , right(leftRight)
        {}

        Indents(T top, T bottom, T left, T right)
            : top(top)
            , bottom(bottom)
            , left(left)
            , right(right)
        {}


        template<class U>
        inline Indents& operator=(const Indents<U>& other) {
            top     = static_cast<T>(other.top);
            bottom  = static_cast<T>(other.bottom);
            left    = static_cast<T>(other.left);
            right   = static_cast<T>(other.right);
        }


        
        T top, bottom, left, right;
    };

}