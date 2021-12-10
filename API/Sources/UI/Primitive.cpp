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


    void Primitive::redraw()
    {
        if(parent) {
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
        if (shrink) {
            shrinkToFit = true;
            setSize(getShrinkedSize());
        } else {
            shrinkToFit = false;
            setSize(getBoundSize());
        }
    }


    void Primitive::setBoundSize(const Vec2f& size)
    {
        boundSize = size;
        if(!shrinkToFit) {
            setSize(size);
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