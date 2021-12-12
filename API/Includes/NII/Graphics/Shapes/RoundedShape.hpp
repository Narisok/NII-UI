#pragma once

#include <SFML/Graphics.hpp>

#include <cmath>

namespace nii::graphics::shapes
{

    class RoundedShape: public sf::Shape
    {

    public:

        inline RoundedShape(const sf::Vector2f& size = sf::Vector2f(0, 0))
            : sf::Shape()
            , size(size)
            , radius(5)
        {
            update();
        }

        inline void setRadius(float radius)
        {
            this->radius = radius;
            update();
        }

        inline float getRadius() const
        {
            return radius;
        }

        inline void setSize(const sf::Vector2f& size)
        {
            this->size = size;
            update();
        }

        inline const sf::Vector2f& getSize() const
        {
            return size;
        }

        inline std::size_t getPointCount() const override
        {
            return 40;
        }

        inline sf::Vector2f getPoint(std::size_t index) const override
        {
            switch (index/10u) {
                case 0: {
                    // TL
                    auto pos = index %10;
                    float alpha = 90.f / 9 * (9-pos);
                    float radians = alpha*M_PI/180;
                    float x = sin(radians) * radius;
                    float y = cos(radians) * radius;
                    return {radius-x, radius-y};
                }
                case 1: {
                     // TR
                    auto pos = index %10;
                    float alpha = 90.f / 9 * pos;
                    float radians = alpha*M_PI/180;
                    float x = sin(radians) * radius;
                    float y = cos(radians) * radius;
                    return {size.x-radius+x,radius-y};
                }
                case 2: {
                    // BR
                    auto pos = index %10;
                    float alpha = 90.f / 9 * (9-pos);
                    float radians = alpha*M_PI/180;
                    float x = sin(radians) * radius;
                    float y = cos(radians) * radius;
                    return {size.x-radius+x,size.y-radius+ y};
                }
                case 3: {
                    // BL
                    auto pos = index %10;
                    float alpha = 90.f / 9 * pos;
                    float radians = alpha*M_PI/180;
                    float x = sin(radians) * radius;
                    float y = cos(radians) * radius;
                    return {radius-x,size.y-radius+ y};
                }
            }
            return {0.f, 0.f};
        }


    private:
        sf::Vector2f size;
        float radius;
    };
}