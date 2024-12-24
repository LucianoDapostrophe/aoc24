#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

bool checkSafeDecreasing(const vector<int>& report, bool dampener) {
    for (int i = 1; i < report.size(); i++) {
        int difference = report[i] - report[i - 1];
        if (difference < -3 || difference >= 0) {
            if (dampener) {
                vector<int> reportIRemoved(report.begin(), report.end());
                reportIRemoved.erase(reportIRemoved.begin() + i);
                vector<int> reportIMinus1Removed(report.begin(), report.end());
                reportIMinus1Removed.erase(reportIMinus1Removed.begin() + i - 1);
                return checkSafeDecreasing(reportIRemoved, false) || checkSafeDecreasing(reportIMinus1Removed, false);
            }
            return false;
        }
    }
    return true;
}

bool checkSafeIncreasing(const vector<int>& report, bool dampener) {
    for (int i = 1; i < report.size(); i++) {
        int difference = report[i] - report[i - 1];
        if (difference > 3 || difference <= 0) {
            if (dampener) {
                vector<int> reportIRemoved(report.begin(), report.end());
                reportIRemoved.erase(reportIRemoved.begin() + i);
                vector<int> reportIMinus1Removed(report.begin(), report.end());
                reportIMinus1Removed.erase(reportIMinus1Removed.begin() + i - 1);
                return checkSafeIncreasing(reportIRemoved, false) || checkSafeIncreasing(reportIMinus1Removed, false);
            }
            return false;
        }
    }
    return true;
}

int main() {
    ifstream file("input.txt");
    string line;
    if (!file.is_open()) {
        cerr << "file failed to open" << endl;
        return 0;
    }
    int safeCount = 0;
    while (getline(file, line)) {
        stringstream lineStream(line);
        int n;
        vector<int> report;
        while (lineStream >> n) {
            report.push_back(n);
        }
        if (checkSafeIncreasing(report, true) || checkSafeDecreasing(report, true)) {
            safeCount++;
        }
    }
    cout << safeCount << endl;
    file.close();
}