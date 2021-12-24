#include <SFML/Graphics.hpp>

#include <NII/Utility/Event.hpp>
#include <NII/Utility/Agregates.hpp>
#include <NII/Utility/Debug.hpp>
#include <NII/UI.hpp>
#include <NII/json>

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
//     widget.setRoot(new nii::ui::Canvas("canvas"));
//     // widget.setRoot(new nii::ui::Border("B1"));
//     // widget.setRoot(new nii::ui::Border("B16"));

//    widget["canvas"]->as<nii::ui::Canvas>([] (auto item) {
//         item->addChild(new nii::ui::Border("B1"), {350, 350}, {400, 100});

//         item->addChild(new nii::ui::Border("B18"), {250, 250}, {100, 500});
//         // item->setViewSize({1000, 1000});
//         printf("Canvas here %i\n", item->slots.size());
//     });

//     widget["B16"]->as<nii::ui::Border>([] (auto item) {
//         item->setBorderColor({255,255,0});
//         item->setChild(new nii::ui::Canvas("canvas"));
//         printf("B16\n");
//     });

     

//     widget["B1"]->as<nii::ui::Border>([] (auto item) {
//         // item->setChild(new nii::ui::Border("B2"));
//         item->setChild(new nii::ui::Scroll("scroll"));
//         // item->setChild(new nii::ui::List("list"));
//         item->setAlign(nii::ui::AlignCenter);
//         item->setVAlign(nii::ui::VAlignBottom);
//         item->setBorderColor({50, 50, 80});
//         item->setBorderRadius(0);
//     });
//     widget["scroll"]->as<nii::ui::Scroll>([] (auto item) {
//         item->setChild(new nii::ui::List("list"));
//         // item->setChild(new nii::ui::Border("B2"));
//         item->setViewSize({200, 200});
//         // item->setShrinkToFit(true);
//         // item->redraw();
//     });


//     widget["list"]->as<nii::ui::List>([] (auto item) {
//         item->addChild(new nii::ui::Text(L"My text  дуже багато тексту треба перенести", "text"));
//         item->addChild(new nii::ui::Border("B2"));
//         item->setPlane(nii::ui::PlaneVertical);
//         item->setShrinkToFit(true);
//     });

//      widget["text"]->as<nii::ui::Text>([] (auto item) {
//         item->setFillColor({170,255, 120});
//         item->setFontStyle(nii::ui::FontStyle::Bold);
//         item->setWrapAfter(200.f);
//         item->setWrapEnabled(true);
//     });

//     widget["B2"]->as<nii::ui::Border>([] (auto item) {
//         item->setBorderColor({255,200, 200});
//         item->setPadding({50, 150, 50, 50});
//         item->setShrinkToFit(true);
//     });

//     widget["B2"]->as<nii::ui::Border>()->setChild(new nii::ui::Button("btn"));

//     widget["btn"]->as<nii::ui::Button>( [] (auto item) {
//         item->onClick([]() {
//             printf("Hello click\n");
//         });
//         item->setHoverStyleColor({200, 150, 180});
//         item->setPressStylePadding({11, 8});
//     });

// try {
    nii::json::json json(R"""(
        { "data": { "details": { "shrink_to_fit": false, "size": { "x": 1200.000000, "y": 800.000000 } }, "name": "Widget", "root": { "children": [ { "child": { "child": { "children": [ { "details": { "color": { "a": 255.000000, "b": 120.000000, "g": 255.000000, "r": 170.000000 }, "shrink_to_fit": false, "style": 1.000000, "text": "My text      ", "wrap": { "after": 200.000000, "enabled": true } }, "name": "text", "type": "text" }, { "child": { "child": { "details": { "color": { "a": 255.000000, "b": 0.000000, "g": 0.000000, "r": 0.000000 }, "shrink_to_fit": false, "style": 0.000000, "text": "press", "wrap": { "after": 500.000000, "enabled": false } }, "name": "Text", "type": "text" }, "details": { "border_color": { "a": 255.000000, "b": 255.000000, "g": 255.000000, "r": 255.000000 }, "border_radius": 5.000000, "child_align": 8.000000, "child_valign": 8.000000, "paddings": { "bottom": 10.000000, "left": 10.000000, "right": 10.000000, "top": 10.000000 }, "shrink_to_fit": false, "styles": { "hover": { "color": { "a": 255.000000, "b": 180.000000, "g": 150.000000, "r": 200.000000 }, "paddings": { "bottom": 10.000000, "left": 10.000000, "right": 10.000000, "top": 10.000000 } }, "normal": { "color": { "a": 200.000000, "b": 200.000000, "g": 200.000000, "r": 200.000000 }, "paddings": { "bottom": 10.000000, "left": 10.000000, "right": 10.000000, "top": 10.000000 } }, "press": { "color": { "a": 255.000000, "b": 150.000000, "g": 150.000000, "r": 150.000000 }, "paddings": { "bottom": 11.000000, "left": 8.000000, "right": 8.000000, "top": 11.000000 } } } }, "name": "btn", "type": "button" }, "details": { "border_color": { "a": 255.000000, "b": 200.000000, "g": 200.000000, "r": 255.000000 }, "border_radius": 5.000000, "child_align": 8.000000, "child_valign": 8.000000, "paddings": { "bottom": 150.000000, "left": 50.000000, "right": 50.000000, "top": 50.000000 }, "shrink_to_fit": true }, "name": "B2", "type": "border" } ], "details": { "plane": 0.000000, "shrink_to_fit": true }, "name": "list", "type": "list" }, "details": { "child_align": 8.000000, "child_valign": 8.000000, "plane": 0.000000, "shrink_to_fit": true, "size": { "x": 200.000000, "y": 200.000000 } }, "name": "scroll", "type": "scroll" }, "details": { "border_color": { "a": 255.000000, "b": 80.000000, "g": 50.000000, "r": 50.000000 }, "border_radius": 0.000000, "child_align": 2.000000, "child_valign": 4.000000, "paddings": { "bottom": 10.000000, "left": 10.000000, "right": 10.000000, "top": 10.000000 }, "shrink_to_fit": false }, "name": "B1", "slot": { "position": { "x": 400.000000, "y": 100.000000 }, "size": { "x": 350.000000, "y": 350.000000 } }, "type": "border" }, { "child": null, "details": { "border_color": { "a": 255.000000, "b": 255.000000, "g": 255.000000, "r": 255.000000 }, "border_radius": 5.000000, "child_align": 8.000000, "child_valign": 8.000000, "paddings": { "bottom": 10.000000, "left": 10.000000, "right": 10.000000, "top": 10.000000 }, "shrink_to_fit": false }, "name": "B18", "slot": { "position": { "x": 100.000000, "y": 500.000000 }, "size": { "x": 250.000000, "y": 250.000000 } }, "type": "border" } ], "details": { "shrink_to_fit": false, "size": { "x": 64.000000, "y": 64.000000 } }, "name": "canvas", "type": "canvas" }, "type": "widget" } }
    )""");
// } catch (const char* str) {
//     std::cout << "ERROR: " << str << std::endl;
// }

    // nii::json::json json;

try {
    widget.deserialize(json["data"]);
} catch (const char* str) {
    std::cout << "ERROR: " << str << std::endl;
}


    // json["name"] = "My widget";

    widget.serialize(json["data"]);


    std::cout << json.serialize() << std::endl;


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