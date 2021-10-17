#include <NII/UI/Primitive.hpp>

#include <iostream>

using std::cout;
using std::endl;


namespace nii::ui
{
    Primitive::Primitive()
        : parent(nullptr)
    { cout << "Primitive ()" << endl; }

    Primitive::Primitive(Primitive* parent)
        : parent(parent)
    { cout << "Primitive pa" << endl; }

    Primitive::Primitive(const Primitive& other)
        : parent(nullptr)
    { cout << "Primitive cp" << endl; }

    Primitive::Primitive(Primitive&& other)
        : parent(nullptr)
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
        auto oldParent = parent;
        parent = newParent;
        oldParent->redraw();
        redraw();
    }
}