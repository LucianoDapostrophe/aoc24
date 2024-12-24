#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

int main() {
    ifstream file("input.txt");
    string line;
    vector<int> list1;
    vector<int> list2;
    if (!file.is_open()) {
        cerr << "file failed to open" << endl;
        return 0;
    }
    while (getline(file, line)) {
        auto it = line.find(" ");
        list1.push_back(stoi(line.substr(0, it)));
        list2.push_back(stoi(line.substr(it)));
    }
    file.close();

    //part1
    sort(list1.begin(), list1.end());
    sort(list2.begin(), list2.end());
    int total = 0;
    for (int i = 0; i < list1.size(); i++) {
        total += abs(list1[i] - list2[i]);
    }   
    cout << total << endl;

    //part2
    map<int, int> list2Freq;
    set<int> list1Nums(list1.begin(), list1.end());
    for (int i = 0; i < list2.size(); i++) {
        if (list1Nums.find(list2[i]) != list1Nums.end()) {
            list2Freq[list2[i]]++;
        }
    }
    int similarity = 0;
    for (int n : list1) {
        similarity += n * list2Freq[n];
    }
    cout << similarity << endl;
}