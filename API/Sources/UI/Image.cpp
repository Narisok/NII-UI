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
        , backgroundColor({50, 50, 50, 50})

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

        // view.setCenter(sizeW/2, sizeH/2);
        //     view.setSize(sizeW, sizeH);
        if (objectFit == ObjectFit::Contain) {
            
            auto [width, height] = texture.getSize();
            auto size = getSize();

            states.texture = nullptr;
            states.blendMode = sf::BlendMultiply;

            float x = size.x / width;
            float y = size.y / height;
            float mult = x > y ? y : x;

            float wx = (size.x - width * mult) / 2;
            float hy = (size.y - height * mult) / 2;

            sf::Vertex additionalVertex[8];
            additionalVertex[0].position = {0, 0};
            additionalVertex[1].position = {wx > 0 ? wx : size.x, 0};
            additionalVertex[2].position = {wx > 0 ? wx : size.x, hy > 0 ? hy : size.y};
            additionalVertex[3].position = {0, hy > 0 ? hy : size.y};

            additionalVertex[0+4].position = {wx > 0 ? size.x-wx : 0, hy > 0 ? size.y-hy : 0};
            additionalVertex[1+4].position = {size.x, hy > 0 ? size.y-hy : 0};
            additionalVertex[2+4].position = {size.x, size.y};
            additionalVertex[3+4].position = {wx > 0 ? size.x-wx : 0, size.y };

            auto bgColor = sf::Color({0, 0, 0, 0});
            additionalVertex[0].color = bgColor;
            additionalVertex[1].color = bgColor;
            additionalVertex[2].color = bgColor;
            additionalVertex[3].color = bgColor;
            additionalVertex[0+4].color = bgColor;
            additionalVertex[1+4].color = bgColor;
            additionalVertex[2+4].color = bgColor;
            additionalVertex[3+4].color = bgColor;

            renderer.draw(additionalVertex, 8, sf::PrimitiveType::Quads, states);
            if (backgroundColor.a > 0) {
                states.blendMode = sf::BlendAdd;
                bgColor = backgroundColor;
                additionalVertex[0].color = bgColor;
                additionalVertex[1].color = bgColor;
                additionalVertex[2].color = bgColor;
                additionalVertex[3].color = bgColor;
                additionalVertex[0+4].color = bgColor;
                additionalVertex[1+4].color = bgColor;
                additionalVertex[2+4].color = bgColor;
                additionalVertex[3+4].color = bgColor;
                renderer.draw(additionalVertex, 8, sf::PrimitiveType::Quads, states);
            }

        }

        renderer.display();


        needRedraw = false;
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
        vertexesBuffer[1].position = {newSize.x,0};
        vertexesBuffer[2].position = newSize;
        vertexesBuffer[3].position = {0,newSize.y};
        restartRenderer(newSize);
        recalculateTextCoordinates(newSize);

        if(withRedraw) {
            Primitive::redraw();
        }
    }

    void Image::restartRenderer( Vec2f size)
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
        setShrinkToFit(true);
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
        Primitive::redraw();
        // resetViewSize();
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

    void Image::setBackgroundColor(sf::Color newColor)
    {
        backgroundColor = newColor;
        if (objectFit == ObjectFit::Contain) {
            Primitive::redraw();
        }
    }

    void Image::recalculateTextCoordinates(Vec2f size)
    {
        auto [width, height] = texture.getSize();
        switch (objectFit) {
            case ObjectFit::Fill:
                vertexesBuffer[0].texCoords = {0, 0};
                vertexesBuffer[1].texCoords = {width, 0};
                vertexesBuffer[2].texCoords = {width, height};
                vertexesBuffer[3].texCoords = {0, height};
                break;
            case ObjectFit::Cover: {
                float x = size.x / width;
                float y = size.y / height;
                float mult = x < y ? y : x;
                if (mult == 0.f) {
                    vertexesBuffer[0].texCoords = {0, 0};
                    vertexesBuffer[1].texCoords = {width, 0};
                    vertexesBuffer[2].texCoords = {width, height};
                    vertexesBuffer[3].texCoords = {0, height};
                } else {
                    float wx = (size.x - width * mult) / 2;
                    float hy = (size.y - height * mult) / 2;
                    vertexesBuffer[0].texCoords = {-wx/mult, -hy/mult};
                    vertexesBuffer[1].texCoords = {width + wx/mult, -hy/mult};
                    vertexesBuffer[2].texCoords = {width + wx/mult, height + hy/mult};
                    vertexesBuffer[3].texCoords = {-wx/mult, height + hy/mult};
                }
            }
                break;
            case ObjectFit::Contain: {
                float x = size.x / width;
                float y = size.y / height;
                float mult = x > y ? y : x;
                if (mult == 0.f) {
                    vertexesBuffer[0].texCoords = {0, 0};
                    vertexesBuffer[1].texCoords = {width, 0};
                    vertexesBuffer[2].texCoords = {width, height};
                    vertexesBuffer[3].texCoords = {0, height};
                } else {
                    float wx = (size.x - width * mult) / 2;
                    float hy = (size.y - height * mult) / 2;
                    vertexesBuffer[0].texCoords = {-wx/mult, -hy/mult};
                    vertexesBuffer[1].texCoords = {width + wx/mult, -hy/mult};
                    vertexesBuffer[2].texCoords = {width + wx/mult, height + hy/mult};
                    vertexesBuffer[3].texCoords = {-wx/mult, height + hy/mult};
                }
            }
                break;
        }
    }

    void Image::setObjectFit(ObjectFit fit)
    {
        objectFit = fit;
        recalculateTextCoordinates(getSize());

        Primitive::redraw();
    }



}
