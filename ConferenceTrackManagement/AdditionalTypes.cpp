#include "AdditionalTypes.h"

std::ostream& operator<<(std::ostream& os, const TimeOfDay& time) {
	// Print hours with prefixed 0 for hours smaller than 10
	if (time.hours_ < 10) os << '0';
	os << time.hours_ << ':';

	// Print minutes with prefixed 0 for minutes smaller than 10
	if (time.minutes_ < 10) os << '0';
	os << time.minutes_;

	// Print suffix AM or PM
	if (time.period_ == Period::AM) os << "AM";
	else os << "PM";

	// Return output stream
	return os;
}

bool TimeOfDay::operator<(const TimeOfDay& rhs) const
{
	if (period_ == rhs.GetPeriod())
	{
		return ((hours_%12 < rhs.GetHours()%12) || (hours_ == rhs.GetHours() && minutes_ < rhs.GetMinutes()));
	}
	if (period_ == Period::AM)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool TimeOfDay::operator==(const TimeOfDay& rhs) const
{
	return (period_ == rhs.GetPeriod() && hours_ == rhs.GetHours() && minutes_ == rhs.GetMinutes());
}

bool TimeOfDay::operator!=(const TimeOfDay& rhs) const
{
	return !(*this == rhs);
}

bool TimeOfDay::operator<=(const TimeOfDay& rhs) const
{
	return !(rhs < *this);
}

bool TimeOfDay::operator>(const TimeOfDay& rhs) const
{
	return rhs < *this;
}

bool TimeOfDay::operator>=(const TimeOfDay& rhs) const
{
	return !(*this < rhs);
}

TimeOfDay TimeOfDay::AddMinutes(int minutes) const
{
	TimeOfDay time = TimeOfDay(hours_, minutes_, period_); // Create new time
	time.minutes_ += minutes; // Add minutes

	if (time.minutes_ >= 60)
	{
		int hoursToAdd = time.minutes_ / 60; // Integer division for hours
		time.minutes_ = time.minutes_ % 60; // Modulo division for remaining minutes

		if (time.hours_ < 12 && time.hours_ + hoursToAdd >= 12) // Change period suffix if crossing 12 hour line
		{
			time.period_ = time.period_ == Period::AM ? Period::PM : Period::AM;
		}

		time.hours_ += hoursToAdd; // Add hours
		time.hours_ = time.hours_ > 12 ? time.hours_ % 12 : time.hours_; // Take modulo 12 of hours for 12 hour format
	}
	return time; // Return newly calculated time
}