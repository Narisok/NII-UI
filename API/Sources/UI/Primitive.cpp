#include <NII/UI/Core/Primitive.hpp>

#include <iostream>

using std::cout;
using std::endl;


namespace nii::ui::core
{
    Primitive::Primitive()
        : parent(nullptr)
        , boundSize({0, 0})
        , shrinkToFit(false)
        , needRedraw(true)
    { cout << "Primitive ()" << endl; }

    Primitive::Primitive(Primitive* parent)
        : parent(parent)
        , boundSize({0, 0})
        , shrinkToFit(false)
    { cout << "Primitive pa" << endl; }

    Primitive::Primitive(const Primitive& other)
        : parent(nullptr)
        , boundSize({0, 0})
        , shrinkToFit(false)
    { cout << "Primitive cp" << endl; }

    Primitive::Primitive(Primitive&& other)
        : parent(nullptr)
        , boundSize({0, 0})
        , shrinkToFit(false)
    { cout << "Primitive mv" << endl; }

    Primitive::~Primitive()
    { cout << "Primitive ~~" << endl; }


    void Primitive::redraw() const
    {
        static size_t redrawsCount = 0;
        std::cout << "REDRAWS: " << ++redrawsCount << std::endl;
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
            // setSize(getShrinkedSize());
        } else {
            shrinkToFit = false;
            newSize = getBoundSize();
            // setSize(getBoundSize());
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