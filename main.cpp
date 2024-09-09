#include <iostream>
#include <string>
#include <regex>
#include <vector>
using namespace std;


vector<int> extractIntegers(const string& input) {
    vector<int> integers;
    regex integerRegex("(-?\\d+)");
    sregex_iterator it(input.begin(), input.end(), integerRegex);
    sregex_iterator end;
 
    while (it != end) {
        integers.push_back(stoi(it->str()));
        ++it;
    }
 
    return integers;
}

vector<string> extractOpers(const string& input) {
    string input_copy = input;
    vector<string> opers;
    while(input_copy.find(" ") != string::npos) {
        size_t space = input_copy.find(" ");
        string helper = input_copy.substr(space + 1, 1);
        opers.push_back(helper);
        input_copy.erase(space, 3);
    }
    return opers;
}

int oper_result(int& x, int& y, string& oper) {
    if(oper == "+") {
        return x + y;
    } else if (oper == "-") {
        return x - y;
        } else if(oper == "/") {
            return x / y;
            } else if(oper == "*") {
                return x * y;
            }
    return 0;
}

bool isDividedByNull(vector<int>& integers, vector<string>& operations) {
    for(int i = 0; i < operations.size(); i++) {
        if(operations.at(i) == "/" && integers.at(i + 1) == 0) {
            return true;
        }
    }
    return false;
}

bool isThereOrder(const string& input) {
    if(input.find("*") != string::npos || input.find("/") != string::npos) {
        return true;
    }
    return false;
}

void order_oper_result(vector<int>& integers, vector<string>& operations, const string& input) {
    if(isThereOrder(input)) {
        for(int i = 0; i < operations.size(); i++) {
            if(operations.at(i) == "*" || operations.at(i) == "/") {
                int res = oper_result(integers.at(i), integers.at(i + 1), operations.at(i));
                integers.erase(next(integers.begin(), i), next(integers.begin(), 2 + i));
                operations.erase(next(operations.begin(), i));
                integers.insert(next(integers.begin(), i), res);
            }
        }
    }
}

void simple_opers(vector<int>& integers, vector<string>& operations) {
    int i = 0;
    while(!operations.empty()) {
        int res = oper_result(integers.at(i), integers.at(i + 1), operations.at(i));
        integers.erase(integers.begin(), next(integers.begin(), 2));
        operations.erase(operations.begin());
        integers.insert(integers.begin(), res);
    }
}

int main() {
    string input;
    cout << "Enter operation (or 'exit'): ";
    getline(cin, input);
    while(input != "exit") {
        vector<int> integers = extractIntegers(input);
        vector<string> operations = extractOpers(input);
        
        if(!isDividedByNull(integers, operations)) {
            order_oper_result(integers, operations, input);
            simple_opers(integers, operations);
            cout << "Result: " << integers[0] << endl;
        } else cout << "Error! Divided by NULL" << endl;
        
        
        cout << "Enter operation (or 'exit'): ";
        getline(cin, input);
    }
    
 
    return 0;
}
