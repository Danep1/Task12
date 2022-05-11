#pragma once

#include <iomanip>
#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "calculator.hpp"
#include "view.hpp"

class Visualizer
{
private:

    using complex = Calculator::complex;

    sf::RenderWindow m_window;
    sf::Image        m_image;
    sf::Sprite       m_sprite;
    sf::Texture      m_texture;
    sf::Font         m_font;
    sf::Text         m_text;

    bool m_need_redraw;

    const std::size_t m_width;
    const std::size_t m_height;

    const std::string m_font_filename = "consolas.ttf";
    const std::string m_pic_filename = "julia_c_0.37_-i0.25.jpg";

    const std::string m_title = "Julia fractal visualizer";

    const float m_scale_factor = 2.0f;
    const std::size_t m_max_iterations = 100ULL;
    const complex m_c;

    std::vector < sf::Color > m_colors;

    Calculator m_calculator;
    View m_view;

public:

	Visualizer(std::size_t width, std::size_t height, const complex & c) : m_window(sf::VideoMode(width, height), m_title, sf::Style::Close),
		m_need_redraw(true), m_width(width), m_height(height), m_c(c),
		m_calculator(width, height, m_max_iterations, c),
        m_view(sf::Vector2f(0.0f, 0.0f), 6.0f, 6.0f / (width / height))
	{
		initialize();
	}

	~Visualizer() noexcept = default;

private:

	void initialize();

public:

    void run();

private:

    void review();
    void update();
    void render();
    void save_pic();

private:
    
    void handle_key_pressed(sf::Keyboard::Key code);
};