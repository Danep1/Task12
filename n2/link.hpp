#pragma once

#include <cmath>
#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "functions.hpp"
#include "particle.hpp"

class Link
{
public:

	using particle_t = std::shared_ptr < Particle > ;

private:

	particle_t m_particle_1;
	particle_t m_particle_2;

	const float m_stiffness;
	const float m_distance;

public:

	Link() noexcept = default;

	explicit Link(particle_t particle_1, particle_t particle_2, float stiffness) noexcept :
		m_particle_1(particle_1), m_particle_2(particle_2), m_stiffness(stiffness),
		m_distance(length(m_particle_1->get_pos() - m_particle_2->get_pos()))
	{}

	~Link() noexcept = default;

public:

	void update();

};