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
	friend std::ostream& operator<<(std::ostream& os, const TimeOfDay& time);
private:
	int hours_;
	int minutes_;
	Period period_;
};

std::ostream& operator<<(std::ostream& os, const TimeOfDay& time) {
	// print hours with prefixed 0 for hours smaller than 10
	if (time.hours_ < 10) os << '0';
	os << time.hours_ << ':';

	// print minutes with prefixed 0 for minutes smaller than 10
	if (time.minutes_ < 10) os << '0';
	os << time.minutes_;

	// print suffix AM or PM
	if (time.period_ == Period::AM) os << "AM";
	else os << "PM";

	return os;
}