#pragma once
#include <SFML/Graphics.hpp>

namespace mt
{

    class Rectangle
    {
        sf::Vector2f m_size;
        sf::Vector2f m_position;

        sf::RectangleShape m_shape;

    public:
        Rectangle(sf::Vector2f position, sf::Vector2f size) : m_position(position), m_size(size)
        {
            m_shape.setSize(size);
            m_shape.setPosition(position);
            m_shape.setFillColor(sf::Color(255, 100, 55));
        }

        sf::RectangleShape Get()
        {
            return m_shape;
        }
    };

}