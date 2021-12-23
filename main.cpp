#include <SFML/Graphics.hpp>

#include <NII/Utility/Event.hpp>
#include <NII/Utility/Agregates.hpp>
#include <NII/Utility/Debug.hpp>
#include <NII/UI.hpp>

#include <NII/Graphics/Shapes/RoundedShape.hpp>

#include <array>
#include <iostream>

class EventController
{
public:
    void update();

    nii::ui::core::Primitive* mainUi {};
    nii::ui::core::Primitive* pressPrimitive {};
    nii::ui::core::Primitive* hoverPrimitive {};
    nii::ui::core::Primitive* focusedPrimitive {};

    sf::RenderWindow* window {};

    Vec2f mousePosition {};

}eventController;


int main(int argc, char **argv)
{
    sf::ContextSettings contextSettings;

    sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML works!", sf::Style::Default, contextSettings);
    eventController.window = &window;


    nii::ui::Widget widget({1200, 800});
    eventController.mainUi = &widget;
    widget.setRoot(new nii::ui::Border("B1"));

    widget["B1"]->as<nii::ui::Border>()->setChild(new nii::ui::Border("B2"));
    widget["B2"]->as<nii::ui::Border>()->setBorderColor({255,200, 200});
    widget["B2"]->as<nii::ui::Border>()->setChild(new nii::ui::Button("btn"));

    widget["btn"]->as<nii::ui::Button>()->onClick([]() {
        printf("Hello click\n");
    });
    widget["B2"]->as<nii::ui::Border>()->setChild(new nii::ui::TextArea("area"));

    // widget["B2"]->as<nii::ui::Border>()->setChild(new nii::ui::Text(std::wstring(L"Hello text привіт"), "text"));

    widget["area"]->as<nii::ui::TextArea>([] (auto item) {
        item->onText([](auto text) {
            
        });
    });

    while (window.isOpen())
    {
        

        eventController.update();
        

        window.clear();
        
        window.draw(widget);

        window.display();
    }


    return 0;
}


void EventController::update()
{
    sf::Event event;
    while (window->pollEvent(event))
        {
            bool shiftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);

            if (event.type == sf::Event::Closed) {
                window->close();
            }
            if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window->setView(sf::View(visibleArea));
                if (mainUi) {
                    auto [w, h] = window->getSize();
                    mainUi->setSize({static_cast<float>(w), static_cast<float>(h)});
                }
            }


            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    // key pressed
                }
            }

            if (event.type == sf::Event::MouseMoved)
            {
                mousePosition = {static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)};
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
                        if (releasePrimitive) {
                            releasePrimitive->beginRelease();
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