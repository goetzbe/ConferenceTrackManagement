#include "AdditionalTypes.h"

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

TimeOfDay TimeOfDay::AddMinutes(int minutes)
{
	TimeOfDay time = TimeOfDay(hours_, minutes_, period_);
	time.minutes_ += minutes;

	if (time.minutes_ >= 60)
	{
		int hoursToAdd = time.minutes_ / 60;
		time.minutes_ = time.minutes_ % 60;

		if (time.hours_ < 12 && time.hours_ + hoursToAdd >= 12)
		{
			time.period_ = time.period_ == Period::AM ? Period::PM : Period::AM;
		}
		time.hours_ += hoursToAdd;
		time.hours_ = time.hours_ > 12 ? time.hours_ % 12 : 12;
	}
	return time;
}