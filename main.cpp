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
 
int main() {
    string input;
    cout << "Enter operation (or ''exit''): ";
    getline(cin, input);
    vector<int> integers = extractIntegers(input);
    vector<string> operations = extractOpers(input);
    
    int i = 0;
    while(!operations.empty()) {
        int res = oper_result(integers.at(i), integers.at(i + 1), operations.at(i));
        integers.erase(integers.begin(), next(integers.begin(), 2));
        operations.erase(operations.begin());
        integers.insert(integers.begin(), res);
    }
    
    cout << "Result: " << integers[0] << endl;
 
    return 0;
}
