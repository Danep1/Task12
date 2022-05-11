#pragma once

#include <complex>
#include <iostream>
#include <thread>
#include <vector>

#include <SFML/Graphics.hpp>



class Calculator
{
public:

	using complex = std::complex<float>;
    using field_t = std::vector < std::vector < std::size_t > > ;

private:

	std::size_t m_width;
	std::size_t m_height;
	std::size_t m_max_iterations;
	complex m_c;
	float m_R;

	field_t m_field;

public:

	explicit Calculator(std::size_t width, std::size_t height, std::size_t max_iterations, const complex& c) :
		m_width(width), m_height(height), m_max_iterations(max_iterations), m_c(c),
		m_R(0.5f + std::sqrtf(0.25f + std::abs(c)))
	{
		initialize();
	}

	~Calculator() noexcept = default;

private:

	void initialize();

public:

	void calculate(sf::Vector2f center, float width, float height);

    const auto & field() const noexcept 
	{ 
		return m_field; 
	}

	auto width () const noexcept 
	{ 
		return m_width;  
	}

	auto height() const noexcept 
	{ 
		return m_height; 
	}

	auto max_iterations() const noexcept 
	{ 
		return m_max_iterations; 
	}
};