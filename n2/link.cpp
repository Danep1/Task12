#include "link.hpp"
#include <iostream>

void Link::update()
{
	const auto delta = m_particle_2->get_pos() - m_particle_1->get_pos();

	m_particle_1->forse(norm(delta) * (length(delta) - m_distance) * m_stiffness);
	m_particle_2->forse(norm(delta) * (length(delta) - m_distance) * m_stiffness * -1.0f);
}