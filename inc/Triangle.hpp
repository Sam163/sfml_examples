#pragma once
#include <SFML/Graphics.hpp>

namespace mt
{
    class Triangle
    {
        float m_r;
        sf::Vector2f m_position;
        sf::CircleShape m_shape;

    public:
        Triangle() = default;

        Triangle(sf::Vector2f position, float r)
        {
            m_shape.setPointCount(3);
            Setup(position, r);
        }

        void Setup(sf::Vector2f position, float r)
        {
            m_position = position;
            m_r = r;
            m_shape.setRadius(m_r);
            m_shape.setPosition(m_position);
            m_shape.setFillColor(sf::Color::Green);
        }

        sf::CircleShape Get()
        {
            return m_shape;
        }
    };

}