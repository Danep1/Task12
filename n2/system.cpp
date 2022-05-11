#include "system.hpp"

void Lattice::initialize(float x_0, float y_0)
{
	for (auto i = 0U; i < m_M; ++i)
	{
		m_particles.emplace_back();
		for (auto j = 0U; j < m_N; ++j)
		{
			m_particles[i].emplace_back(std::make_shared<Particle>(sf::Vector2f(x_0 + i * m_a, y_0 + j * m_a),
				sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f), m_radius));
		}
	}

	for (auto i = 0ULL; i < m_M - 1; ++i)
	{
		for (auto j = 0ULL; j < m_N - 1; ++j)
		{
			m_links.emplace_back(particle(i, j), particle(i + 1, j), m_stiffness);
			m_links.emplace_back(particle(i, j), particle(i, j + 1), m_stiffness);
			m_links.emplace_back(particle(i, j), particle(i + 1, j + 1), m_stiffness);
			m_links.emplace_back(particle(i + 1, j), particle(i, j + 1), m_stiffness);
		}
		m_links.emplace_back(particle(i, m_N - 1), particle(i + 1, m_N - 1), m_stiffness);
	}
	for (auto k = 0ULL; k < m_N - 1; ++k)
	{
		m_links.emplace_back(particle(m_M - 1, k), particle(m_M - 1, k + 1), m_stiffness);
	}
}

void Lattice::push(const sf::Vector2f force) const
{
	for (auto & layer : m_particles)
		for (auto & particle : layer) 
		{
			particle->forse(force);
		}
}

void Lattice::update() const
{

	for (auto link : m_links)
	{
		link.update();
	}

	for (auto & layer : m_particles)
		for (auto & particle : layer)
		{
			particle->forse({ 0.0f, 0.01f});

			if (particle->get_pos().y + m_radius > m_max_point.y)
			{
				particle->set_v({ 0.0f, 0.0f });
				particle->forse(particle->get_a() * -1.0f);
				//particle->set_pos( particle->get_pos() + sf::Vector2f(0.0f, m_max_point.y - m_radius));
			}

			if (particle->get_pos().y - m_radius < m_min_point.y)
			{
				particle->set_v({ 0.0f, 0.0f });
				particle->forse(particle->get_a() * -1.0f);
				//particle->set_pos(particle->get_pos() + sf::Vector2f(0.0f, m_min_point.y + m_radius));
			}

			if (particle->get_pos().x + m_radius > m_max_point.x)
			{
				particle->set_v({ 0.0f, 0.0f });
				particle->forse(particle->get_a() * -1.0f);
				//particle->set_pos(particle->get_pos() + sf::Vector2f(m_max_point.x - m_radius, 0.0f));
			}

			if (particle->get_pos().x - m_radius < m_min_point.x)
			{
				particle->set_v({ 0.0f, 0.0f });
				particle->forse(particle->get_a() * -1.0f);
				//particle->set_pos(particle->get_pos() + sf::Vector2f(m_min_point.x + m_radius, 0.0f));
			}

			particle->move(1.25f);
		}
}