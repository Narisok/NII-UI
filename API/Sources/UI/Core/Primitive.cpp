#include "NII/UI/Core/Primitive.hpp"


namespace nii::ui::core
{
    Primitive::Primitive(const std::string& name)
        : name(name)
        , parent(nullptr)
        , boundSize({0, 0})

        , hoverEvent()
        , unhoverEvent()
        , clickEvent()
        , pressEvent()
        , releaseEvent()

        , shrinkToFit(false)
        , pressed(false)
        , hovered(false)
        , needRedraw(true)
    {
        if (!this->name.size()) {
            this->name = naming::GenerateName<Primitive>();
        }
    }

    Primitive::~Primitive()
    {    }
    

    Primitive* Primitive::intersect(Vec2f pos)
    {
        auto [width, height] = getSize();
        if (static_cast<float>(pos.x) <= width && static_cast<float>(pos.y) <= height) {
            auto primitive = intersectNext({static_cast<float>(pos.x), static_cast<float>(pos.y)});
            if (primitive) {
                return primitive;
            } else {
                return this;
            }
        }
        return nullptr;
    }

    Primitive* Primitive::intersectNext(Vec2f pos)
    {
        return nullptr;
    }

    Primitive* Primitive::findByName(const std::string& name)
    {
        return name == this->name ? this : nullptr;
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


    const std::string& Primitive::getName() const
    {
        return name;
    }

    void Primitive::setName(const std::string& newName)
    {
        name = newName;
    }

    void Primitive::serialize(nii::json::entities::wrapper wrapper)
    {
    }
    Primitive* Primitive::deserialize(nii::json::entities::wrapper wrapper)
    {
        return nullptr;
    }

}