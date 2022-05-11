#pragma once

#include <cmath>
#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "functions.hpp"
#include "link.hpp"
#include "particle.hpp"

class Lattice
{
public:

	using particle_t = std::shared_ptr < Particle > ;

private:

	const sf::Vector2f m_min_point;
	const sf::Vector2f m_max_point;

	const std::size_t m_M;
	const std::size_t m_N;
	const float m_a;
	const float m_radius;
	const float m_stiffness = 0.05f;

	std::vector < std::vector < particle_t > > m_particles;

	std::vector < Link > m_links;

public:

	explicit Lattice(std::size_t m, std::size_t n, float a, float radius, sf::Vector2f min_point, sf::Vector2f max_point) noexcept :
		m_min_point(min_point), m_max_point(max_point), m_M(m), m_N(n), m_a(a), m_radius(radius)
	{
		initialize(a, a);
	}

	~Lattice() noexcept = default;

private:

	void initialize(float y_0, float x_0);

public:

	particle_t particle(std::size_t i, std::size_t j) const
	{
		return m_particles.at(i).at(j);
	}

	particle_t particle_xy(sf::Vector2i pos) const
	{
		auto i = pos.x / static_cast<int>(m_a) - 1;
		auto j = pos.y / static_cast<int>(m_a) - 1;
		return m_particles.at(i).at(j);
	}

	const auto & particles() const noexcept
	{
		return m_particles;
	}

public:
	
	void push(sf::Vector2f force) const;

	void update() const;

};