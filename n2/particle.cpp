#include "particle.hpp"

void Particle::forse(sf::Vector2f forse)
{
	m_acceleration += forse;
}

void Particle::move(float dt)
{
	m_velocity += m_acceleration * dt;

	m_position += m_velocity * dt;

	m_acceleration = sf::Vector2f(0.0f, 0.0f);
}