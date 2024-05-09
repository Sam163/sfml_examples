#include <SFML/Graphics.hpp>
#include "Circle.hpp"
#include "Game.hpp"

int main()
{
    mt::Game game(1000, 600, "Game!!!");
    game.Setup(10);

    game.LifeCycle();

    // mt::Game game_copy = game;

    return 0;
}
// #include <SFML/Graphics.hpp>

// int main()
// {
//     sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
//     sf::CircleShape shape(100.f);
//     shape.setFillColor(sf::Color::Green);

//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }

//         window.clear();
//         window.draw(shape);
//         window.display();
//     }

//     return 0;
// }