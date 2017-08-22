#ifndef TIMER_H
#define TIMER_H


class Timer
{
public:
	inline Timer()
	{
		time = 0.0;
	}

	inline void Update(float dt)
	{
		time += dt;
	}

	inline void Restart()
	{
		time = 0.0;
	}

	inline float Get()
	{
		return time;
	}

private:
	float time;

};


#endif // TIMER_H
