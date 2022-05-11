#include <exception>
#include <iostream>

#include "visualizer.hpp"

int main(int argc, char ** argv)
{
	const auto wight = 1000LL;

	const auto height = 1000ULL;

    try 
	{
        Visualizer visualizer(1000ULL, 1000ULL, {0.37f, -0.25f});

		visualizer.run();
    }
    catch (const std::exception & exception) 
	{
        std::cerr << exception.what() << '\n';

		system("pause");

        return EXIT_FAILURE;
    }
	catch (...)
	{
		std::cerr << "Unknown exception\n";

		system("pause");

		return EXIT_FAILURE;
	}

	system("pause");

    return EXIT_SUCCESS;
}
