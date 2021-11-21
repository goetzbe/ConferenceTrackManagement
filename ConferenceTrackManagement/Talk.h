#pragma once
#include <string>

class Talk {
public:
	Talk(std::string& inputString);
	std::string GetName() const { return name_; }
	int GetLength() const { return length_; }
private:
	std::string name_;
	int length_;

};