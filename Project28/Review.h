#pragma once
#include <string>
#include <chrono>

struct Review {
	std::string id;
	std::string title;
	std::string author;
	std::chrono::system_clock::time_point date;
	int point = 0;
	std::string notes;
};
