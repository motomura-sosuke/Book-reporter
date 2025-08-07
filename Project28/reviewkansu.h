#pragma once
#include <vector>
#include "Review.h"

void loadReviewsCSV(std::vector<Review>& reviews, const std::string& filename);
void saveReviewsCSV(const std::vector<Review>& reviews, const std::string& filename);
bool compareDate(const Review& a, const Review& b);
