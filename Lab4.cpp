#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '=';
}

bool isInArray(const string arr[], int size, const string& str) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == str) {
            return true;
        }
    }
    return false;
}

bool isInArray(const char arr[], int size, char ch) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == ch) {
            return true;
        }
    }
    return false;
}

int main() {

    ifstream file("program.cpp");
    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    const int maxFunctions = 100;
    const int maxOperators = 100;

    string functionArray[maxFunctions];
    char operatorArray[maxOperators];

    int functionCount = 0;
    int operatorCount = 0;

    string line;
    string currentFunction;
    while (getline(file, line)) {

        size_t pos = line.find('(');
        if (pos != string::npos) {

            size_t functionNameStart = line.rfind(' ', pos);
            currentFunction = line.substr(functionNameStart + 1, pos - functionNameStart - 1);

            if (currentFunction != "main" && !isInArray(functionArray, functionCount, currentFunction)) {
                functionArray[functionCount++] = currentFunction;
            }
        }

        for (char c : line) {
            if (isOperator(c) && !isInArray(operatorArray, operatorCount, c)) {
                operatorArray[operatorCount++] = c;
            }
        }
    }

    cout << "User Defined Functions:\n";
    for (int i = 0; i < functionCount; ++i) {
        cout << "Function-" << i + 1 << ": " << functionArray[i] << '\n';
    }
    cout << "Total number of user-defined functions: " << functionCount << "\n\n";

    cout << "Operators:\n";
    for (int i = 0; i < operatorCount; ++i) {
        cout << "Operator-" << i + 1 << ": ";
        switch (operatorArray[i]) {
            case '+':
                cout << "addition\n";
                break;
            case '-':
                cout << "subtraction\n";
                break;
            case '*':
                cout << "multiplication\n";
                break;
            case '=':
                cout << "assignment\n";
                break;
            default:
                cout << "unknown\n";
        }
    }
    cout << "Total number of operators: " << operatorCount << "\n";

    file.close();

    return 0;
}
