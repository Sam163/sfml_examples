#pragma once
#include <string>
#include <iostream>

#include <vector>
#include "Circle.hpp"
#include "Player.hpp"

namespace mt
{

    class Game
    {
        int m_width;
        int m_height;
        std::string m_capture;

        std::vector<mt::Circle> m_circles;

        int m_n;
        sf::RenderWindow m_window;
        sf::Texture m_textureBackground;
        sf::Sprite m_spriteBackground;

        sf::Font m_font;
        sf::Text m_fpsText;
        int m_fps = 0;

        Player m_player;

        float m_speed = 1.8f;

    public:
        Game(int width, int height, const std::string &capture)
        {
            m_width = width;
            m_height = height;
            m_capture = capture;
        }

        bool Setup(int n)
        {
            m_n = n;
            m_window.create(sf::VideoMode(m_width, m_height), m_capture);

            // SETUP CIRCLES
            srand(time(0));

            for (int i = 0; i < m_n; i++)
            {
                int x = rand() % 1000;
                int y = rand() % 600;
                int r = rand() % 100 + 1;
                m_circles.push_back(mt::Circle(sf::Vector2f(x, y), r));
                m_circles.back().set_speed(m_speed);
            }

            // GET BACKGROUND
            if (!m_textureBackground.loadFromFile("assets\\space.jpg"))
            {
                std::cout << "Error while loading background.jpg" << std::endl;
                return false;
            }
            m_spriteBackground.setTexture(m_textureBackground);

            // SETUP FPS COUNTER
            if (!m_font.loadFromFile("assets\\tnr_font.ttf"))
            {
                std::cout << "Error while loading arial.ttf" << std::endl;
                return false;
            }
            m_fpsText.setFont(m_font);
            m_fpsText.setCharacterSize(20); // in pixels, not points!
            m_fpsText.setStyle(sf::Text::Bold | sf::Text::Underlined);
            m_fpsText.setColor(sf::Color::Magenta);

            // SETUP PLAYER
            bool player_setup_result = m_player.setup(
                sf::Vector2f{ 100.f, (float)m_height / 2.f},
                sf::Vector2f{ 0.0F, 0.0F },
                sf::Vector2f{(float)m_width, (float)m_height });
            if (!player_setup_result) {
                std::cout << "Error while setup player assets." << std::endl;
                return false;
            }
        }

        void LifeCycle()
        {
            sf::Clock clock;
            float dt;

            while (m_window.isOpen())
            {
                dt = clock.getElapsedTime().asSeconds();
                clock.restart();

                // CHECK EVENTS
                sf::Event event;
                while (m_window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        m_window.close();
                }
                m_player.controll_events();

                // GAME PROCESS

                m_player.move(dt);

                for (int i = 0; i < m_n; i++) {
                    m_circles[i].move();
                }

                for (int i = 0; i < m_n; i++) {
                    if (!m_circles[i].border_collision(m_width, m_height)) {
                        for (int j = i + 1; j < m_n; j++) {
                            if (m_circles[i].collision(m_circles[j])) {
                                sf::Vector2f position_i = m_circles[i].get_position();
                                sf::Vector2f position_j = m_circles[j].get_position();

                                sf::Vector2f velocity_i = position_i - position_j;
                                sf::Vector2f velocity_j = position_j - position_i;

                                m_circles[i].set_velocity(velocity_i);
                                m_circles[j].set_velocity(velocity_j);

                                m_circles[i].set_speed(m_speed);
                                m_circles[j].set_speed(m_speed);
                            }
                        }
                    } 
                }

                m_fps = static_cast<int>(1.f / dt);
                m_fpsText.setString("FPS: " + std::to_string(m_fps));

                // DRAW FRAME
                m_window.clear();
                m_window.draw(m_spriteBackground);

                for (int i = 0; i < m_n; i++)
                {
                    m_window.draw(m_circles[i].Get());
                }
                m_window.draw(m_player.get_sprite());

                m_window.draw(m_fpsText);
                m_window.display();
            }
        }
    };

}