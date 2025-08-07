#include <iostream>
#include <algorithm>
#include <limits>
#include "Review.h"
#include "reviewkansu.h"
using namespace std;

template<typename T>
bool safeRead(T& out) {
	if (!(cin >> out)) return false;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return true;
}
bool safeRead(string& out) {
	return bool(getline(cin >> ws, out));
}

int main() {
	bool keep = true;
	vector<Review> reviews;
	loadReviewsCSV(reviews, "reviews.csv");
	while (keep) {
		cout << "ctrl+z‚Å’†’f\n";
		Review r;
		cout << "ID(ISBN): ";
		if (!safeRead(r.id)) {
			cout << "’†’f\n";
			return 1;
		}
		cout << "ƒ^ƒCƒgƒ‹: ";
		if (!safeRead(r.title)) {
			cout << "’†’f\n";
			return 1;
		}
		cout << "’˜ŽÒ: ";
		if (!safeRead(r.author)) {
			cout << "’†’f\n";
			return 1;
		}
		int y , m, d;
		cout << "“ú•t (YYYY¨Enter¨MM¨Enter¨DD‚Å“ü—Í): ";
		if (!safeRead(y)||!safeRead(m)||!safeRead(d)) {
			cout << "’†’f\n";
			return 1;
		}
		{
			tm tm = {};
			tm.tm_year = y - 1900;
			tm.tm_mon = m - 1;
			tm.tm_mday = d;
			r.date = chrono::system_clock::from_time_t(mktime(&tm));
		}
		cout << "•]‰¿(“_”‚ð‚Â‚¯‚Ä‚­‚¾‚³‚¢B): ";
		if (!safeRead(r.point)) {
			cout << "’†’f\n";
			return 1;
		}
		cout << "ƒƒ‚: ";
		if (!safeRead(r.notes)) {
			cout << "’†’f\n";
			return 1;
		}
		reviews.push_back(r);
		
		char conti{};
		while(true){
			cout << "‘±‚¯‚Ä“ü—Í‚µ‚Ü‚·‚©? (y/n): ";
			if (!(cin >> conti)) {
				cout << "“ü—ÍƒGƒ‰[\n";
				return 1;
			}
			if (conti == 'n') {
				cout << "I—¹‚µ‚Ü‚µ‚½B\n";
				keep = false;
				break;
			}
			if(conti == 'y') {
				break;
			}
			cout << "y/n‚ð“ü—Í‚µ‚Ä‚­‚¾‚³‚¢B\n";
		}
	}
	sort(reviews.begin(), reviews.end(), compareDate);
	saveReviewsCSV(reviews, "reviews.csv");
	cout << "reviews.csv‚É•Û‘¶‚µ‚Ü‚µ‚½B\n";
	return 0;
}