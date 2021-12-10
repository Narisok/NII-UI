#pragma once

#include "Core/Primitive.hpp"

#include <SFML/Graphics/RenderTexture.hpp>

namespace nii::ui
{
    class Widget: public core::Primitive
    {
        
    public:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
        
    // protected:
        void redraw() override;

        void setRoot(core::Primitive* root);


        void setSize(const Vec2f& size) override;
        Vec2f getShrinkedSize() const override;

    // private:
        mutable sf::RenderTexture renderer;
        core::Primitive *root;
    };
}