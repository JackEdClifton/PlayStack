#pragma once

/* get unix time */
double unixTime();

/* get time delta from start of runtime */
float elapsedTime();

/* random number */
int randint(int min, int max);

/* sleep in seconds */
void sleep(int duration);
void sleep(float duration);
void sleep(double duration);

/* container for frametime variables */
struct FrameTimer {
	float delta, start, end, fps;
	FrameTimer();
	void update();
};