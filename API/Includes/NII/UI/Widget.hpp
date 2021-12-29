#pragma once

#include "Core/Primitive.hpp"

#include <SFML/Graphics/RenderTexture.hpp>

#include <fstream>
#include <sstream>
#include <iostream>

namespace nii::ui
{
    class Widget: public core::Primitive
    {
        
    public:

        inline static std::string GetDefaultName() { return "widget"; }

        Widget(Vec2f size, const std::string& name = {});

        Widget(const Widget&) = delete;
        Widget(Widget&&) = delete;

        virtual ~Widget();

        Primitive* intersectNext(Vec2f pos) override;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;

        inline bool loadFromFile(const std::string& fileName)
        {
            try {
                std::ifstream file(fileName);
                std::stringstream buffer;
                buffer << file.rdbuf();
                nii::json::json json(buffer.str());
                deserialize(json["data"]);
                return true;
            } catch (...) {
                return false;
            }
        }
        
    // protected:
        void redraw() /* override */;

        void setRoot(core::Primitive* root);
        void setRoot(std::unique_ptr<core::Primitive>&& root);
        void removeRoot();
        std::unique_ptr<core::Primitive> extractRoot();

        core::Primitive* findByName(const std::string& name) override;

        core::Primitive* operator[](const std::string& name)
        {
            return findByName(name);
        }



        void setSize(const Vec2f& size, bool withRedraw = true) override;
        Vec2f getShrinkedSize() const override;

        void serialize(nii::json::entities::wrapper wrapper) override;
        core::Primitive* deserialize(nii::json::entities::wrapper wrapper) override;

        void setClearColor(const sf::Color& newColor);

        inline void removeChild(Primitive* other) override
        {
            removeRoot();
        }

    // private:
        sf::RenderTexture renderer;
        std::unique_ptr<core::Primitive> root;
        Vec2f size;

        sf::Color clearColor;
    };
}