#include <SFML/Graphics.hpp>

#include <NII/Utility/Event.hpp>
#include <NII/Utility/Agregates.hpp>
#include <NII/Utility/Debug.hpp>
#include <NII/UI.hpp>

#include <NII/Graphics/Shapes/RoundedShape.hpp>

#include <array>
#include <iostream>

int main(int argc, char **argv)
{
    sf::ContextSettings contextSettings(
        4, // depth
        2, // stencil
        0, // antialiasing
        3,
        0
        );

    sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML works!", sf::Style::Default, contextSettings);
   

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

    // border.shape.setFillColor({255,0,0});
    // border1.shape.setFillColor({0,255,0});


    nii::ui::Image image;

    image.setFillColor({100, 255, 60});
    image.setTexture(textureFace, false);
    image.setViewSize({200, 200});

    nii::ui::Grid grid;

    grid.addChild(&image,0,0);

    grid.addChild(&image,0,1);

    grid.addChild(&text,6,6);

    grid.addChild(&text,5,6);

    grid.addChild(&text,4,6);

    grid.addChild(&text,3,6);

    grid.addChild(&text,2,6);


    grid.addChild(&text,1,0);

    grid.addChild(&text,1,1);

    nii::ui::List list;

    // list.addChild(&image);
    // list.addChild(&text);
    // list.addChild(&image);

    // image.shape.setFillColor({100, 10, 60});
    // image.shape.setTexture(&textureBookmark);
    // image.setSize({32.f, 32.f});

    text.setText(L"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
    text.setWrapAfter(500);
    text.setCharacterSize(16);
    text.setWrapEnabled(true);

    nii::ui::Scroll scroll;
    scroll.setChild(&image);
    image.setViewSize({1000, 1000});
    scroll.setViewSize({200, 200});
    scroll.setShrinkToFit(false);

    widget.setRoot(&border);
    border.setChild(&border1);
    // border1.setChild(&image);
    border1.setChild(&scroll);
    // border1.setChild(&list);

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
        sf::Event event;
        while (window.pollEvent(event))
        {
            bool h = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::A:
                        // image.setObjectFit(nii::ui::ObjectFit::Fill);
                        // text.setFontStyle(nii::ui::FontStyle::Regular);
                        border1.child.setAlign(nii::ui::AlignLeft);
                        
                        break;
                    case sf::Keyboard::O:
                        // image.setObjectFit(nii::ui::ObjectFit::Cover);
                        // text.setFontStyle(nii::ui::FontStyle::Bold);
                        border1.child.setAlign(nii::ui::AlignCenter);
                        break;
                    case sf::Keyboard::E:
                        // image.setObjectFit(nii::ui::ObjectFit::Contain);
                        // text.setFontStyle(nii::ui::FontStyle::StrikeThrough);
                        border1.child.setAlign(nii::ui::AlignRight);
                        break;

                        case sf::Keyboard::SemiColon:
                        border1.child.setVAlign(nii::ui::VAlignTop);
                        
                        break;
                    case sf::Keyboard::Q:
                        border1.child.setVAlign(nii::ui::VAlignCenter);
                        break;
                    case sf::Keyboard::J:
                        border1.child.setVAlign(nii::ui::VAlignBottom);
                        break;

                    case sf::Keyboard::U:
                        // image.setViewSize({200, 200});
                        text.setText("Hello");
                    break;

                    case sf::Keyboard::I:
                        // image.setViewSize({300, 150});
                        text.setText(L"Привіт це дуже великий текст\nThis is a very long text!");
                    break;

                    case sf::Keyboard::W:
                        text.setWrapEnabled(!text.wrapEnabled);
                    break;

                    case sf::Keyboard::M:
                        list.setPlane(list.plane == nii::ui::Plane::Vertical ? nii::ui::Plane::Horizontal : nii::ui::Plane::Vertical);
                    break;
                }
            }
            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.delta > 0) {
                    scroll.move({h ? -10.f : 0.f, h ? 0.f : -10.f});
                } else {
                    scroll.move({h ? 10.f : 0.f, h ? 0.f : 10.f});
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                switch(event.mouseButton.button) {

                    case sf::Mouse::Button::Left:
                        border.setShrinkToFit(!border.shrinkToFit);
                        rshape.setRadius(rshape.getRadius()+5);
                        break;
                    case sf::Mouse::Button::Right:
                        list.setShrinkToFit(!list.shrinkToFit);
                        grid.setShrinkToFit(!grid.shrinkToFit);
                        // image.setShrinkToFit(!image.shrinkToFit);
                        // text.setShrinkToFit(!text.shrinkToFit);
                        // rshape.setRadius(rshape.getRadius()-5);
                        break;

                    case sf::Mouse::Button::Middle:
                        border1.setShrinkToFit(!border1.shrinkToFit);
                        break;

                    case sf::Mouse::Button::XButton1:
                        // image.setViewSize({300, 200});
                        image.setUseTexture(!image.useTexture);

                        // image.setFillColor({100, 255, 60});
                        
                        break;
                    case sf::Mouse::Button::XButton2:
                        // image.resetViewSize();
                        image.setShrinkToFit(!text.shrinkToFit);
                        text.setShrinkToFit(!text.shrinkToFit);

                        // image.setFillColor({255, 255, 0});
                        break;
                }
            }
        }

        window.clear();
        
        // auto view = sf::View({0,200}, {1200/2, 800/2});// 1200, 800
        window.setView(tmp);
        // auto rect = view.getViewport();
        window.draw(widget);
        // sf::RectangleShape sh(view.getSize());
        // sh.setPosition(view.getCenter());
        // sh.setOrigin(view.getSize().x/2, view.getSize().y/2);
        // sh.setFillColor({255,0,0});
        // window.draw(sh);

        window.display();
    }


    return 0;
}