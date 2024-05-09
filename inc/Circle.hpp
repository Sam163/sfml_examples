#pragma once
#include <SFML/Graphics.hpp>

namespace mt
{
    class Circle
    {
        float m_r;
        sf::Vector2f m_position;
        sf::CircleShape m_shape;

        sf::Vector2f m_velocity{0.1f, 0.1f};

        float norm(const sf::Vector2f& v) {
            return std::sqrt(v.x * v.x + v.y * v.y);
        }

    public:
        Circle() = default;

        Circle(sf::Vector2f position, float r)
        {
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

        bool collision(const Circle& other) {
            float distance = norm(m_position - other.m_position);
            return distance < m_r + other.m_r;
        }

        bool border_collision(int window_width, int window_height) {
            bool result = false;

            if (border_left_collision() && m_velocity.x < 0.f) {
                m_velocity.x *= -1.f;
                result = true;
            }
                
            if (border_right_collision(window_width) && m_velocity.x > 0.f) {
                m_velocity.x *= -1.f;
                result = true;
            }

            if (border_up_collision() && m_velocity.y < 0.f) {
                m_velocity.y *= -1.f;
                result = true;
            }

            if (border_down_collision(window_height) && m_velocity.y > 0.f) {
                m_velocity.y *= -1.f;
                result = true;
            }

            return result;
        }

        bool border_left_collision() {
            return ((m_position.x - m_r) < 0.f); // left border
        }

        bool border_right_collision(int window_width) {
            return ((m_position.x + m_r) > (float)window_width); // left border
        }

        bool border_up_collision() {
            return ((m_position.y - m_r) < 0.f);  // up border
        }

        bool border_down_collision(int window_height) {
            return ((m_position.y + m_r) > (float)window_height);  // down border
        }

        void set_speed(float speed) {
            float n = norm(m_velocity);
            m_velocity /= n;
            m_velocity *= speed;
        }

        void move() {
            m_position += m_velocity;
            m_shape.setPosition(sf::Vector2f{ m_position.x - m_r, m_position.y - m_r});
        }

        void set_velocity(sf::Vector2f velocity) { 
            m_velocity = velocity;
        }

        sf::Vector2f get_velocity() {
            return m_velocity;
        }

        sf::Vector2f get_position() {
            return m_position;
        }

    };

}