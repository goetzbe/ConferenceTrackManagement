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

void TimeOfDay::AddMinutes(int minutes)
{
	minutes_ += minutes;

	if (minutes_ >= 60)
	{
		int hoursToAdd = minutes_ / 60;
		minutes_ = minutes_ % 60;

		if (hours_ < 12 && hours_ + hoursToAdd >= 12)
		{
			period_ = period_ == Period::AM ? Period::PM : Period::AM;
		}
		hours_ += hoursToAdd;
		hours_ = hours_ > 12 ? hours_ % 12 : 12;
	}

}