#include <SFML/Graphics.hpp>
#include <NII/Utility/Event.hpp>
#include <NII/UI/Border.hpp>
#include <NII/Utility/Agregates.hpp>
#include <array>
#include <iostream>
#include <NII/Utility/Debug.hpp>
#include <NII/UI/Widget.hpp>

int main(int argc, char **argv)
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML works!");
    sf::CircleShape shape(100.f);

    sf::RectangleShape rs1({500, 400});
    rs1.setFillColor({255,0,0});
    rs1.setPosition(100, 100);


    sf::RectangleShape rs2({400, 300});
    rs2.setFillColor({0, 250,0});


    nii::ui::Border border;
    nii::ui::Border border1;

    // nii::ui::Border border1;
    nii::ui::Widget widget;
    widget.root = &border;
    border.parent = &widget;

    border1.parent = &border;
    border.child = &border1;

    border.shape.setFillColor({255,0,0});
    border1.shape.setFillColor({0,255,0});

    widget.renderer.create(200, 150);
    border.setBound({0, 150, 0, 200});
    widget.needRedraw = true;
    // widget.renderer.
    // border.redraw();
    
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                std::cout << "hello" << std::endl; 
                border.shape.setFillColor({255,0,0});
                border1.shape.setFillColor({0,255,0});
                border.redraw();
            }
        }

        window.clear();
        window.draw(widget);
        // window.draw(rs1);
        // window.draw(rs2, rs1.getTransform());
        window.display();
    }


    return 0;
}