#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Particle
{
private:

	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;

	float m_radius;
	//float m_charge;

public:

	Particle() noexcept = default;

	explicit Particle(sf::Vector2f position, sf::Vector2f velocity,
		sf::Vector2f acceleration, float radius) noexcept :
			m_position(position), m_velocity(velocity),
			m_acceleration(acceleration), m_radius(radius)
	{}

	~Particle() noexcept = default;

public:

	const auto get_pos() const noexcept 
	{ 
		return m_position; 
	}

	const auto get_v() const noexcept
	{
		return m_velocity;
	}

	const auto get_a() const noexcept
	{
		return m_acceleration;
	}

	const auto get_radius() const noexcept
	{
		return m_radius;
	}

public:
	void set_pos(sf::Vector2f pos) noexcept
	{
		m_position = pos;
	}

	void set_v(sf::Vector2f v) noexcept
	{
		m_velocity = v;
	}

public:

	void forse(sf::Vector2f delta);

	void move(float dt);

};