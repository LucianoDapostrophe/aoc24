#include <fstream>
#include <string>
#include <iostream>
#include <stack>

using namespace std;

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

int parseMul(string op) {
    string mulRemoved = op.substr(3);
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
        while (line.find("mul") != string::npos) {
            line = line.substr(line.find("mul"));
            auto end = line.find(")") + 1;
            string op = line.substr(0, end);
            total += parseMul(op);
            line = line.substr(end);
        }
    }
    file.close();
    cout << total << endl;
}