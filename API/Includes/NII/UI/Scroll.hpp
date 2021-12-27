#pragma once

#include "Core/Primitive.hpp"
#include "Core/ChildPrimitive.hpp"
#include "Traits.hpp"

#include <SFML/Graphics.hpp>

namespace nii::ui
{
    class Scroll: public core::Primitive
    {
    public:
        inline static std::string GetDefaultName() { return "scroll"; }

        Scroll(const std::string& name = {});
        virtual ~Scroll();

        Scroll(const Scroll& other) = delete;
        Scroll(Scroll&& other) = delete;

        Primitive* intersectNext(Vec2f pos) override;
        Primitive* intersectNextWith(Vec2f& pos) override;
    
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        void redraw() /* override */;

        void setSize(const Vec2f& size, bool withRedraw = true) override;
        Vec2f getShrinkedSize() const override;

        void setChild(core::Primitive* child);
        void setChild(std::unique_ptr<core::Primitive>&& child);

        void setViewSize(const Vec2f& newSize);
        void resetViewSize();
        void move(Vec2f pos);


        void scroll(float delta) override;
        void scrollHorizontal(float delta) override;

        core::Primitive* findByName(const std::string& name) override;

        void serialize(nii::json::entities::wrapper wrapper) override;
        core::Primitive* deserialize(nii::json::entities::wrapper wrapper) override;

        inline void removeChild(Primitive* other) override
        {
            child.removeChild();
        }


    private:
        void restartRenderer(Vec2f size);
    public:


    // private:
        // sf::RectangleShape shape;
        Vec2f size;
        Vec2f center;
        mutable sf::RenderTexture renderer;
        core::ChildPrimitive child;
        Plane plane;
        
    };
}