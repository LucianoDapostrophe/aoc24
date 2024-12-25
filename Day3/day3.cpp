#include <fstream>
#include <string>
#include <iostream>
#include <stack>

using namespace std;

bool doFunc = true;
int parseMul(string op);

bool checkBrackets(string op) {
    stack<char> stack;
    for (char c : op) {
        if (c == '(') {
            stack.push(c);
        }
        else if (c == ')') {
            if (!stack.empty() && stack.top() == '(') {
                stack.pop();
            } 
            else {
                return false;
            }
        }
    }
    if (stack.empty()) return true;
    else return false;
}

bool checkDigits(string operand) {
    for (char c : operand) {
        if (!isdigit(c)) return false;
    }
    return true;
}

int parseOps(string& line) {
    int lineTotal = 0;
    while (line.find("mul") != string::npos) {
        auto nearestMul = line.find("mul");
        auto nearestDo = line.find("do()");
        auto nearestDont = line.find("don't()");
        if (nearestMul < nearestDont) {
            line = line.substr(nearestMul);
            auto end = line.find(")") + 1;
            if (doFunc || nearestDo < nearestMul) {
                doFunc = true;
                string op = line.substr(0, end);
                lineTotal += parseMul(op);
            }
            line = line.substr(end);
        }
        else if (nearestDont < nearestDo) {
            doFunc = false;
            line = line.substr(nearestDont + 7);
        }
    }
    //for substrings, do and don't after no more muls matters
    while (line.find("do()") != string::npos || line.find("don't()") != string::npos) {
        auto nearestDo = line.find("do()");
        auto nearestDont = line.find("don't()");
        if (nearestDont < nearestDo) {
            doFunc = false;
            line = line.substr(nearestDont + 7);
        }
        else {
            doFunc = true;
            line = line.substr(nearestDo + 4);
        }
    }
    return lineTotal;
}

int parseMul(string op) {
    string mulRemoved = op.substr(3);
    //if there's a nested don't, this mul isn't valid so parse this
    //subline and then parse the rest
    if (mulRemoved.find("don't()") != string::npos) {
        return parseOps(mulRemoved);
    }
    //check the brackets
    if (mulRemoved[0] == '(' && mulRemoved[mulRemoved.length() - 1] == ')' && checkBrackets(mulRemoved)) {
        //remove outer brackets
        string bracketsRemoved = mulRemoved.substr(1, mulRemoved.length() - 2);
        //separate the operands
        auto comma = bracketsRemoved.find(",");
        if (comma == string::npos) return 0;
        string strOperand1 = bracketsRemoved.substr(0, comma);
        string strOperand2 = bracketsRemoved.substr(comma + 1);
        if (checkDigits(strOperand1) && checkDigits(strOperand2)) {
            //return multiplication
            return stoi(strOperand1) * stoi(strOperand2);
        }
        return 0;
    }
    else {
        //look for nested mul
        auto it = mulRemoved.find("mul");
        if (it != string::npos) {
            auto end = mulRemoved.find(")");
            if (end == mulRemoved.length() - 1) {
                return parseMul(mulRemoved.substr(it));
            }
            return parseMul(mulRemoved.substr(it, end + 1));
        }
        return 0;
    }
}


int main() {
    ifstream file("input.txt");
    string line;
    if (!file.is_open()) {
        cerr << "file failed to open" << endl;
        return 0;
    }
    int total = 0;
    while (getline(file, line)) {
        total += parseOps(line);
    }
    file.close();
    cout << total << endl;
}