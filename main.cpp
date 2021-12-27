#include <SFML/Graphics.hpp>

#include <NII/Utility/Event.hpp>
#include <NII/Utility/Agregates.hpp>
#include <NII/Utility/Debug.hpp>
#include <NII/UI.hpp>
#include <NII/json>

#include <NII/Graphics/Shapes/RoundedShape.hpp>

#include <array>
#include <iostream>
#include <fstream>
#include <filesystem>

class EventController: public sf::Drawable
{
public:
    void update();

    void hook(nii::ui::core::Primitive* primitive);
    void releaseHook(nii::ui::core::Primitive* primitive);

    void changeNameSelected(const sf::String& newName);
    void deleteSelected();

    void removeSelected();

    nii::ui::core::Primitive* mainUi {};
    nii::ui::core::Primitive* pressPrimitive {};
    nii::ui::core::Primitive* hoverPrimitive {};
    nii::ui::core::Primitive* focusedPrimitive {};

    nii::ui::core::Primitive* editorHover {};
    nii::ui::core::Primitive* editorFocused {};
    nii::ui::core::Primitive* hookedPrimitive {};

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::RenderWindow* window {};

    Vec2f mousePosition {};
    sf::View* view;

    sf::Vector2i mpr {};
    bool mprEnabled {false};

    nii::ui::core::Primitive* drawWidget {};

};


int main(int argc, char **argv)
{
    EventController eventController;
    sf::ContextSettings contextSettings;

    sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML works!", sf::Style::Default, contextSettings);
    eventController.window = &window;

    // nii::ui::Widget* modal = new nii::ui::Widget({1200, 800});

    nii::ui::Widget widget({1200, 800});
    eventController.mainUi = &widget;
    widget.setRoot(new nii::ui::Canvas("canvas"));
//     // widget.setRoot(new nii::ui::Border("B1"));
//     // widget.setRoot(new nii::ui::Border("B16"));

   widget["canvas"]->as<nii::ui::Canvas>([] (auto item) {
        item->addChild(new nii::ui::List("top-list"), {350, 50}, {0, 0});
        item->addChild(new nii::ui::List("left-list"), {350, 800}, {0, 50});

        // item->addChild(new nii::ui::Border("B18"), {250, 250}, {100, 500});
        // item->setViewSize({1000, 1000});
        // printf("Canvas here %i\n", item->slots.size());
    });
    widget["top-list"]->as<nii::ui::List>([] (auto item) {
        item->setPlane(nii::ui::PlaneHorizontal);
        item->addChild(new nii::ui::Button("save", "save"));
        item->addChild(new nii::ui::Button("load", "load"));
        auto newButton = new nii::ui::Button("new", "new");
        item->addChild(newButton);
        
    });

   

    widget["left-list"]->as<nii::ui::List>([] (auto item) {
        item->addChild(new nii::ui::Border("bor-scroll"));
        item->addChild(new nii::ui::Scroll("details-scroll"));
        
    });

    widget["bor-scroll"]->as<nii::ui::Border>([] (auto item) {
        item->setChild(new nii::ui::Scroll("primitives-scroll"));
        item->setShrinkToFit(true);
        item->setBorderColor({50, 50, 50});
    });


    widget["primitives-scroll"]->as<nii::ui::Scroll>([] (auto item) {
        item->setViewSize({250, 400});
        item->setChild(new nii::ui::List("primitives-list"));
    });

    widget["primitives-list"]->as<nii::ui::List>([&eventController] (auto item) {
        item->setShrinkToFit(true);
        for(auto& name : {"border", "text", "button", "canvas", "scroll", "list"}) {
            item->addChild(new nii::ui::Border(name + std::string("_border")));

            nii::ui::core::Primitive* added = item->findByName( name + std::string("_border"));
            added->as<nii::ui::Border>([&name, &eventController](auto border) {

                border->setChild(new nii::ui::Button(name+std::string("_button")));
                border->setBorderColor({0,0,0,0});
                
                nii::ui::core::Primitive* added = border->findByName(name+std::string("_button"));
                added->as<nii::ui::Button>([&name, &eventController] (auto button) {

                    button->setChild(new nii::ui::List(name + std::string("_list")));
                    button->setBorderColor({50,40,50,50});
                    auto eventPtr = &eventController;
                    button->onPress(std::bind(&EventController::hook, &eventController, std::placeholders::_1));


                    button->onRelease(std::bind(&EventController::releaseHook, &eventController, std::placeholders::_1));

                    nii::ui::core::Primitive* added = button->findByName(name+std::string("_list"));
                    added->as<nii::ui::List>([&name] (auto list) {
                        list->addChild(new nii::ui::Image(name+std::string("_image")));
                        list->addChild(new nii::ui::Border(name+std::string("bor_1")));

                        list->setShrinkToFit(true);
                        list->setPlane(nii::ui::PlaneHorizontal);

                        nii::ui::core::Primitive* added1 = list->findByName(name+std::string("bor_1"));
                        added1->as<nii::ui::Border>([&name](auto textBorder) {
                            textBorder->setChild(new nii::ui::List(name + std::string("_list")));
                            textBorder->setBorderColor({50,40,50,50});
                            textBorder->setChild(new nii::ui::Text(name + std::string(" my name"), name+std::string("_text")));
                        }); // text border

                        added1 = list->findByName(name+std::string("_image"));
                        added1->as<nii::ui::Image>([&name](auto img) {
                            
                        });
                    }); // list


                }); // button
            });

            
        }
        // item->addChild(new nii::ui::Text("Prmitive 2", "p2"));
        // item->addChild(new nii::ui::Text("Prmitive 3", "p3"));
        // item->redraw();
    });

    widget["details-scroll"]->as<nii::ui::Scroll>([] (auto item) {
        item->setViewSize({260, 400});
        // item->setShrinkToFit(true);
        item->setChild(new nii::ui::List("details-list"));
    });

    widget["details-list"]->as<nii::ui::List>([&eventController] (auto item) {
        auto area = new nii::ui::TextArea("detail-name");
        // area->onText(std::bind(&EventController::changeNameSelected, eventController, std::placeholders::_1));
        area->onText([&eventController] (auto text) {
            eventController.changeNameSelected(text);
        });
        item->addChild(area);
        auto btn = new nii::ui::Button("delete", "Delete selected");
        item->addChild(btn);
        btn->onClick([&eventController](auto button) {
            eventController.deleteSelected();
        });
        // item->visibility = false;
        // auto shrinkList = new nii::ui::List("shrink-list");
        // shrinkList->setPlane(nii::ui::PlaneHorizontal);
        // auto border = new nii::ui::Border;
        // border->setChild(new nii::ui::Text("Shrink to fit"));
        // auto checkBox = new nii::ui::CheckBox("shrink-to-fit");
        // checkBox->setShrinkToFit(true);
        // shrinkList->addChild(border);
        // shrinkList->addChild(checkBox);
        // shrinkList->children[1].setVAlign(nii::ui::VAlignCenter);
        // shrinkList->setShrinkToFit(true);
        // item->addChild(shrinkList);
        // item->children[1].setVAlign(nii::ui::VAlignCenter);
    });







// try {
    // nii::json::json json(R"""(
    //      { "data": { "details": { "shrink_to_fit": false, "size": { "x": 1200.000000, "y": 800.000000 } }, "name": "Widget", "root": { "children": [ { "child": { "child": { "children": [ { "details": { "color": { "a": 255.000000, "b": 120.000000, "g": 255.000000, "r": 170.000000 }, "shrink_to_fit": false, "style": 1.000000, "text": "My text      ", "wrap": { "after": 200.000000, "enabled": true } }, "name": "text", "type": "text" }, { "child": { "child": { "details": { "color": { "a": 255.000000, "b": 0.000000, "g": 0.000000, "r": 0.000000 }, "shrink_to_fit": false, "style": 0.000000, "text": "press", "wrap": { "after": 500.000000, "enabled": false } }, "name": "Text", "type": "text" }, "details": { "border_color": { "a": 255.000000, "b": 255.000000, "g": 255.000000, "r": 255.000000 }, "border_radius": 5.000000, "child_align": 8.000000, "child_valign": 8.000000, "paddings": { "bottom": 10.000000, "left": 10.000000, "right": 10.000000, "top": 10.000000 }, "shrink_to_fit": false, "styles": { "hover": { "color": { "a": 255.000000, "b": 180.000000, "g": 150.000000, "r": 200.000000 }, "paddings": { "bottom": 10.000000, "left": 10.000000, "right": 10.000000, "top": 10.000000 } }, "normal": { "color": { "a": 200.000000, "b": 200.000000, "g": 200.000000, "r": 200.000000 }, "paddings": { "bottom": 10.000000, "left": 10.000000, "right": 10.000000, "top": 10.000000 } }, "press": { "color": { "a": 255.000000, "b": 150.000000, "g": 150.000000, "r": 150.000000 }, "paddings": { "bottom": 11.000000, "left": 8.000000, "right": 8.000000, "top": 11.000000 } } } }, "name": "btn", "type": "button" }, "details": { "border_color": { "a": 255.000000, "b": 200.000000, "g": 200.000000, "r": 255.000000 }, "border_radius": 5.000000, "child_align": 8.000000, "child_valign": 8.000000, "paddings": { "bottom": 150.000000, "left": 50.000000, "right": 50.000000, "top": 50.000000 }, "shrink_to_fit": true }, "name": "B2", "type": "border" } ], "details": { "plane": 0.000000, "shrink_to_fit": true }, "name": "list", "type": "list" }, "details": { "child_align": 8.000000, "child_valign": 8.000000, "plane": 0.000000, "shrink_to_fit": true, "size": { "x": 200.000000, "y": 200.000000 } }, "name": "scroll", "type": "scroll" }, "details": { "border_color": { "a": 255.000000, "b": 80.000000, "g": 50.000000, "r": 50.000000 }, "border_radius": 0.000000, "child_align": 2.000000, "child_valign": 4.000000, "paddings": { "bottom": 10.000000, "left": 10.000000, "right": 10.000000, "top": 10.000000 }, "shrink_to_fit": false }, "name": "B1", "slot": { "position": { "x": 400.000000, "y": 100.000000 }, "size": { "x": 350.000000, "y": 350.000000 } }, "type": "border" }, { "child": null, "details": { "border_color": { "a": 255.000000, "b": 255.000000, "g": 255.000000, "r": 255.000000 }, "border_radius": 5.000000, "child_align": 8.000000, "child_valign": 8.000000, "paddings": { "bottom": 10.000000, "left": 10.000000, "right": 10.000000, "top": 10.000000 }, "shrink_to_fit": false }, "name": "B18", "slot": { "position": { "x": 100.000000, "y": 500.000000 }, "size": { "x": 250.000000, "y": 250.000000 } }, "type": "border" } ], "details": { "shrink_to_fit": false, "size": { "x": 64.000000, "y": 64.000000 } }, "name": "canvas", "type": "canvas" }, "type": "widget" } }
    // )""");
// } catch (const char* str) {
//     std::cout << "ERROR: " << str << std::endl;
// }

    // nii::json::json json;

// try {
    // widget.deserialize(json["data"]);
// } catch (const char* str) {
//     std::cout << "ERROR: " << str << std::endl;
// }


    // json["name"] = "My widget";

    // widget.serialize(json["data"]);


    // std::cout << json.serialize() << std::endl;

    nii::ui::Widget drawWidget({800, 500});
    eventController.drawWidget = &drawWidget;
    drawWidget.setClearColor({0,0,0, 80});
    drawWidget.setSize({800, 500});

    sf::View view({-290, -30, static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)});

    eventController.view = &view;

    nii::graphics::shapes::RoundedShape rsY({5.f, static_cast<float>(window.getSize().y)-20.f});
    rsY.setRadius(2.5f);
    rsY.setFillColor({50,255,50, 50});
    

    nii::graphics::shapes::RoundedShape rsX({static_cast<float>(window.getSize().x)-20.f, 5.f});
    rsX.setRadius(2.5f);
    rsX.setFillColor({255,50,50, 50});
    

    widget["new"]->as<nii::ui::Button>([&drawWidget] (auto button) {
        button->onClick([&drawWidget] (auto button) {
            drawWidget.removeRoot();
        });
    });


    widget["save"]->as<nii::ui::Button>([&drawWidget] (auto button) {
        button->onClick([&drawWidget] (auto button) {
            nii::json::json json;
            json["name"] = drawWidget.name;
            drawWidget.serialize(json["data"]);
            std::ofstream file(drawWidget.name+".wdg");
            if (file.is_open()) {
                printf("OPEN\n");
                file << json.serialize();
                file.close();
            } else {
                printf("NOT OPEN!!\n");
            }
        });
    });
    bool click = false;
    nii::ui::Border* bor = nullptr;
    widget["load"]->as<nii::ui::Button>([&] (auto button) {
        button->onClick([&] (auto button) {
            
            // click = true;
            
            widget["canvas"]->as<nii::ui::Canvas>([&] (auto canvas) {
                
            // eventController.mainUi = modal;
            
                    bor = new nii::ui::Border();
                    bor->setAlign(nii::ui::AlignCenter);
                    bor->setVAlign(nii::ui::VAlignTop);
                    auto list = new nii::ui::List();
                    list->setShrinkToFit(true);
                    bor->setShrinkToFit(true);
                    bor->setChild(list);
                    printf("BOR: %p\n", bor);
                    // modal->setRoot(bor);
                    printf("BOR: %p\n", bor);
                    bor->setShrinkToFit(false);
                    canvas->addChild(bor, {(float)window.getSize().x, (float)window.getSize().y}, {0.f, 0.f});
                    // bor->removeFromParent();
                    for( auto &a : {"Myown.wdg","widget_1.wdg","3",",4","5"}) {
                        auto btn = new nii::ui::Button(std::string(a), std::string(a));
                        btn->onClick([&, bor] (auto i) {
                            printf("BOR: %p\n", bor);
                            try {
                                drawWidget.removeRoot();
                                std::ifstream file(i->name);
                                std::stringstream buffer;
                                buffer << file.rdbuf();
                                nii::json::json json(buffer.str());
                                drawWidget.deserialize(json["data"]);
                                // bor->child.removeChild();
                            } catch (const char* str) {
                                std::cerr << "ERROR: " << str << std::endl;
                            } catch (const std::exception& ex) {
                                std::cerr << ex.what() << std::endl;
                            }
                            printf("BOR: %p\n", bor);
                            click = true;
                            // eventController.mainUi = &widget;
                            // delete modal;
                            // modal = nullptr;
                        });
                        list->addChild(btn);
                    }
            });
        });
    });



    while (window.isOpen())
    {
        if (click) {
            bor->removeFromParent();
            // bor->child.removeChild();
            click = false;
        }
        eventController.update();

        window.setView(view);
        sf::RenderStates screenStates = sf::RenderStates::Default;
        screenStates.transform.translate((view.getCenter().x)-static_cast<float>(window.getSize().x)/2.f,(view.getCenter().y)-static_cast<float>(window.getSize().y)/2.f);

        {
            rsY.setSize({5.f, static_cast<float>(window.getSize().y)});
            rsX.setSize({static_cast<float>(window.getSize().x), 5.f});
            rsY.setPosition(0.f, view.getCenter().y+10.f);
            rsX.setPosition(view.getCenter().x+10.f, 0.f);
            rsY.setOrigin({2.5f, static_cast<float>(window.getSize().y)/2.f});
            rsX.setOrigin({static_cast<float>(window.getSize().x)/2.f, 2.5f});
            rsX.setRadius(2.5f);
            rsX.setFillColor({255,50,50, 50});
            rsY.setRadius(2.5f);
            rsY.setFillColor({50,255,50, 50});
        }
        
        // printf("Mouse: (%f;%f)\n", eventController.mousePosition.x, eventController.mousePosition.x);

        window.clear({50, 50, 80});

        window.draw(rsY);
        window.draw(rsX);
        {
            rsY.setSize({2.f, static_cast<float>(window.getSize().y)});
            rsX.setSize({static_cast<float>(window.getSize().x), 2.f});
            rsY.setPosition(drawWidget.size.x, view.getCenter().y+10.f);
            rsX.setPosition(view.getCenter().x+10.f, drawWidget.size.y);
            rsX.setRadius(1.f);
            rsX.setFillColor({255,50,50, 20});
            rsY.setRadius(1.f);
            rsY.setFillColor({50,255,50, 20});
        }
        window.draw(rsY);
        window.draw(rsX);

        window.draw(drawWidget);

        window.draw(widget, screenStates);

        window.draw(eventController, screenStates);
        // if (modal == eventController.mainUi) {
        //     window.draw(*modal, screenStates);
        // }
        window.display();

        // widget.removeRoot();
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
                view->setSize(event.size.width, event.size.height);
                // window->setView(*view);
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

                if (mprEnabled) {
                    view->setCenter({mpr.x-mousePosition.x, mpr.y-mousePosition.y});
                }
                auto pos1 = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
                if (pos1.x >= 0 && pos1.y >= 0) {
                    editorHover = drawWidget->intersect({pos1.x, pos1.y});
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

                        auto pos1 = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
                        if (pos1.x >= 0 && pos1.y >= 0) {
                            if (editorHover && editorFocused != editorHover) {
                                removeSelected();
                                editorFocused = editorHover;
                                editorFocused->outline(true);
                                mainUi->findByName("details-list")->as<nii::ui::List>([this] (auto item) {
                                    mainUi->findByName("detail-name")->as<nii::ui::TextArea>([&item, this] (auto area) {
                                        area->setInputString(editorFocused->name);
                                    });
                                });
                            }
                        }

                        break;
                    }

                    case sf::Mouse::Button::Right: {
                        mpr.x = mousePosition.x + view->getCenter().x;
                        mpr.y = mousePosition.y + view->getCenter().y;
                        mprEnabled = true;
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

                    case sf::Mouse::Button::Right: {
                        mprEnabled = false;
                    }
                 }
            }
        }

}

void EventController::hook(nii::ui::core::Primitive* primitive)
{
    hookedPrimitive = primitive;
}

void EventController::releaseHook(nii::ui::core::Primitive* primitive)
{
    auto [x, y] = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
    x -= fmod(x, 5);
    y -= fmod(y, 5);

    auto inter = drawWidget->intersect({x, y});
    if (x < 0 || y < 0) {
        inter = nullptr;
    }
    if (inter) {
        inter->as<nii::ui::Widget>([&primitive] (auto widget) {
            auto name = primitive->name.substr(0, primitive->name.find("_button"));
            std::cout << "Widget: " << name << std::endl;
            widget->setRoot(std::move(nii::ui::serialization::createPrimitiveFromType(name)));
        });
        inter->as<nii::ui::Canvas>([&primitive, x, y] (auto canvas) {
            auto name = primitive->name.substr(0, primitive->name.find("_button"));
            std::cout << "Canvas: " << name << std::endl;
            auto newPrimitive = nii::ui::serialization::createPrimitiveFromType(name);

            newPrimitive->setShrinkToFit(true);
            canvas->addChild(std::move(newPrimitive), newPrimitive->getShrinkedSize(), {x, y});
        });

        inter->as<nii::ui::Border>([&primitive] (auto border) {
            auto name = primitive->name.substr(0, primitive->name.find("_button"));
            std::cout << "Border: " << name << std::endl;
            border->setChild(std::move(nii::ui::serialization::createPrimitiveFromType(name)));
        });

        inter->as<nii::ui::Scroll>([&primitive] (auto scroll) {
            auto name = primitive->name.substr(0, primitive->name.find("_button"));
            std::cout << "Scroll: " << name << std::endl;
            scroll->setChild(std::move(nii::ui::serialization::createPrimitiveFromType(name)));
            // scroll->setShrinkToFit(true);
        });

        inter->as<nii::ui::List>([&primitive] (auto list) {
            auto name = primitive->name.substr(0, primitive->name.find("_button"));
            std::cout << "List: " << name << std::endl;
            list->addChild(std::move(nii::ui::serialization::createPrimitiveFromType(name)));
            list->setShrinkToFit(true);
        });
    }

    hookedPrimitive = nullptr;
}

void EventController::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (hookedPrimitive) {
        states.transform.translate(mousePosition.x, mousePosition.y);
        target.draw(*hookedPrimitive, states);
    }
}

void EventController::changeNameSelected(const sf::String& newName)
{
    if (editorFocused) {
        editorFocused->setName(newName.toAnsiString());
    }

}

void EventController::deleteSelected()
{
    if (editorFocused) {
        editorFocused->removeFromParent();
        removeSelected();
    }
}


void EventController::removeSelected()
{
    if (editorFocused) {
        editorFocused->outline(false);
    }
    mainUi->findByName("details-list")->as<nii::ui::List>([this] (auto item) {
        mainUi->findByName("detail-name")->as<nii::ui::TextArea>([&item, this] (auto area) {
            area->previewString = L"Select primitive";
            area->setInputString("");
        });
    });
     editorFocused = nullptr;
}
