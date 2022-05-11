#pragma once

#include <cmath>
#include <vector>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "functions.hpp"
#include "system.hpp"

class Visualizer
{
private:
	const float m_width = 800;
	const float m_height = 800;

	const std::string m_title = "PHYSICS";
	const float m_a = 50.0f;
	const float m_particle_radius = 5.0f;

	sf::RenderWindow m_window;
	sf::Event m_event;

	Lattice m_lattice;

public:
	Visualizer() : m_window(sf::VideoMode(m_width, m_height), m_title, sf::Style::Titlebar | sf::Style::Close),
		m_lattice(m_width / m_a - 1ULL, m_height / m_a - 1ULL, m_a, m_particle_radius, 
			{0.0f, 0.0f}, {m_width, m_height - m_a}) {}

	void run()
	{
		m_window.setFramerateLimit(60U);


		while (m_window.isOpen())
		{
			while (m_window.pollEvent(m_event))
			{
				if (m_event.type == sf::Event::MouseButtonPressed)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						track_mouse();
					}
				}

				if (m_event.type == sf::Event::Closed)
				{
					m_window.close();
				}
			}

			m_lattice.update();

			m_window.clear();

			draw();

			m_window.display();
		}
	}

private:


	void track_mouse()
	{
		auto i = (static_cast<int>((sf::Mouse::getPosition() - m_window.getPosition()).x) / static_cast<int>(m_a)) - 1;
		auto j = (static_cast<int>((sf::Mouse::getPosition() - m_window.getPosition()).y) / static_cast<int>(m_a)) - 1;

		try
		{
			m_lattice.particle(i, j)->forse(sf::Vector2f(1.0f, 1.0f) * 1.5f);
		}
		catch (const std::exception & ec)
		{
			std::cerr << "Error: " << ec.what() << std::endl;
		}
	}

	void draw()
	{
		for (auto & layer: m_lattice.particles())
			for (auto & particle : layer)
			{
				sf::CircleShape circle(m_particle_radius);

				circle.setPosition(particle->get_pos() + sf::Vector2f(1.0f, 1.0f) * m_particle_radius);

				circle.setFillColor(sf::Color::Red);

				m_window.draw(circle);
			}
	}
};
