#pragma once

#include "Core/Primitive.hpp"
#include "Core/ChildPrimitive.hpp"
#include "Traits.hpp"

#include <vector>

namespace nii::ui
{
    class Grid: public core::Primitive
    {
    public:
    
        Grid();
        virtual ~Grid();

        size_t getRowsCount() const;
        size_t getColumnsCount() const;

        void addChild(core::Primitive* child, size_t row, size_t col);
        // void removeChild(size_t row, size_t col);
        // Primitive* fetchChild(size_t row, size_t col);
        // void changeChild(size_t row, size_t col, core::Primitive* newChild);
    
        void redraw() /* override */;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        void setSize(const Vec2f& size, bool withRedraw = true) override;
        Vec2f getShrinkedSize() const override;

    // private:
        void calculateGridSize(size_t row, size_t col);
        Vec2f findBound(size_t row, size_t col) const;
        float findRowHeight(size_t row) const;
        float findColumnWidth(size_t col) const;

        float findPositionX(size_t row) const;
        float findPositionY(size_t col) const;

    // private:
        std::vector<std::vector<core::ChildPrimitive>> children;
        size_t rowsCount;
        size_t columnsCount;

        size_t cRowsCount;
        size_t cColumnsCount;

        // Vec2f maxBound;
        
    };
}