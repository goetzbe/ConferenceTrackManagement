#pragma once
#include <string>
#include <ostream>

enum class Period {
	AM,
	PM
};

class TimeOfDay
{
public:
	TimeOfDay(int hours, int minutes, Period period) : hours_(hours), minutes_(minutes), period_(period) {};

	void AddMinutes(int minutes);

	friend std::ostream& operator<<(std::ostream& os, const TimeOfDay& time);
private:
	int hours_;
	int minutes_;
	Period period_;
};