#pragma once

#include "Core/Primitive.hpp"
#include "Traits.hpp"

#include <SFML/Graphics.hpp>

namespace nii::ui
{
    class Image: public core::Primitive
    {
    public:
        Image();
        ~Image();
    
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        void redraw() /* override */;

        void setSize(const Vec2f& size, bool withRedraw = true) override;
        Vec2f getShrinkedSize() const override;

        void setTexture(const sf::Texture& rhl, bool useTexture = true);

        void setIsRepeated(bool repeated);

        void setUseTexture(bool use);

        void setFillColor(sf::Color newColor);

        void setViewSize(const Vec2f& newSize);
        void resetViewSize();

    private:
        void restartRenderer(const Vec2f& size) const;
    public:


    // private:
        // sf::RectangleShape shape;
        bool isRepeated;
        bool useTexture;
        ObjectFit objectFit;
        Vec2f size;
        sf::Color color;

        sf::Texture texture;
        mutable sf::Vertex vertexesBuffer[4];
        mutable sf::RenderTexture renderer;
        
    };
}