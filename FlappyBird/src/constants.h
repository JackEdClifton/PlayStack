#pragma once

// global constants
namespace CONST {

	// window
	static const unsigned int WINDOW_WIDTH = 600;
	static const unsigned int WINDOW_HEIGHT = 600;

	// pipe
	static const int PIPE_COUNT = 3;
	static const float PIPE_FIRST_X = 500.0f;
	static const float PIPE_GAP = static_cast<float>(WINDOW_WIDTH) / (PIPE_COUNT-1);
}