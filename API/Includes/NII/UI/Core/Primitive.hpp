#pragma once

#include "../Traits.hpp"
#include <NII/Utility/AgregatesLiterals.hpp>
#include <SFML/Graphics/Drawable.hpp>

namespace nii::ui::core
{
    class  Primitive: public sf::Drawable
    {
     using Event = nii::util::Event<>;

    public:
        Primitive();
        virtual ~Primitive();
        
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override =0;


        void redraw() const;
        // virtual void updatedGeometry();

        virtual void setParent(Primitive* parent); //TODO: IS NEED? 

        void setShrinkToFit(bool shrink);

        // IndentsFloat getBound() const;
        // virtual void setBound(const IndentsFloat& bound);

        Vec2f         getSize()         const;
        Vec2f         getBoundSize()    const;
        virtual Vec2f getShrinkedSize() const =0;

        void setBoundSize(const Vec2f& size);
        virtual void setSize(const Vec2f& size, bool withRedraw = true) =0;

        inline Primitive* intersect(Vec2f pos)
        {
            auto [width, height] = getSize();
            // printf("PS: x:%f; y:%f;\n", width, height);
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

        virtual Primitive* intersectNext(Vec2f pos);

        inline void mouseMove(Vec2i pos)
        {
            if (!hovered) {
                hovered = true;
                if (parent) {
                    parent->beginHover();
                }
                hover();
            }
            if (hovered) {
                hovered = false;
                if (parent) {
                    parent->beginUnhover();
                }
                unhover();
            }
        }

        void beginHover();
        void beginUnhover();
    
        virtual void hover();
        virtual void unhover();
        virtual void click();
        virtual void press();
        virtual void release();


        virtual void scroll(float delta);
        virtual void scrollHorizontal(float delta);

        void onHover(Event::Function calleable);
        void onUnhover(Event::Function calleable);
        void onClick(Event::Function calleable);
        void onPress(Event::Function calleable);
        void onRelease(Event::Function calleable);


    // protected:
        Primitive *parent;
        Vec2f boundSize;

        Event hoverEvent;
        Event unhoverEvent;

        Event clickEvent;
        Event pressEvent;
        Event releaseEvent;

        bool shrinkToFit;
        bool pressed;
        bool hovered;
        mutable bool needRedraw;

    };
}