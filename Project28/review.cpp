#include "reviewkansu.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <iostream>
#include <chrono> 
using namespace std;


string Date(const chrono::system_clock::time_point& tp) {
	time_t t = chrono::system_clock::to_time_t(tp);
	char buf[11];
	tm tm{};
#if defined(_MSC_VER)
	localtime_s(&tm, &t);
#else
	localtime_r(&t, &tm);
#endif
	strftime(buf, sizeof(buf), "%Y-%m-%d", &tm);
	return string(buf);
}

void loadReviewsCSV(vector<Review>& reviews, const string& filename) {
	ifstream ifs(filename);
	if (!ifs) return; 

	string line;
	getline(ifs, line);

	while (getline(ifs, line)) {
		istringstream ss(line);
		Review r;
		string dateStr, pre;

		getline(ss, pre, ','); r.id = pre;
		getline(ss, pre, ','); r.title = pre.substr(1, pre.size() - 2);
		getline(ss, pre, ','); r.author = pre.substr(1, pre.size() - 2);
		getline(ss, dateStr, ',');
		getline(ss, pre, ','); r.point = stoi(pre);
		getline(ss, pre);     r.notes = pre.substr(1, pre.size() - 2);

		tm tm{};
		istringstream iss(dateStr);
		iss >> get_time(&tm, "%Y-%m-%d");
		auto time = mktime(&tm);
		r.date = chrono::system_clock::from_time_t(time);

		reviews.push_back(r);
	}
}

bool compareDate(const Review& a, const Review& b) {
	return a.date < b.date;
}

void saveReviewsCSV(const vector<Review>& reviews, const string& filename) {
	ofstream ofs(filename);
	if (!ofs) {
		cerr << "ファイルを開けませんでした ※ファイルを閉じて実行してください " << filename << "\n";
		return;
	}

	ofs << "ID,Title,Author,Date,Point,Notes\n";
	for (const auto& r : reviews) {
		ofs << r.id << ",\""
			<< r.title << "\",\""
			<< r.author << "\","
			<< Date(r.date) << ","
			<< r.point << ",\""
			<< r.notes << "\"\n";
	}
}
