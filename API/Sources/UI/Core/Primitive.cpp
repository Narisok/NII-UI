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


    Primitive* Primitive::intersectNext(Vec2f pos)
    {
        return nullptr;
    }

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


    void Primitive::hover()
    {

    }

    void Primitive::unhover()
    {

    }

    void Primitive::click()
    {

    }

    void Primitive::press()
    {

    }

    void Primitive::release()
    {

    }


    void Primitive::scroll(float delta)
    {
        if (parent) {
            parent->scroll(delta);
        }
    }
    void Primitive::scrollHorizontal(float delta)
    {
        if (parent) {
            parent->scrollHorizontal(delta);
        }
    }


    void Primitive::onHover(Primitive::Event::Function calleable)
    {
        hoverEvent.addListener(std::move(calleable));
    }

    void Primitive::onUnhover(Primitive::Event::Function calleable)
    {
        unhoverEvent.addListener(std::move(calleable));
    }
    
    void Primitive::onClick(Primitive::Event::Function calleable)
    {
        clickEvent.addListener(std::move(calleable));
    }

    void Primitive::onPress(Primitive::Event::Function calleable)
    {
        pressEvent.addListener(std::move(calleable));
    }

    void Primitive::onRelease(Primitive::Event::Function calleable)
    {
        releaseEvent.addListener(std::move(calleable));
    }

    void Primitive::beginHover()
    {
        if (!hovered) {
            hovered = true;
            if (parent) {
                parent->beginHover();
            }
            hover();
            hoverEvent.call();
        }
    }

    void Primitive::beginUnhover()
    {
        if (hovered) {
            hovered = false;
            if (parent) {
                parent->beginUnhover();
            }
            unhover();
            unhoverEvent.call();
        }
    }

    void Primitive::beginClick()
    {
        click();
        clickEvent.call();
    }


    void Primitive::beginPress()
    {
        pressed = true;
        press();
        pressEvent.call();
    }

    void Primitive::beginRelease()
    {
        pressed = false;
        release();
        releaseEvent.call();
    }

}