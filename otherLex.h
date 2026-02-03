#ifndef OTHER_LEX_H
#define OTHER_LEX_H
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

vector<vector<string>> otherLexFun(vector<vector<string>> &tokenizedLines, 
                                    vector<string> &originalLines, 
                                    unordered_map<string,int> &sym);

#endif
