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
    // window.
    eventController.window = &window;


   

    sf::Texture textureBookmark;
    std::cout << (textureBookmark.loadFromFile("bookmark-32.png") ? "texture bookmark loaded successfully" : "texture bookmark error loading") << std::endl;
    sf::Texture textureClose;
    std::cout << (textureClose.loadFromFile("close-32.png") ? "texture close loaded successfully" : "texture close error loading") << std::endl;
    sf::Texture textureTrash;
    std::cout << (textureTrash.loadFromFile("delete-white-24.png") ? "texture close loaded successfully" : "texture close error loading") << std::endl;
    sf::Texture textureFace;
    std::cout << (textureFace.loadFromFile("face.png") ? "texture close loaded successfully" : "texture close error loading") << std::endl;

    sf::Font font;
    
    std::cout << (font.loadFromFile("Fonts/Hauora-Regular.ttf") ? "font loaded successfully" : "font error loading") << std::endl;

    sf::VertexArray quad(sf::Quads, 4);

    // define it as a rectangle, located at (10, 10) and with size 100x100
    quad[0].position = sf::Vector2f(10.f, 10.f);
    quad[1].position = sf::Vector2f(110.f, 10.f);
    quad[2].position = sf::Vector2f(110.f, 110.f);
    quad[3].position = sf::Vector2f(10.f, 110.f);

    // define its texture area to be a 25x50 rectangle starting at (0, 0)
    quad[0].texCoords = sf::Vector2f(0.f, 0.f);
    quad[1].texCoords = sf::Vector2f(24.0f, 0.f);
    quad[2].texCoords = sf::Vector2f(24.0f, 24.f);
    quad[3].texCoords = sf::Vector2f(0.f, 24.f);

    quad[0].color = sf::Color({255, 255, 255});
    quad[1].color = sf::Color({255, 255, 0});
    quad[2].color = sf::Color({255, 0, 255});
    quad[3].color = sf::Color({0, 255, 255});

    sf::RenderStates quadState;

    quadState.texture = &textureTrash;
    quadState.blendMode = sf::BlendAlpha;

    sf::RectangleShape rs1({500, 400});
    rs1.setFillColor({255,0,0});
    rs1.setPosition(100, 100);


    sf::RectangleShape rs2({400, 300});
    rs2.setFillColor({0, 250,0});

    nii::ui::Widget widget({1200, 800});
    eventController.mainUi = &widget;
    widget.renderer.create(1920, 1080);
    widget.renderer.setSmooth(true);

    nii::ui::Border border;
    nii::ui::Border border1;

    nii::ui::Text text;
    text.setCharacterSize(20);
    text.setFont(font);
    text.setFillColor({255, 0,0});
    text.setText("Hello1 omg long text omg oeunths sntaoeu");
    // text.setWrapEnabled(true);
    text.setWrapAfter(200);

    nii::ui::Text textc1;
    textc1.setCharacterSize(20);
    textc1.setFont(font);
    textc1.setFillColor({255, 0,0});
    textc1.setText("Hello1 omg long text omg oeunths sntaoeu");
    // text.setWrapEnabled(true);
    textc1.setWrapAfter(200);

    nii::ui::Text text1;
    text1.setCharacterSize(20);
    text1.setFont(font);
    text1.setFillColor({255, 0,0});
    text1.setText("Hello2");

    nii::ui::Text text2;
    text2.setCharacterSize(60);
    text2.setFont(font);
    text2.setFillColor({255, 0,0});
    text2.setText("Hellmg oeunths");
    // text2.setWrapEnabled(true);
    // text2.setWrapAfter(200);

    nii::ui::Text text3;
    text3.setCharacterSize(20);
    text3.setFont(font);
    text3.setFillColor({255, 0,0});
    text3.setText("Hello1");

    nii::ui::Text text4;
    text4.setCharacterSize(14);
    text4.setFont(font);
    text4.setFillColor({255, 0,0});
    text4.setText("Hellmg31 axoeu sntaoeu");
    text4.setWrapEnabled(true);
    text4.setWrapAfter(200);

    // border.shape.setFillColor({255,0,0});
    // border1.shape.setFillColor({0,255,0});


    nii::ui::Image image;

    image.setFillColor({100, 255, 60});
    image.setTexture(textureFace, false);
    image.setViewSize({200, 200});

    nii::ui::Image image1;

    image1.setFillColor({100, 255, 60});
    image1.setTexture(textureFace, false);
    image1.setViewSize({200, 200});

    nii::ui::Grid grid;

    grid.addChild(&text1,0,0);

    grid.addChild(&text2,0,1);
    grid.addChild(&text3,2,2);


    grid.addChild(&text4,1,2);

    // grid.addChild(&text,4,6);

    // grid.addChild(&text,3,6);

    // grid.addChild(&text,2,6);


    // grid.addChild(&text,1,0);

    // grid.addChild(&text,1,1);

    nii::ui::Canvas canvas;
    canvas.setViewSize({500.f, 500.f});
    canvas.addChild(&textc1, {100.f, 100.f}, {20.f, 20.f});

    canvas.addChild(&image1, {100.f, 400.f}, {220.f, 220.f});






    nii::ui::List list;

    list.addChild(&text);
    list.addChild(&image);

    // image.shape.setFillColor({100, 10, 60});
    // image.shape.setTexture(&textureBookmark);
    // image.setSize({32.f, 32.f});

    text.setText(L"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
    text.setWrapAfter(500);
    text.setCharacterSize(16);
    text.setWrapEnabled(true);

    nii::ui::Scroll scroll;
    scroll.setChild(&list);
    // scroll.setChild(&grid);

    canvas.addChild(&scroll, {300.f, 300.f}, {350.f, 100.f});
    
    // scroll.setChild(&image);
    image.setUseTexture(true);
    image.setViewSize({700, 300});
    // image.set
    scroll.setViewSize({300, 500});
    scroll.setShrinkToFit(false);
    scroll.setShrinkToFit(true);

    widget.setRoot(&border);
    border.setChild(&border1);
    // border1.setChild(&grid);
    // border1.setChild(&image);
    // border1.setChild(&scroll);
    // nii::ui::Text nText(L"My new text");
    nii::ui::Button button;
    button.setShrinkToFit(true);

    nii::ui::TextArea area;
    nii::ui::CheckBox check;
    nii::ui::List l1;
    l1.addChild(&area);
    l1.addChild(&button);
    l1.addChild(&check);
    border1.setChild(&l1);
    area.setShrinkToFit(true);
    check.setShrinkToFit(true);
    // check.setIsChecked(true);
    button.onClick([]() {
        printf("CLICK FROM MYY\n");
    });
    // border1.setChild(&list);
    // border1.setChild(&text);
    text.setShrinkToFit(true);
    text.setText("Hello my name is Andrew!");
    border1.child.setAlign(nii::ui::AlignCenter);
    border1.child.setVAlign(nii::ui::VAlignCenter);
    // border1.setShrinkToFit(true);
    // image.setShrinkToFit(false);
    // scroll.move({0.f, 2056.f});
    // list.setShrinkToFit(true);
    // scroll.setShrinkToFit(true);
    image.setViewSize({1200, 1200});
    image.setShrinkToFit(false);
    image.setShrinkToFit(true);
    grid.setShrinkToFit(true);

    list.setShrinkToFit(true);

    // border.setBorderThickness(10);
    border1.setBorderColor({50, 50, 255, 100});
    // border1.setBorderThickness(5);

    border1.setBorderRadius(20);



   
    nii::graphics::shapes::RoundedShape rshape({500, 500});
    rshape.setOutlineThickness(10);
    rshape.setFillColor({255,255,255});
    rshape.setOutlineColor({0,0,255});
    rshape.setSize({100, 500});
    rshape.setRadius(50);

    rshape.setPosition(200, 200);

    auto tmp = window.getView();
    // tmp.zoom(1.2);
    
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