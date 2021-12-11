#include <NII/UI/Image.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>

using std::cout;
using std::endl;


namespace nii::ui
{
     Image::Image()
        : Primitive()
        , isRepeated(false)
        , useTexture(false)
        , objectFit(ObjectFit::Fill)
        , size({32,32})
        , color({255, 255, 255})

        , texture()
        , vertexesBuffer()
        , renderer()
    {
        renderer.create(32, 32);
        setSize(size);
        cout << "Image ()" << endl;
    }

    Image::~Image()
    {
        cout << "Image ~~" << endl;
    }

    void Image::redraw()
    {
        auto states = sf::RenderStates::Default;
        if (useTexture) {
            states.texture = &texture;
        }

        renderer.clear(sf::Color(0,0,0,0));
        renderer.draw(vertexesBuffer, 4, sf::PrimitiveType::Quads, states);
        renderer.display();


        needRedraw = false;
        
        // Primitive::redraw();
    }

    void Image::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (needRedraw) {
            const_cast<Image*>(this)->redraw();
        }
        target.draw(sf::Sprite(renderer.getTexture()), states);
    }

    void Image::setSize(const Vec2f& newSize, bool withRedraw)
    {
        vertexesBuffer[0].position = {0,0};
        vertexesBuffer[0].texCoords = {0,0};
        
        vertexesBuffer[1].position = {newSize.x,0};
        vertexesBuffer[1].texCoords = {newSize.x,0};

        vertexesBuffer[2].position = newSize;
        vertexesBuffer[2].texCoords = newSize;

        vertexesBuffer[3].position = {0,newSize.y};
        vertexesBuffer[3].texCoords = {0,newSize.y};

        restartRenderer(newSize);

        if(withRedraw) {
            Primitive::redraw();
        }
    }

    void Image::restartRenderer(const Vec2f& size) const
    {
        auto [width, height] = renderer.getSize();
        if(size.x > width || size.y > height) {
            while (width < size.x) {
                width *= 2;
            }
            while (height < size.y) {
                height *= 2;
            }
            renderer.create(width, height);
        }
    }


    void Image::setViewSize(const Vec2f& newSize)
    {
        size = newSize;
        setSize(size);
    }

    void Image::resetViewSize()
    {
        if (useTexture) {
            size = {static_cast<float>(texture.getSize().x), static_cast<float>(texture.getSize().y)};
        } else {
            size = {32, 32};
        }

        setSize(shrinkToFit ? size : boundSize);
    }



    Vec2f Image::getShrinkedSize() const
    {
        return size;
    }

    void Image::setTexture(const sf::Texture& rhl, bool useTexture)
    {
        texture = rhl;
        setUseTexture(useTexture);
    }

    void Image::setIsRepeated(bool repeated)
    {
        isRepeated = repeated;
        texture.setRepeated(repeated);
        Primitive::redraw();
    }

    void Image::setUseTexture(bool use)
    {
        useTexture = use;
        auto newColor = use ? sf::Color({255, 255, 255, 255}) : color;
        vertexesBuffer[0].color = newColor;
        vertexesBuffer[1].color = newColor;
        vertexesBuffer[2].color = newColor;
        vertexesBuffer[3].color = newColor;
        resetViewSize();
    }

    void Image::setFillColor(sf::Color newColor)
    {
        color = newColor;
        vertexesBuffer[0].color = newColor;
        vertexesBuffer[1].color = newColor;
        vertexesBuffer[2].color = newColor;
        vertexesBuffer[3].color = newColor;
        Primitive::redraw();
    }



}
