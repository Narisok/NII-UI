#include <SFML/Graphics.hpp>

#include <NII/Utility/Event.hpp>
#include <NII/Utility/Agregates.hpp>
#include <NII/Utility/Debug.hpp>
#include <NII/UI.hpp>
#include <NII/json>

#include <NII/Graphics/Shapes/RoundedShape.hpp>

#include <array>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

class EventController
{
public:
    void update();


    nii::ui::core::Primitive* mainUi {};
    nii::ui::core::Primitive* pressPrimitive {};
    nii::ui::core::Primitive* hoverPrimitive {};
    nii::ui::core::Primitive* focusedPrimitive {};

    inline void setMainUI(nii::ui::core::Primitive* newUI)
    {
        mainUi = newUI;
        mainUi->setSize(*winSize);
    }

    sf::RenderWindow* window {};

    Vec2f mousePosition {};
    sf::View* view;


    Vec2f* winSize;

};







int main(int argc, char **argv)
{
    EventController eventController;
    sf::ContextSettings contextSettings;

    sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML works!", sf::Style::Default, contextSettings);
    eventController.window = &window;

    Vec2f winSize {static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)};
    eventController.winSize = &winSize;

    sf::View view({-290, -30, winSize.x, winSize.y});
    eventController.view = &view;

    nii::ui::Widget widget(winSize);
    eventController.setMainUI(&widget);

    widget.loadFromFile("My custom widget.wdg");

    widget["button"]->onClick([&widget] (auto button) {
        widget["text"]->as<nii::ui::Text>([] (auto text) {
            text->setText(L"Привіт світ");
        });
    });


    while (window.isOpen())
    {
        eventController.update();
        window.setView(view);
        sf::RenderStates screenStates = sf::RenderStates::Default;
        screenStates.transform.translate((view.getCenter().x)-winSize.x/2.f,(view.getCenter().y)-winSize.y/2.f);

        window.clear({50, 50, 80});

        window.draw(widget, screenStates);

        window.display();
    }


    return 0;
}








void EventController::update()
{
    sf::Event event;
        while (window->pollEvent(event))
        {
            if (mainUi) {
                bool shiftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);

                if (event.type == sf::Event::Closed) {
                    window->close();
                }
                if (event.type == sf::Event::Resized) {

                    view->setSize(event.size.width, event.size.height);
                    // window->setView(*view);
                    if (mainUi) {
                        auto [w, h] = window->getSize();
                        mainUi->setSize({static_cast<float>(w), static_cast<float>(h)});
                    }
                    *winSize =  {static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)};
                }


                if (event.type == sf::Event::KeyPressed) {
                    switch (event.key.code) {
                        // key pressed
                    }
                }

                if (event.type == sf::Event::MouseMoved)
                {
                    // mousePosition = {static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)};
                    auto pos1 = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
                    mousePosition = {static_cast<float>(sf::Mouse::getPosition(*window).x), static_cast<float>(sf::Mouse::getPosition(*window).y)};
                    // mousePosition = { pos1.x + view->getCenter().x, pos1.y + view->getCenter().y};
                    auto hovered = mainUi->intersect(mousePosition);
                    if (hovered != hoverPrimitive) {
                        if (hoverPrimitive) {
                            hoverPrimitive->beginUnhover();
                        }
                        hoverPrimitive = hovered;
                        if (hovered) {
                            hovered->beginHover();
                        } 
                    }

                    

                    
                }

                if (event.type == sf::Event::TextEntered)
                {
                    if (focusedPrimitive) {
                        if (auto focusable = dynamic_cast<nii::ui::Focusable*>(focusedPrimitive)) {
                            focusable->textEntered(event.text.unicode);
                        }
                    }
                }

                if (event.type == sf::Event::MouseWheelScrolled) {
                    if (hoverPrimitive) {
                        if (shiftPressed) {
                            hoverPrimitive->scrollHorizontal(event.mouseWheelScroll.delta);
                        } else {
                            hoverPrimitive->scroll(event.mouseWheelScroll.delta);
                        }
                    }
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    switch (event.mouseButton.button) {
                        case sf::Mouse::Button::Left: {
                            pressPrimitive = hoverPrimitive;
                            if (pressPrimitive) {
                                pressPrimitive->beginPress();
                            }

                            if (auto focusable = dynamic_cast<nii::ui::Focusable*>(focusedPrimitive)) {
                                focusable->endFocus();
                            }
                            focusedPrimitive = nullptr;


                            break;
                        }
                    }
                }
                if (event.type == sf::Event::MouseButtonReleased) {
                    switch(event.mouseButton.button) {
                        case sf::Mouse::Button::Left: {

                            auto releasePrimitive = hoverPrimitive;
                            if (pressPrimitive) {
                                pressPrimitive->beginRelease();
                            }
                            if (releasePrimitive == pressPrimitive) {
                                releasePrimitive->beginClick();

                                focusedPrimitive = releasePrimitive;
                                if (auto focusable = dynamic_cast<nii::ui::Focusable*>(focusedPrimitive)) {
                                    focusable->beginFocus();
                                }

                            }

                            pressPrimitive = nullptr;
                            break;
                        }
                    }
                }
            }
        }

}
