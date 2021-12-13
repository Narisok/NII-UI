#include "NII/UI/Core/Primitive.hpp"


namespace nii::ui::core
{
    Primitive::Primitive()
        : parent(nullptr)
        , boundSize({0, 0})
        , shrinkToFit(false)
        , needRedraw(true)
    { /* cout << "Primitive ()" << endl; */ }

    Primitive::~Primitive()
    { /* cout << "Primitive ~~" << endl; */ }


    void Primitive::redraw() const
    {
        bool recursive = !needRedraw;
        needRedraw = true;
        if(recursive && parent) {
            parent->redraw();
        }
    }

    void Primitive::setParent(Primitive *newParent)
    {
        parent = newParent;
        redraw();
    }

    void Primitive::setShrinkToFit(bool shrink)
    {
        Vec2f newSize;
        auto [width, height] = getSize();
        if (shrink) {
            shrinkToFit = true;
            newSize = getShrinkedSize(); 
        } else {
            shrinkToFit = false;
            newSize = getBoundSize();
        }
        if (newSize.x != width || newSize.y != height) {
            setSize(newSize);
        }
    }


    void Primitive::setBoundSize(const Vec2f& size)
    {
        if (size.x != boundSize.x || size.y != boundSize.y) {
            boundSize = size;
            if (!shrinkToFit) {
                setSize(size);
            }
        }
    }


    Vec2f Primitive::getSize() const
    {
        if(shrinkToFit) {
            return getShrinkedSize();
        } else {
            return boundSize;
        }
    }

    Vec2f Primitive::getBoundSize() const
    {
        return boundSize;
    }


    // Vec2f Primitive::getSize() const
    // {
    //     auto [top, bottom, left, right] = getBound();
    //     return {right - left, bottom - top};
    // }

    // void Primitive::setSize(const Vec2f& size)
    // {

    // }

}