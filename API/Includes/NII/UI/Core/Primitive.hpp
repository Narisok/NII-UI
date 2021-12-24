#pragma once

#include "../Traits.hpp"

#include <NII/Utility/AgregatesLiterals.hpp>
#include <NII/json>

#include <SFML/Graphics/Drawable.hpp>

#include <memory>


namespace nii::ui::core
{
    class  Primitive: public sf::Drawable
    {
     using Event = nii::util::Event<>;

    public:
        inline static std::string GetDefaultName() { return "Primitive"; }
    
        Primitive(const std::string& name = {});
        virtual ~Primitive();
        
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override =0;

        void redraw() const;

        virtual void setParent(Primitive* parent);

        void setShrinkToFit(bool shrink);

        Vec2f         getSize()         const;
        Vec2f         getBoundSize()    const;
        virtual Vec2f getShrinkedSize() const =0;

        void setBoundSize(const Vec2f& size);
        virtual void setSize(const Vec2f& size, bool withRedraw = true) =0;

        Primitive* intersect(Vec2f pos);
        virtual Primitive* intersectNext(Vec2f pos);


        void beginHover();
        void beginUnhover();
        void beginPress();
        void beginRelease();
        void beginClick();

    
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

        virtual Primitive* findByName(const std::string& name);

        const std::string& getName() const;
        void setName(const std::string& newName);

        template<class T>
        inline T* as()
        {
            return dynamic_cast<T*>(this);
        }

        template<class T>
        inline void as(std::function<void(T*)> fun)
        {
            auto ptr = dynamic_cast<T*>(this);
            if (ptr) {
                fun(ptr);
            }
        }

        virtual void serialize(nii::json::entities::wrapper wrapper);
        virtual Primitive* deserialize(nii::json::entities::wrapper wrapper);

    // protected:
        std::string name;

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