#pragma once

#include <SFML/Graphics/Drawable.hpp>

namespace nii::ui
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

        virtual void setParent(Primitive *newParent);

    // protected:
        Primitive *parent;
    };
}