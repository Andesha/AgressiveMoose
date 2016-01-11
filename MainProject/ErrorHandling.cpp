#include "stdafx.h"
#include "ErrorHandling.h"

void outputError(std::string error) {
	std::cout << "An error has occurred:" << std::endl; // Pretty output formatting:
	std::cout << error << std::endl;
	std::cout << "Press any key to exit the application" << std::endl;

	int t; // Pause.
	std::cin >> t;

	SDL_Quit();
	exit(1); // Exit with error code.
}