#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

namespace mt
{

	class Player
	{
		sf::Vector2f m_position;
		sf::Vector2f m_min_move_limit;
		sf::Vector2f m_max_move_limit;

		sf::Vector2f m_move_direction;
		float m_speed = 250.f;

		sf::Vector2f m_scale = sf::Vector2f{0.2f, 0.2f};
		sf::Texture m_textureShip;
		sf::Sprite m_spriteShip;

		bool border_left_collision() {
			return m_position.x < m_min_move_limit.x; // left border
		}

		bool border_right_collision() {
			return m_position.x > m_max_move_limit.x; // left border
		}

		bool border_up_collision() {
			return m_position.y < m_min_move_limit.y;  // up border
		}

		bool border_down_collision() {
			return m_position.y > m_max_move_limit.y;  // down border
		}

	public:

		Player() = default;

		bool setup(const sf::Vector2f& position, const sf::Vector2f& min_move_limit, const sf::Vector2f& max_move_limit)
		{
			m_position = position;
			m_min_move_limit = min_move_limit;
			m_max_move_limit = max_move_limit;

			if (!m_textureShip.loadFromFile("assets\\player.png"))
			{
				std::cout << "Error while loading player.png" << std::endl;
				return false;
			}
			m_spriteShip.setTexture(m_textureShip);

			m_spriteShip.setScale(m_scale);
			m_spriteShip.setOrigin(m_textureShip.getSize().x / 2, m_textureShip.getSize().y / 2);
			m_spriteShip.setPosition(m_position);
			m_spriteShip.setRotation(0.0f);
		}

		void controll_events() {
			sf::Vector2f direction{ 0.0f, 0.0f };

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				direction.y -= 1.f;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				direction.y += 1.f;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				direction.x -= 1.f;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				direction.x += 1.f;
			}

			set_direction(direction);
		}

		void set_direction(const sf::Vector2f& direction)
		{
			float n = norm(direction);

			if (n == 0) {
				m_move_direction = direction;
			}
			else {
				m_move_direction = direction / n;
			}
			// std::cout << "Direction = " << m_move_direction.x << " " << m_move_direction.y << std::endl;
		}

		void move(float dt) {
			if (border_left_collision() && m_move_direction.x < 0.f) {
				m_move_direction.x = 0.f;
			}

			if (border_right_collision() && m_move_direction.x > 0.f) {
				m_move_direction.x = 0.f;
			}

			if (border_up_collision() && m_move_direction.y < 0.f) {
				m_move_direction.y = 0.f;
			}

			if (border_down_collision() && m_move_direction.y > 0.f) {
				m_move_direction.y = 0.f;
			}


			sf::Vector2f delta = m_move_direction * m_speed * dt;
			//std::cout << "Position delta = " << delta.x << " " << delta.y << std::endl;

			m_position += delta;
			//std::cout << "Position = " << m_position.x << " " << m_position.y << std::endl;

			m_spriteShip.setPosition(m_position);
		}

		sf::Sprite get_sprite()
		{
			return m_spriteShip;
		}
	};

}