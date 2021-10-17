#pragma once

#include "Primitive.hpp"

#include <SFML/Graphics/RenderTexture.hpp>

namespace nii::ui
{
    class Widget: public Primitive
    {
        
    public:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
        
    // protected:
        void redraw() override;

    // private:
        mutable sf::RenderTexture renderer;
        Primitive *root;
        mutable bool needRedraw;
    };
}