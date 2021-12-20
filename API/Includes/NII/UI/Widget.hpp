#pragma once

#include "Core/Primitive.hpp"

#include <SFML/Graphics/RenderTexture.hpp>

namespace nii::ui
{
    class Widget: public core::Primitive
    {
        
    public:
        inline Widget(Vec2f size)
            : renderer()
            , root(nullptr)
            , size(size)
        { 
            setBoundSize(size);
        }

        Primitive* intersectNext(Vec2f pos) override;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
        
    // protected:
        void redraw() /* override */;

        void setRoot(core::Primitive* root);


        void setSize(const Vec2f& size, bool withRedraw = true) override;
        Vec2f getShrinkedSize() const override;

    // private:
        sf::RenderTexture renderer;
        core::Primitive *root;
        Vec2f size;
    };
}