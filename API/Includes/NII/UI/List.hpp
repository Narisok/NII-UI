#pragma once

#include "Core/Primitive.hpp"
#include "Core/ChildPrimitive.hpp"
#include "Traits.hpp"

#include <vector>

namespace nii::ui
{
    class List: public core::Primitive
    {
    public:
        inline static std::string GetDefaultName() { return "List"; }

        List(const std::string& name = {});
        virtual ~List();

        List(const List& other) = delete;
        List(List&& other) = delete;


        Primitive* intersectNext(Vec2f pos) override;



        // Vec2f getChildBoundSize(size_t idx) const;
        void addChild(core::Primitive* child);
        void addChild(std::unique_ptr<core::Primitive>&& child);
        // void removeChild(size_t idx);
        // Primitive* fetchChild(size_t idx);
        // void changeChild(size_t idx, core::Primitive* newChild);
    
        void redraw() /* override */;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        void setSize(const Vec2f& size, bool withRedraw = true) override;
        Vec2f getShrinkedSize() const override;

        void setPlane(Plane newPlane);

    // private:
        std::vector<core::ChildPrimitive> children;
        Plane plane;
        
    };
}