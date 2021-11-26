#pragma once
#include <string>
#include <ostream>

// Period of the day
enum class Period {
	AM,
	PM
};

// Time in a day in hours and minutes in 12 hour format
class TimeOfDay
{
public:
	// Default time 00:00AM --> 0 hours usually not possible, which indicates uninitialized time
	TimeOfDay() : hours_(0), minutes_(0), period_(Period::AM) {};
	TimeOfDay(int hours, int minutes, Period period) : hours_(hours), minutes_(minutes), period_(period) {};

	bool operator<(const TimeOfDay& rhs) const;
	bool operator==(const TimeOfDay& rhs) const;
	bool operator!=(const TimeOfDay& rhs) const;
	bool operator<=(const TimeOfDay& rhs) const;
	bool operator>(const TimeOfDay& rhs) const;
	bool operator>=(const TimeOfDay& rhs) const;

	int GetHours() const { return hours_; }
	int GetMinutes() const { return minutes_; }
	Period GetPeriod() const { return period_; }

	TimeOfDay AddMinutes(int minutes) const; // Add given minutes and return new TimeOfDay

	// Output time in four digit format with period suffix: XX:XXAM
	friend std::ostream& operator<<(std::ostream& os, const TimeOfDay& time); 
private:
	int hours_;
	int minutes_;
	Period period_;
};