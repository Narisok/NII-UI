#pragma once

#include "Core/Primitive.hpp"
#include "Core/ChildPrimitive.hpp"
#include "Traits.hpp"

#include <vector>

namespace nii::ui
{
    class List: public core::Primitive, public Paddingable
    {
    public:

        // struct ChildData
        // {
        //     Vec2f bound;
        //     core::ChildPrimitive child;
        // };
    
        List();
        virtual ~List();



        // Vec2f getChildBoundSize(size_t idx) const;
        void addChild(core::Primitive* child);
        // void removeChild(size_t idx);
        // Primitive* fetchChild(size_t idx);
    
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