#pragma once

#include "NII/Utility/AgregatesLiterals.hpp"

#include <SFML/Graphics/Drawable.hpp>

namespace nii::ui::core
{
    class  Primitive: public sf::Drawable
    {
    public:
        Primitive();
        Primitive(Primitive* parent);
        Primitive(const Primitive& other);
        Primitive(Primitive&& other);
        virtual ~Primitive();
        
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override =0;


        virtual void redraw();

        virtual void setParent(Primitive* parent); //TODO: IS NEED? 

        void setShrinkToFit(bool shrink);

        // IndentsFloat getBound() const;
        // virtual void setBound(const IndentsFloat& bound);

        Vec2f         getSize()         const;
        Vec2f         getBoundSize()    const;
        virtual Vec2f getShrinkedSize() const =0;

        void setBoundSize(const Vec2f& size);
        virtual void setSize(const Vec2f& size) =0;



    // protected:
        Primitive *parent;
        Vec2f boundSize;
        bool shrinkToFit;

    };
}