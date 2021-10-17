#pragma once

#include "Primitive.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

namespace nii::ui
{
    class Border: public Primitive
    {
    public:
        Border();
        Border(const Border& other);
        Border(Border&& other);
        ~Border();
    
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        // void setChild(Primitive* newChild);

    // private:
        Primitive* child;
        sf::RectangleShape shape;
        
    };
}