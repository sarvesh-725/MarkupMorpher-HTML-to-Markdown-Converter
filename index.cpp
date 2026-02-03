#include "lex.h"
#include "otherLex.h"
#include <bits/stdc++.h>

using namespace std;

int main() {
    ifstream file("input.md");  
    string line;
    // Check if file opened
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return 0;
    }
    vector<string> inputlines ; 
    // Read line by line
    while (getline(file, line)) {
        inputlines.push_back(line);
    }
    file.close();


    // lexical analysis
    unordered_map<string,int> mp = {{"######", 1}, {"#####", 2}, {"####", 3}, {"###", 4}, {"##", 5}, {"#", 6}, {"-", 7}, {"****", 8}, {"**", 9}, {"![", 10}, {"[", 11}, {"]", 12}, {"(", 13}, {")", 14}};

    vector<vector<string>> tokenizedOutput = lexfun(inputlines, mp);
    
    // Process trailing whitespace cases in otherLexFun
    vector<vector<string>> output = otherLexFun(tokenizedOutput, inputlines, mp);
    
    for(auto &vec : output) {
        for(auto &tok : vec) {
            cout << tok << " ";
        }
        cout << endl;
    }

    // ParseResult parseResult = parseDocument(output, mp);
    // for(const auto &msg : parseResult.messages) {
    //     cout << msg << endl;
    // }
    return 0;
}