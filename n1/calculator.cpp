#include "calculator.hpp"

#include "visualizer.hpp"

void Calculator::initialize()
{
	m_field.resize(m_height);

	for (auto & row : m_field)
	{
		row.resize(m_width);
	}
}

void Calculator::calculate(sf::Vector2f center, float width, float height)
{
	auto threads_number = std::thread::hardware_concurrency();

	auto dx = width  / m_width;
	auto dy = height / m_height;

	std::vector < std::thread > threads(threads_number);

	const auto size = m_height / threads_number;
    const auto tail = m_height - threads_number * size;

    auto function = [=](std::size_t id)
    {
        const auto first_y = size * id;
        const auto last_y  = std::min(m_height, first_y + size);

		for (auto y = first_y; y < last_y; ++y)
		{
			for (auto x = 0U; x < m_width; ++x) 
			{
				complex z(
					center.x - width  / 2.0f + dx * x,
					center.y - height / 2.0f + dy * y					
				);

				auto iteration = 0U;

				for (; iteration < m_max_iterations && std::abs(z) <= m_R; ++iteration)
				{
					z = z * z + m_c;
				}

				m_field[x][y] = iteration;
			}
		}
    };

	for (auto id = 0ULL; id < threads_number; ++id)
	{
		threads[id] = std::thread(function, id);
	}

	if (tail > 0ULL)
	{
		function(threads_number);
	}

	for (auto id = 0ULL; id < threads_number; ++id)
	{
		threads[id].join();
	}
}