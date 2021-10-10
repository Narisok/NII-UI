#pragma once

#include <vector>
#include <list>
#include <variant>
#include <functional>
#include <utility>

#include <iostream>

namespace nii::util
{

    class Event;
    class Listener;

    namespace base
    {

        class BaseEvent;
        class BaseListener;

        class BaseEvent
        {
            friend BaseListener; 
            friend Listener;

        protected:
            virtual void unbind(BaseListener*) =0;
            virtual void bind(BaseListener*) =0;
            void connect(BaseListener *listener);
        };

        class BaseListener
        {
            friend BaseEvent;
            friend Event;

        protected:
            virtual void unbind(BaseEvent*) =0;
            virtual void bind(BaseEvent*) =0;
            void connect(BaseEvent *event);

        public:
            virtual void operator()() =0;
        };


        inline void BaseEvent::connect(BaseListener *listener)
        {
            this->bind(listener);
            listener->bind(this);
        }

        inline void BaseListener::connect(BaseEvent *event)
        {
            this->bind(event);
            event->bind(this);
        }

        
    } // namespace base

    


// template<class ... ARGS>
    class Event : public base::BaseEvent
    {
    using Function  = std::function<void()>;
    using Listener  = base::BaseListener*;
    using Variant   = std::variant<Function, Listener>;
    using Container = std::list<Variant>;
    using Iterator = Container::iterator;

    public:
        class ListenerHandler
        {
            friend Event;

        protected:
            ListenerHandler(const ListenerHandler&) = delete;
            ListenerHandler(Event *event, Iterator iterator);

        public:
            ListenerHandler(ListenerHandler&&other);
            ~ListenerHandler();

            void unbind();
            void save();

        private:
            Event *event;
            Iterator iterator;
        };

    public:
        Event();
        Event(const Event& other);
        Event(Event&& other);
        ~Event();

        ListenerHandler listenGuard(Function calleable);
        void listen(Function calleable);
        void listen(base::BaseListener &listener);
        inline void removeListener(ListenerHandler& handler);

        void call();

     private:
        void unbind(base::BaseListener *listener) override;
        void bind(base::BaseListener *listener) override;

     private:
        Container listeners;
    };



    class Listener : public base::BaseListener
    {
    using Container = std::vector<base::BaseEvent*>;
    
    public:
        Listener();
        Listener(const Listener& other) = delete;
        Listener(Listener&& other);
        ~Listener();

        void listen(base::BaseEvent &event);
        void operator()() override;

    private:
        void unbind(base::BaseEvent *event) override;
        void bind(base::BaseEvent *event) override;

    private:
        Container events;
    };

    struct AnonymousListener : Listener
    {

        AnonymousListener(std::function<void()> function)
            : function(function)
        {}
        
        void operator()()
        {
            function();
        }

    private:
        std::function<void()> function;
    };


    // ============================== Event ============================== //


        inline Event::Event()
            : listeners()
        {
            std::cout << "EVENT" << std::endl;
        }

        inline Event::Event(const Event& other)
            : listeners(other.listeners)
        {
            std::cout << "EVENT cp" << std::endl;
        }
        inline Event::Event(Event&& other)
            : listeners(std::move(other.listeners))
        {
            std::cout << "EVENT mv" << std::endl;
        }

        inline Event::~Event()
        {
            std::cout << "~EVENT" << std::endl;
            for(auto &listener : listeners) {
                std::visit([this](auto && arg) {
                    if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, Listener>)
                    arg->unbind(this);
                }, listener);
            }
        }

        inline Event::ListenerHandler Event::listenGuard(Event::Function calleable)
        {
            auto iterator = listeners.emplace(listeners.end(), Variant{std::move(calleable)});
            return ListenerHandler(this, std::move(iterator));
        }

        inline void Event::listen(Event::Function calleable)
        {
            listeners.emplace_back(std::move(calleable));
        }

        void Event::listen(base::BaseListener &listener)
        {
            connect(&listener);
        }


        inline void Event::removeListener(ListenerHandler& handler)
        {
            if(handler.event == nullptr) {
                throw "Can't unbind empty listener handler!"; //TODO logical error
            }
            if(handler.event != this) {
                throw "The listener handler does not belongs to this event!"; //TODO logical error
            }
            listeners.erase(handler.iterator);
        }

        inline void Event::call()
        {
            for(auto &callable : listeners) {
                std::visit([](auto && arg) { 
                    using T = std::decay_t<decltype(arg)>;
                    if constexpr (std::is_same_v<T, Function>)
                        arg();
                    else if constexpr (std::is_same_v<T, Listener>)
                        arg->operator()();
                }, callable);
            }
        }

        inline void Event::unbind(base::BaseListener *listener)
        {
            for(auto it = listeners.begin(); it != listeners.end(); ++it) {
                auto ptr = std::get_if<Listener>(&*it);
                if(ptr && *ptr == listener) {
                    listeners.erase(it);
                    break;
                }
            }
        }

        inline void Event::bind(base::BaseListener *listener)
        {
            listeners.emplace_back(listener);
        }


    // ============================== Event::ListenerHandler ============================== //

        inline Event::ListenerHandler::ListenerHandler(Event *event, Event::Iterator iterator)
            : event(event)
            , iterator(iterator)
        { 
            std::cout << "LISTENER HAND" << std::endl; 
        }

        inline Event::ListenerHandler::ListenerHandler(Event::ListenerHandler&&other)
            : event(std::move(other.event))
            , iterator(std::move(other.iterator))
        {
            other.event = nullptr;
        }
        
        inline Event::ListenerHandler::~ListenerHandler()
        {
            std::cout << "~LISTENER HAND" << std::endl;
            if(event != nullptr) {
                unbind();
            }
        }

        inline void Event::ListenerHandler::unbind()
        {
            event->removeListener(*this);
            event = nullptr;
        }

        inline void Event::ListenerHandler::save()
        {
            event = nullptr;
        }



// ============================== Listener ============================== //

        inline Listener::Listener()
            : events()
        {
            std::cout << "LISTENER" << std::endl;
        }

        // inline Listener::Listener(const Listener& other)
        //     : events(other.events)
        // {
        //     std::cout << "LISTENER cp" << std::endl;
        // }

        inline Listener::Listener(Listener&& other)
            : events(std::move(other.events))
        {
            std::cout << "LISTENER mv" << std::endl;
        }

        inline Listener::~Listener()
        {
            std::cout << "~LISTENER" << std::endl;
            for(auto i : events) {
                i->unbind(this);
            }
        }

        inline void Listener::listen(base::BaseEvent &event)
        {
            connect(&event);
        }

        inline void Listener::operator()()
        {
            std::cout << "LISTENER ()" << std::endl;
        }

        inline void Listener::unbind(base::BaseEvent *event)
        {
            for(auto it = events.begin(); it != events.end(); ++it) {
                if(*it == event) {
                    events.erase(it);
                    break;
                }
            }
        }

        inline void Listener::bind(base::BaseEvent *event)
        {
            events.emplace_back(event);
        }
}