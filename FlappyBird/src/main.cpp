
// modules and libraries
#include <iostream>
#include <filesystem>
#include "gameModes.h"
#include "times.h"

int main(int argc, char* argv[]) {

	// setup
	srand(static_cast<unsigned int>(unixTime()));

	// run game
	titlescreen();

	// output elapsed time and prevent closing
	#ifdef _DEBUG
	std::cout << "[Program Finished in " << elapsedTime() << "s]" << std::endl;
	std::cin.get();
	#endif
}

