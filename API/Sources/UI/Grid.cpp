#include "NII/UI/Grid.hpp"

#include <SFML/Graphics.hpp>

namespace nii::ui
{
    Grid::Grid()
        : Primitive()
        , children(4)
        , rowsCount(0)
        , columnsCount(0)
        , cRowsCount(4)
        , cColumnsCount(4)
        // , maxBound({0.f, 0.f})
    {
        for (auto& a : children) {
            a.resize(4);
        }
    }

    Grid::~Grid()
    {}


    core::Primitive* Grid::intersectNext(Vec2f pos)
    {
        float tmpColsWidth = 0;
        for (auto r = 0u; r < rowsCount; r++) {
            float height = findRowHeight(r);
            
            for (auto c = 0u; c < columnsCount; c++) {
                float width = findColumnWidth(c);
                tmpColsWidth += width;
                if (width >= pos.x && height >= pos.y) {
                    return children[r][c].intersect(pos);
                }
                pos.x -= width;
                
            }
            pos.x += tmpColsWidth;
            pos.y -= height;
            tmpColsWidth = 0;
            
        }
        return nullptr;
    }

    void Grid::redraw()
    {
        if (shrinkToFit) {
            setSize(getShrinkedSize(), false);
        } else {
            setSize(getBoundSize(), false);
        }

        needRedraw = false;
    }

    void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // sf::RectangleShape shape(getSize());
        // shape.setFillColor({0,0,0,50});
        // shape.setOutlineColor({255,20,20,100});
        // shape.setOutlineThickness(3);
        // target.draw(shape, states);

        if (needRedraw) {
            const_cast<Grid*>(this)->redraw();
        }

        float tmpColsWidth = 0;
        for (auto r = 0u; r < rowsCount; r++) {
            float height = r == 0 ? 0 : findRowHeight(r - 1);
            states.transform.translate(-tmpColsWidth, height);
            tmpColsWidth = 0;
            for (auto c = 0u; c < columnsCount; c++) {
                float width = c == 0 ? 0 : findColumnWidth(c - 1);
                tmpColsWidth += width;
                states.transform.translate(width, 0.f);
                target.draw(children[r][c], states);

                // sf::RectangleShape shape(findBound(r,c));
                // shape.setFillColor({54,45,54,50});
                // shape.setOutlineColor({255,255,250,250});
                // shape.setOutlineThickness(3);
                // target.draw(shape, states);
            }
        }
    }

    void Grid::setSize(const Vec2f& size, bool withRedraw)
    {
        // for (auto& a : children) {
        //     auto [width, height] = a.getShrinkedSize();
        //     a.setBoundSize({vr ? size.x : width, vr ? height : size.y});
        // }

        for (auto r = 0u; r < rowsCount; r++) {
            float height = findRowHeight(r);
            for (auto c = 0u; c < columnsCount; c++) {
                float width = findColumnWidth(c);
                children[r][c].setBoundSize({width, height});
            }
        }

        if (withRedraw) {
            Primitive::redraw();
        }
    }

    Vec2f Grid::getShrinkedSize() const
    {
        return {findPositionX(columnsCount - 1), findPositionY(rowsCount - 1)};
    }

    void Grid::addChild(core::Primitive* child, size_t row, size_t col)
    {
        calculateGridSize(row, col);
        auto [width, height] = child->getShrinkedSize();
        Vec2f bound = findBound(row, col);
        bound.x = width > bound.x ? width : bound.x;
        bound.y = height > bound.y ? height : bound.y;
        children[row][col].setChild(this, child, bound);
    }


    Vec2f Grid::findBound(size_t row, size_t col) const
    {
        return {findColumnWidth(col), findRowHeight(row)};
    }

    float Grid::findRowHeight(size_t row) const
    {
        float result = 0;

        for (auto& a : children[row]) {
            float height = a.getShrinkedSize().y;
            if (height > result) {
                result = height;
            }
        }

        return result;
    }

    float Grid::findColumnWidth(size_t col) const
    {
        float result = 0;

        for (auto& rows : children) {
            auto width = rows[col].getShrinkedSize().x;
            if (width > result) {
                result = width;
            }
        }

        return result;
    }


    float Grid::findPositionX(size_t col) const
    {
        float width = 0;

        for (auto i = 0u; i < col + 1; i++) {
            width += findColumnWidth(i);
        }

        return width;
    }

    float Grid::findPositionY(size_t row) const
    {
        float height = 0;

        for (auto i = 0u; i < row + 1; i++) {
            height += findRowHeight(i);
        }

        return height;
    }



    void Grid::calculateGridSize(size_t row, size_t col)
    {
        size_t cRowsNewCount = row + 1;
        size_t cColumnsNewCount = col + 1;

        if (cRowsNewCount > rowsCount) {
            rowsCount = cRowsNewCount;
        }


        if (cColumnsNewCount > columnsCount) {
            columnsCount = cColumnsNewCount;
        }

        if ( cRowsNewCount > cRowsCount) {
            children.resize(cRowsNewCount + 2);
            cRowsCount = cRowsNewCount + 2;
        }

        if (cColumnsNewCount > cColumnsCount) {
            for (auto &a : children) {
                a.resize(cColumnsNewCount + 2);
            }
            cColumnsCount = cColumnsNewCount + 2;
        }
    }


    size_t Grid::getRowsCount() const
    {
        return rowsCount;
    }

    size_t Grid::getColumnsCount() const
    {
        return columnsCount;
    }

        // void removeChild(size_t row, size_t col);
        // Primitive* fetchChild(size_t row, size_t col);
        // void changeChild(size_t row, size_t col, core::Primitive* newChild);
    


}
