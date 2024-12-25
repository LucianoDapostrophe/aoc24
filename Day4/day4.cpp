#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
const string word = "XMAS";

int checkForward(const vector<string>& puzzle, int i, int j) {
    if (j + 3 < puzzle[i].length()) {
        string matchCheck = puzzle[i].substr(j, word.length());
        if (matchCheck == word) return 1;
    }
    return 0;
}

int checkBackward(const vector<string>& puzzle, int i, int j) {
    if (j - 3 >= 0) {
        string matchCheck = puzzle[i].substr(j - 3, word.length());
        reverse(matchCheck.begin(), matchCheck.end());
        if (matchCheck == word) return 1;
    }
    return 0;
}

int checkUp(const vector<string>& puzzle, int i, int j) {
    if (i - 3 >= 0) {
        string matchCheck = {puzzle[i][j], puzzle[i-1][j], puzzle[i-2][j], puzzle[i-3][j]};
        if (matchCheck == word) return 1;
    }
    return 0;
}

int checkDown(const vector<string>& puzzle, int i, int j) {
    if (i + 3 < puzzle.size()) {
        string matchCheck = {puzzle[i][j], puzzle[i+1][j], puzzle[i+2][j], puzzle[i+3][j]};
        if (matchCheck == word) return 1;
    }
    return 0;
}

int checkNW(const vector<string>& puzzle, int i, int j) {
    if (i - 3 >= 0 && j - 3 >= 0) {
        string matchCheck = {puzzle[i][j], puzzle[i-1][j-1], puzzle[i-2][j-2], puzzle[i-3][j-3]};
        if (matchCheck == word) return 1;
    }
    return 0;
}

int checkNE(const vector<string>& puzzle, int i, int j) {
    if (i - 3 >= 0 && j + 3 < puzzle[i].length()) {
        string matchCheck = {puzzle[i][j], puzzle[i-1][j+1], puzzle[i-2][j+2], puzzle[i-3][j+3]};
        if (matchCheck == word) return 1;
    }
    return 0;
}

int checkSE(const vector<string>& puzzle, int i, int j) {
    if (i + 3 < puzzle.size() && j + 3 < puzzle[i].length()) {
        string matchCheck = {puzzle[i][j], puzzle[i+1][j+1], puzzle[i+2][j+2], puzzle[i+3][j+3]};
        if (matchCheck == word) return 1;
    }
    return 0;
}

int checkSW(const vector<string>& puzzle, int i, int j) {
    if (i + 3 < puzzle.size() && j - 3 >= 0) {
        string matchCheck = {puzzle[i][j], puzzle[i+1][j-1], puzzle[i+2][j-2], puzzle[i+3][j-3]};
        if (matchCheck == word) return 1;
    }
    return 0;
}

int main() {
    ifstream file("input.txt");
    vector<string> crossword;
    // {
    //     "MMMSXXMASM",
    //     "MSAMXMSMSA",
    //     "AMXSXMAAMM",
    //     "MSAMASMSMX",
    //     "XMASAMXAMM",
    //     "XXAMMXXAMA",
    //     "SMSMSASXSS",
    //     "SAXAMASAAA",
    //     "MAMMMXMMMM",
    //     "MXMXAXMASX"
    // };
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
            if (crossword[i][j] == 'X') {
                total += checkForward(crossword, i, j);
                total += checkBackward(crossword, i, j);
                total += checkUp(crossword, i, j);
                total += checkDown(crossword, i, j);
                total += checkNW(crossword, i, j);
                total += checkNE(crossword, i, j);
                total += checkSW(crossword, i, j);
                total += checkSE(crossword, i, j);
            }
        }
    }
    file.close();
    cout << total << endl;
}