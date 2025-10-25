
/* modules and libraries */
#include <chrono>
#include <thread>
#include "times.h"

/* get unix time */
double unixTime() {
	return static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count()) / 1000000000.0;
}

/* get time delta from start of runtime */
const double START_UNIX_TIME = unixTime();
float elapsedTime() { return (float)(unixTime() - START_UNIX_TIME); }

/* random number */
int randint(int min, int max) {
	return min + (rand() % (max-min));
}

/* sleep in seconds */
void sleep(int duration) { std::this_thread::sleep_for(std::chrono::milliseconds((int)(duration * 1000))); }
void sleep(float duration) { std::this_thread::sleep_for(std::chrono::milliseconds((int)(duration * 1000.0f))); }
void sleep(double duration) { std::this_thread::sleep_for(std::chrono::milliseconds((int)(duration * 1000.0))); }

/* container for frametime variables */
FrameTimer::FrameTimer() {
	start = elapsedTime();
	update();
}
void FrameTimer::update() {
	end = elapsedTime();
	delta = end - start;
	start = end;
	fps = 1 / delta;
}

