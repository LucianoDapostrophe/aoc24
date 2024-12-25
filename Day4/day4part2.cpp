#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
const string word = "MAS";

int checkDiagonals(const vector<string>& puzzle, int i, int j) {
    if (i-1 >= 0 && i+1 < puzzle.size() && j-1 >= 0 && j+1 < puzzle[i].length()) {
        string ascDiagonal = {puzzle[i+1][j-1], puzzle[i][j], puzzle[i-1][j+1]};
        string desDiagonal = {puzzle[i-1][j-1], puzzle[i][j], puzzle[i+1][j+1]};
        if (ascDiagonal == word && desDiagonal == word) return 1;
        string revAscDiag(ascDiagonal);
        reverse(revAscDiag.begin(), revAscDiag.end());
        if (revAscDiag == word && desDiagonal == word) return 1;
        string revDesDiag(desDiagonal);
        reverse(revDesDiag.begin(), revDesDiag.end());
        if (ascDiagonal == word && revDesDiag == word) return 1;
        if (revAscDiag == word && revDesDiag == word) return 1;
    }
    return 0;
}

int main() {
    ifstream file("input.txt");
    vector<string> crossword;
    string line;
    if (!file.is_open()) {
        cerr << "file failed to open" << endl;
        return 0;
    }
    while (getline(file, line)) {
        crossword.push_back(line);
    }
    int total = 0;
    for (int i = 0; i < crossword.size(); i++) {
        for (int j = 0; j < crossword[i].length(); j++) {
            if (crossword[i][j] == 'A') {
                total += checkDiagonals(crossword, i, j);
            }
        }
    }
    file.close();
    cout << total << endl;
}