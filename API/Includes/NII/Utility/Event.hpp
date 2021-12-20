#pragma once

#include <vector>
#include <list>
#include <variant>
#include <functional>
;

#include <iostream>

namespace nii::util
{

    template<class ... ARGS>
    class Event;
    template<class ... ARGS>
    class Listener;

    namespace base
    {
        template<class ... ARGS>
        class Listener;

        template<class ... ARGS>
        class Event
        {
            friend nii::util::Listener<ARGS...>; 
            friend Listener<ARGS...>;

        protected:
            virtual void unbind(Listener<ARGS...> *) =0;
            virtual void bind(Listener<ARGS...> *) =0;
            void connect(Listener<ARGS...>  *listener);
        };

        template<class ... ARGS>
        class Listener
        {
            friend nii::util::Event<ARGS...>;
            friend Event<ARGS...>;

        protected:
            virtual void unbind(Event<ARGS...> *) =0;
            virtual void bind(Event<ARGS...> *) =0;
            void connect(Event<ARGS...>  *event);

        public:
            virtual void takeCall(ARGS const&...) =0;
        };


        template<class ... ARGS>
        inline void Event<ARGS...>::connect(Listener<ARGS...> *listener)
        {
            this->bind(listener);
            listener->bind(this);
        }

        template<class ... ARGS>
        inline void Listener<ARGS...>::connect(Event<ARGS...> *event)
        {
            this->bind(event);
            event->bind(this);
        }
        
    } // namespace base

    


    template<class ... ARGS>
    class Event : public base::Event<ARGS...>
    {
    public:
     using BaseListener = base::Listener<ARGS...>;
     using Function  = std::function<void(ARGS...)>;
     using Listener  = BaseListener*;
     using Variant   = std::variant<Function, Listener>;
     using Container = std::list<Variant>;
     using Iterator  = typename Container::iterator;

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
        Event(const Event& other) = delete;
        Event(Event&& other);
        ~Event();

        ListenerHandler addListenerGuard(Function calleable);
        void addListener(Function calleable);
        void addListener(BaseListener &listener);
        inline void removeListener(ListenerHandler& handler);

        void call(const ARGS &... arguments);
        void operator()(const ARGS &... arguments);

     private:
        void unbind(BaseListener *listener) override;
        void bind(BaseListener *listener) override;

     private:
        Container listeners;
    };


    template<class ... ARGS>
    class Listener : public base::Listener<ARGS...>
    {
    using BaseEvent = base::Event<ARGS...>;
    using Container = std::vector<BaseEvent*>;

    public:
        Listener();
        Listener(const Listener& other) = delete;
        Listener(Listener&& other);
        ~Listener();

        void listen(BaseEvent &event);
        void takeCall(const ARGS &... arguments) = 0;

    private:
        void unbind(BaseEvent *event) override;
        void bind(BaseEvent *event) override;

    private:
        Container events;
    };

    template<class ... ARGS>
    struct AnonymousListener : Listener<ARGS...>
    {
    using Function = std::function<void(ARGS...)>;

        AnonymousListener(Function function)
            : function(function)
        {}
        
        inline void takeCall(ARGS const&... arguments) { function(arguments...); }

    private:
        Function function;
    };

    template<class ... ARGS>
    AnonymousListener(void(ARGS...)) -> AnonymousListener<ARGS...>;

    // ============================== Event ============================== //


        template<class ... ARGS>
        inline Event<ARGS...>::Event()
            : listeners()
        {
            std::cout << "EVENT" << std::endl;
        }

        template<class ... ARGS>
        inline Event<ARGS...>::Event(Event&& other)
            : listeners(std::move(other.listeners))
        {
            std::cout << "EVENT mv" << std::endl;
        }

        template<class ... ARGS>
        inline Event<ARGS...>::~Event()
        {
            std::cout << "~EVENT" << std::endl;
            for(auto &listener : listeners) {
                std::visit([this](auto && arg) {
                    if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, Listener>)
                    arg->unbind(this);
                }, listener);
            }
        }

        template<class ... ARGS>
        inline typename Event<ARGS...>::ListenerHandler Event<ARGS...>::addListenerGuard(Function calleable)
        {
            auto iterator = listeners.emplace(listeners.end(), Variant{std::move(calleable)});
            return ListenerHandler(this, std::move(iterator));
        }

        template<class ... ARGS>
        inline void Event<ARGS...>::addListener(Function calleable)
        {
            listeners.emplace_back(std::move(calleable));
        }

        template<class ... ARGS>
        inline void Event<ARGS...>::addListener(BaseListener &listener)
        {
            this->connect(&listener);
        }


        template<class ... ARGS>
        inline void Event<ARGS...>::removeListener(ListenerHandler& handler)
        {
            if(handler.event == nullptr) {
                throw "Can't unbind empty listener handler!"; //TODO logical error
            }
            if(handler.event != this) {
                throw "The listener handler does not belongs to this event!"; //TODO logical error
            }
            listeners.erase(handler.iterator);
        }

        template<class ... ARGS>
        inline void Event<ARGS...>::call(const ARGS &... arguments)
        {
            for(auto &callable : listeners) {
                std::visit([&arguments...](auto && arg) { 
                    using T = std::decay_t<decltype(arg)>;
                    if constexpr (std::is_same_v<T, Function>)
                        arg(arguments...);
                    else if constexpr (std::is_same_v<T, Listener>)
                        arg->takeCall(arguments...);
                }, callable);
            }
        }

        template<class ... ARGS>
        inline void Event<ARGS...>::operator()(const ARGS &... arguments)
        {
            call(arguments...);
        }

        template<class ... ARGS>
        inline void Event<ARGS...>::unbind(BaseListener *listener)
        {
            for(auto it = listeners.begin(); it != listeners.end(); ++it) {
                auto ptr = std::get_if<Listener>(&*it);
                if(ptr && *ptr == listener) {
                    listeners.erase(it);
                    break;
                }
            }
        }

        template<class ... ARGS>
        inline void Event<ARGS...>::bind(BaseListener *listener)
        {
            listeners.emplace_back(listener);
        }


    // ============================== Event::ListenerHandler ============================== //

        template<class ... ARGS>
        inline Event<ARGS...>::ListenerHandler::ListenerHandler(Event<ARGS...> *event, Event<ARGS...>::Iterator iterator)
            : event(event)
            , iterator(iterator)
        { 
            std::cout << "LISTENER HAND" << std::endl; 
        }

        template<class ... ARGS>
        inline Event<ARGS...>::ListenerHandler::ListenerHandler(Event<ARGS...>::ListenerHandler&&other)
            : event(std::move(other.event))
            , iterator(std::move(other.iterator))
        {
            other.event = nullptr;
        }
        
                template<class ... ARGS>
        inline Event<ARGS...>::ListenerHandler::~ListenerHandler()
        {
            std::cout << "~LISTENER HAND" << std::endl;
            if(event != nullptr) {
                unbind();
            }
        }

        template<class ... ARGS>
        inline void Event<ARGS...>::ListenerHandler::unbind()
        {
            event->removeListener(*this);
            event = nullptr;
        }

        template<class ... ARGS>
        inline void Event<ARGS...>::ListenerHandler::save()
        {
            event = nullptr;
        }



// ============================== Listener ============================== //

        template<class ... ARGS>
        inline Listener<ARGS...>::Listener()
            : events()
        {
            std::cout << "LISTENER" << std::endl;
        }

        template<class ... ARGS>
        inline Listener<ARGS...>::Listener(Listener&& other)
            : events(std::move(other.events))
        {
            std::cout << "LISTENER mv" << std::endl;
        }

        template<class ... ARGS>
        inline Listener<ARGS...>::~Listener()
        {
            std::cout << "~LISTENER" << std::endl;
            for(auto i : events) {
                i->unbind(this);
            }
        }

        template<class ... ARGS>
        inline void Listener<ARGS...>::listen(BaseEvent &event)
        {
            this->connect(&event);
        }

        // template<class ... ARGS>
        // inline void Listener<ARGS...>::takeCall(const ARGS &... arguments)
        // {
        //     std::cout << "LISTENER () " ;
        //     (std::cout << ... << arguments);
        //     std::cout <<  std::endl;
        // }

        template<class ... ARGS>
        inline void Listener<ARGS...>::unbind(BaseEvent *event)
        {
            for(auto it = events.begin(); it != events.end(); ++it) {
                if(*it == event) {
                    events.erase(it);
                    break;
                }
            }
        }

        template<class ... ARGS>
        inline void Listener<ARGS...>::bind(BaseEvent *event)
        {
            events.emplace_back(event);
        }
}